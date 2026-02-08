#include <sbi/sbi_console.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_trap.h>
#include <sbi/sbi_ml.h>
#include <sbi/riscv_asm.h>

#include <stddef.h>
#include <riscv_vector.h>

#define assert(val,str) if(!(val)){sbi_panic(str);}

// 方式2：定义自定义宏（复用性更好，放在代码头部）
#define MY_FLOAT_INFINITY  (*(float32_t *)&(uint32_t){0x7F800000})//定义正无穷
#define MY_FLOAT_NEG_INFINITY (*(float32_t *)&(uint32_t){0xFF800000})//定义负无穷

#define SBI_ML_ERR_MASK    (0xFFFF000000000000UL)
#define SBI_ML_VAL_MASK    (0x0000FFFFFFFFFFFFUL)
#define SBI_ML_SET_ERR(val, err) ((val) & SBI_ML_VAL_MASK) | (((unsigned long)(err)) << 48)
#define SBI_ML_GET_ERR(val)       ((int)((val) >> 48))
#define SBI_ML_GET_VAL(val)       ((val) & SBI_ML_VAL_MASK)
//static int use_fxdpt=0;
#define m2d(x, i, j)    ((x)->values[i * (x)->shape[2] + j])
#define m1d(x, i)       ((x)->values[i])
#define _ReLU(x)        (x > 0 ?  x : 0)

// 极简版 expf()：计算 e^x（x 为 float32_t，适用于 |x| ≤ 5.0f，满足 sigmoid 需求）
float32_t my_expf(float32_t x) {
    // 处理特殊情况（避免溢出，适配你的代码场景）
    if (x > 30.0f) return MY_FLOAT_INFINITY;  // e^30 已远超 float 有效范围，返回正无穷
    if (x < -30.0f) return 0.0f;              // e^-30 趋近于 0，直接返回 0

    // 泰勒级数展开：e^x = 1 + x + x²/2! + x³/3! + x⁴/4! + ... + x^n/n!
    float32_t result = 1.0f;
    float32_t term = 1.0f;
    int n = 1;

    // 迭代计算（迭代 10 次，满足单精度浮点精度要求）
    while (n <= 30) {
        term *= x / (float32_t)n;
        result += term;
        n++;
    }

    return result;
}

// 极简版 tanhf()：计算 tanh(x)，依赖自定义 my_expf()
float32_t my_tanhf(float32_t x) {
    // 利用奇偶性：tanh(-x) = -tanh(x)，减少计算量
    if (x < 0.0f) {
        return -my_tanhf(-x);
    }

    // 处理特殊情况
    if (x > 10.0f) return 1.0f;    // x 过大，tanh(x) 趋近于 1
    if (x < 1e-8f) return x;       // x 过小，tanh(x) ≈ x

    // 核心公式：tanh(x) = (e^(2x) - 1) / (e^(2x) + 1)
    float32_t e_2x = my_expf(2.0f * x);
    return (e_2x - 1.0f) / (e_2x + 1.0f);
}

void matmul_rvv(double *a, double *b, double *c, int n, int m, int p) {
  size_t vlmax = __riscv_vsetvlmax_e64m1();
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      double *ptr_a = &a[i * p];
      double *ptr_b = &b[j];
      int k = p;
      // Set accumulator to  zero.
      vfloat64m1_t vec_s = __riscv_vfmv_v_f_f64m1(0.0, vlmax);
      vfloat64m1_t vec_zero = __riscv_vfmv_v_f_f64m1(0.0, vlmax);
      for (size_t vl; k > 0; k -= vl, ptr_a += vl, ptr_b += vl * m) {
        vl = __riscv_vsetvl_e64m1(k);

        // Load row a[i][k..k+vl)
        vfloat64m1_t vec_a = __riscv_vle64_v_f64m1(ptr_a, vl);
        // Load column b[k..k+vl)[j]
        vfloat64m1_t vec_b =
          __riscv_vlse64_v_f64m1(ptr_b, sizeof(double) * m, vl);

        // Accumulate dot product of row and column. If vl < vlmax we need to
        // preserve the existing values of vec_s, hence the tu policy.
        vec_s = __riscv_vfmacc_vv_f64m1_tu(vec_s, vec_a, vec_b, vl);
      }

      // Final accumulation.
      vfloat64m1_t vec_sum =
        __riscv_vfredusum_vs_f64m1_f64m1(vec_s, vec_zero, vlmax);
      double sum = __riscv_vfmv_f_s_f64m1_f64(vec_sum);
      c[i * m + j] = sum;
    }
}

static inline int matmul_1(Tensor *dst, Tensor *src1, Tensor *src2, int use_fxdpt)
{
    int i, j, k;
    if (use_fxdpt) {
        fxdpt_t *psrc1 = (fxdpt_t *)src1->data;
        fxdpt_t *psrc2 = (fxdpt_t *)src2->data;
        fxdpt_t *pdst = (fxdpt_t *)dst->data;
        for(i = 0; i < src1->shape[1]; i++)
            for(j = 0; j < src2->shape[2]; j++)
                for(k = 0; k < src1->shape[2]; k++){
                    pdst[i * src2->shape[2] + j] += fxdpt_mul(psrc1[i * src1->shape[2] + k],psrc2[k * src2->shape[2] + j]);
                }
    } else {
        float *psrc1 = (float *)src1->data;
        float *psrc2 = (float *)src2->data;
        float *pdst = (float *)dst->data;
        for(i = 0; i < src1->shape[1]; i++)
            for(j = 0; j < src2->shape[2]; j++)
                for(k = 0; k < src1->shape[2]; k++){
                    pdst[i * src2->shape[2] + j] += float32_mul(psrc1[i * src1->shape[2] + k],psrc2[k * src2->shape[2] + j]);
                }
    }
    return 0; // 成功返回0
}

static inline int matmul(Tensor *dst, Tensor *src1, Tensor *src2, int use_fxdpt)
{
    //asm volatile("fence iorw, iorw" ::: "memory");
    // 1. 通用参数校验（两种模式共用）
    //sbi_printf("matmul\n");
    //sbi_printf("地址:%p\n",src1->shape);
    //sbi_printf("地址:%p\n",src1->shape+1);
    //sbi_printf("地址%p\n",src1->shape+2);
    //sbi_printf("1\n");
    int h1 = src1->shape[1];  // 矩阵1的行
    //sbi_printf("2\n");
    int w1 = src1->shape[2];  // 矩阵1的列
    int h2 = src2->shape[1];  // 矩阵2的行
    int w2 = src2->shape[2];  // 矩阵2的列
    //sbi_printf("w1:%d\nh2:%d\n",w1,h2);
    //sbi_printf("w1地址:%p\nh2地址:%p\n",&src1->shape[2],&src2->shape[1]);
    //sbi_printf("mat_src1->data:%p\n",src1->data);
    //sbi_printf("mat_src2->data:%p\n",src2->data);
    //sbi_printf("mat_dst:%p\n",dst->data);
    //sbi_printf("src1内容:%d\nsrc2内容:%d\ndst内容:%d\n",*((int *)src1->data),*((int *)src2->data),*((int *)dst->data));
    //sbi_printf("src1内容:%d\nsrc2内容:%d\ndst内容:%d\n",*((int *)src1->data+1),*((int *)src2->data+1),*((int *)dst->data));
    // 矩阵乘法合法性校验：矩阵1的列必须等于矩阵2的行
    if (w1 != h2) {
        sbi_printf("Matmul error: src1 cols(%d) != src2 rows(%d)\n", w1, h2);
        return -1;
    }

    int hout = dst->shape[1]; // 结果矩阵的行
    int wout = dst->shape[2]; // 结果矩阵的列
    // 结果矩阵尺寸校验：行=矩阵1的行，列=矩阵2的列
    if (hout != h1 || wout != w2) {
        sbi_printf("Matmul error: dst shape(%d,%d) mismatch expected(%d,%d)\n",
                   hout, wout, h1, w2);
        return -1;
    }

    // 2. 运行时模式切换（核心逻辑）
    if (use_fxdpt) {
        // ===================== 定点数模式（fxdpt_t）=====================
        //sbi_printf("定点数模式\n");
        //sbi_printf("测试:\n%d",*((fxdpt_t *)src1->data));
        fxdpt_t *psrc1 = (fxdpt_t *)src1->data;
        /*if (*((fxdpt_t *)src1->data) == psrc1[0])
            sbi_printf(" == ");
        else
            sbi_printf(" != ");
        sbi_printf("%d\n",psrc1[0]);
        sbi_printf("测试:\n%d",*((fxdpt_t *)src2->data));*/
        fxdpt_t *psrc2 = (fxdpt_t *)src2->data;
        /*if (*((fxdpt_t *)src2->data) == psrc2[0])
            sbi_printf(" == ");
        else
            sbi_printf(" != ");
        sbi_printf("%d\n",psrc2[0]);*/
        fxdpt_t *pdst = (fxdpt_t *)dst->data;
        //sbi_printf("mat_src1->data:%p\n",src1->data);
        //sbi_printf("mat_src2->data:%p\n",src2->data);
        //sbi_printf("mat_dst:%p\n",dst->data);
        // 三重循环实现定点数矩阵乘法（和S-mode MLLB逻辑完全对齐）
        for (int i = 0; i < h1; i++) {          // 遍历矩阵1的行
            for (int j = 0; j < w2; j++) {      // 遍历矩阵2的列
                fxdpt_ext sum = 0;              // 64位累加避免溢出
                for (int k = 0; k < w1; k++) {  // 遍历公共维度
                    // 定点数乘法累加（复用S-mode的运算规则）
                    fxdpt_t psrc1_val = psrc1[i * w1 + k];
                    //sbi_printf("mat_%d_%d_%d_src1->data:%p\n",i,j,k,src1->data);
                    fxdpt_t psrc2_val = psrc2[k * w2 + j];
                    //sbi_printf("%d_%d:%d*%d\n",j,k,psrc1[i * w1 + k],psrc2[k * w2 + j]);
                    //sbi_printf("%d_%d:%d*%d\n",j,k,psrc1_val,psrc2_val);
                    sum += (fxdpt_ext)psrc1_val * psrc2_val;
                    //sbi_printf("%d_%d:%d*%d=%ld\n",j,k,psrc1_val,psrc2_val,sum);
                }
                // 移位得到最终定点数结果（除以2^11）
                //sbi_printf("数值为:%ld\n",sum);
                fxdpt_t a = (fxdpt_t)(sum >> FXDPT_FBITS);
                //sbi_printf("数值为:%d\n",a);
                pdst[i * w2 + j] = a;
                //sbi_printf("mat_%d_src1->data:%p\n",j,src1->data);
                //sbi_printf("src1的地址:%p\n",&src1->data);
                //sbi_printf("dst_%d内容:%d\n",j,pdst[i * w2 + j]);
                //sbi_printf("dst_%d地址:%p\n",j,&(pdst[i * w2 + j]));
            }
        }
        /*sbi_printf("mat_src1->data:%p\n",src1->data);
        sbi_printf("mat_src2->data:%p\n",src2->data);
        sbi_printf("mat_dst:%p\n",dst->data);
        sbi_printf("2\n");*/
    } else {
        // ===================== 32位浮点数模式（对齐S-mode MLLB）=====================
        // 类型转换：数据区为32位浮点数（float）
        sbi_printf("float\n");
        float *psrc1 = (float *)src1->data;
        float *psrc2 = (float *)src2->data;
        float *pdst = (float *)dst->data;

        int vl = 0;
        for (int i = 0; i < h1; i++) {
            for (int j = 0; j < w2; j += vl) {
                // 设置RVV向量长度：适配32位浮点数（e32m4）
                vl = __riscv_vsetvl_e32m4(w2 - j);

                // 初始化累加和为0（32位浮点数，和S-mode一致）
                vfloat32m4_t _sum = __riscv_vfmv_v_f_f32m4(0.f, vl);
                
                int offset_dst = i * w2 + j;
                float *_psrc1_off = psrc1 + i * w1;
                float *_psrc2_off = psrc2 + j;

                for (int k = 0; k < w1; k++) {
                    float _src1 = *_psrc1_off;
                    // 加载32位浮点数向量（vle32_v_f32m4）
                    vfloat32m4_t _src2 = __riscv_vle32_v_f32m4(_psrc2_off, vl);
                    // 32位浮点数乘累加（vfmaddd_vf_f32m4）：_sum += _src1 * _src2
                    _sum = __riscv_vfmacc_vf_f32m4(_sum, _src1, _src2, vl);
                    
                    _psrc1_off++;
                    _psrc2_off += w2;
                }
                // 写入32位浮点数结果（无需类型转换，直接存储）
                __riscv_vse32_v_f32m4(pdst + offset_dst, _sum, vl);
            }
        }
    }
    //sbi_printf("mat_src1->data:%p\n",src1->data);
    //sbi_printf("mat_src2->data:%p\n",src2->data);
    //sbi_printf("mat_dst:%p\n",dst->data);
    //sbi_printf("src1内容:%d\nsrc2内容:%d\ndst内容:%d\n",*((int *)src1->data),*((int *)src2->data),*((int *)dst->data));

    return 0; // 成功返回0
}
/*
只有浮点数模式的matmul
static inline int matmul(Tensor *dst, Tensor *src1, Tensor *src2)
{
    int h1 = src1->shape[0];
    int w1 = src1->shape[1];

    int h2 = src2->shape[0];
    int w2 = src2->shape[1];

    // assert(w1 == h2, "w1 ==h2");
    if(w1 == h2){
      sbi_printf("w1: %d == h2: %d\n",w1,h2);
    }else
      sbi_printf("w1: %d == h2: %d\n",w1,h2);

    int hout = dst->shape[0];
    int wout = dst->shape[1];

    // assert(hout == h1 && wout == w2, "hout == h1 && wout == w2");
    if(hout == h1 && wout == w2){
      sbi_printf("hout: %d == h1: %d && wout:%d == w2: %d\n",hout,h1,wout,w2);
    }else
      sbi_printf("hout: %d == h1: %d && wout: %d == w2: %d\n",hout,h1,wout,w2);

    float16_t *psrc1 = (float16_t *)src1->data;
    float16_t *psrc2 = (float16_t *)src2->data;
    float16_t *pdst = (float16_t *)dst->data;

    int vl = 0;
    for(int i = 0; i < h1; i++) {
        for (int j = 0; j < w2; j += vl) {
            vl = __riscv_vsetvl_e16m4(w2 - j);

            vfloat32m8_t _sum = __riscv_vfmv_v_f_f32m8(0.f, vl);
            int offset_dst = i * w2 + j;
            float16_t *_psrc1_off = psrc1 + i * w1;
            float16_t *_psrc2_off = psrc2 + j;
            for (int k = 0; k < w1; k++) {
                float16_t _src1 = *_psrc1_off;
                vfloat16m4_t _src2 = __riscv_vle16_v_f16m4(_psrc2_off, vl);
                _sum = __riscv_vfwmacc_vf_f32m8(_sum, _src1, _src2, vl);
                _psrc1_off++;
                _psrc2_off += w2;
                sbi_printf("%d\n",*((int *)dst->data+k));
            }
            __riscv_vse16_v_f16m4(pdst+offset_dst, __riscv_vfncvt_f_f_w_f16m4(_sum, vl), vl);
        }
    }

    return 0;
}
*/
static int conv2d(Tensor *dst, Tensor *src, Tensor *weight, sbi_ml_conv_params_t *conv_params)
{
    // Extract tensor dimensions
    int N = src->shape[0];      // batch size
    int H = src->shape[1];      // input height
    int W = src->shape[2];      // input width
    int Cin = src->shape[3];    // input channels

    int KH = weight->shape[0];  // kernel height
    int KW = weight->shape[1];  // kernel width
    int Win = weight->shape[2]; // weight input channels (should equal Cin)
    int Cout = weight->shape[3]; // output channels

    int OH = dst->shape[1];     // output height
    int OW = dst->shape[2];     // output width
    int Cout_dst = dst->shape[3]; // output channels (should equal Cout)

    // Get convolution parameters
    conv_params_t *params = (conv_params_t *)conv_params->params_paddr;
    int stride_h = params->stride_h;
    int stride_w = params->stride_w;
    int pad_h = params->pad_h;
    int pad_w = params->pad_w;
    //int groups = params->groups;

    // Type casting for data access
    float16_t *psrc = (float16_t *)src->data;
    float16_t *pweight = (float16_t *)weight->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Basic validation
    if (Cin != Win || Cout != Cout_dst) {
        sbi_printf("Channel mismatch: Cin=%d, Win=%d, Cout=%d, Cout_dst=%d\n",
                   Cin, Win, Cout, Cout_dst);
        return SBI_EINVAL;
    }

    // Convolution computation
    for (int n = 0; n < N; n++) {           // batch
        for (int cout = 0; cout < Cout; cout++) {  // output channel
            for (int oh = 0; oh < OH; oh++) {      // output height
                for (int ow = 0; ow < OW; ow++) {  // output width
                    float32_t sum = 0.0f;

                    // Accumulate over input channels and kernel spatial dimensions
                    for (int cin = 0; cin < Cin; cin++) {    // input channel
                        for (int kh = 0; kh < KH; kh++) {     // kernel height
                            for (int kw = 0; kw < KW; kw++) {  // kernel width
                                // Calculate input position with padding
                                int ih = oh * stride_h + kh - pad_h;
                                int iw = ow * stride_w + kw - pad_w;

                                // Check bounds
                                if (ih >= 0 && ih < H && iw >= 0 && iw < W) {
                                    // Get input value
                                    int input_idx = ((n * H + ih) * W + iw) * Cin + cin;
                                    float16_t input_val = psrc[input_idx];

                                    // Get weight value
                                    int weight_idx = ((kh * KW + kw) * Cin + cin) * Cout + cout;
                                    float16_t weight_val = pweight[weight_idx];

                                    // Accumulate (convert to float32 for better precision)
                                    sum += (float32_t)input_val * (float32_t)weight_val;
                                }
                            }
                        }
                    }

                    // Store result
                    int output_idx = ((n * OH + oh) * OW + ow) * Cout + cout;
                    pdst[output_idx] = (float16_t)sum;
                }
            }
        }
    }

    return SBI_SUCCESS;
}

// 池化算子
static int pooling(Tensor *dst, Tensor *src, sbi_ml_pool_params_t *pool_params)
{
    int N = src->shape[0];
    int H = src->shape[1];
    int W = src->shape[2];
    int C = src->shape[3];

    int OH = dst->shape[1];
    int OW = dst->shape[2];
    int OC = dst->shape[3];

    pool_params_t *params = (pool_params_t *)pool_params->params_paddr;
    int kh = params->kh;
    int kw = params->kw;
    int stride_h = params->stride_h;
    int stride_w = params->stride_w;
    int pad_h = params->pad_h;
    int pad_w = params->pad_w;

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int oh = 0; oh < OH; oh++) {
                for (int ow = 0; ow < OW; ow++) {
                    if (pool_params->pool_type == SBI_ML_POOL_MAX) {
                        // 最大池化
                        float32_t max_val = MY_FLOAT_NEG_INFINITY;
                        for (int ph = 0; ph < kh; ph++) {
                            for (int pw = 0; pw < kw; pw++) {
                                int ih = oh * stride_h + ph - pad_h;
                                int iw = ow * stride_w + pw - pad_w;
                                if (ih >= 0 && ih < H && iw >= 0 && iw < W) {
                                    int idx = ((n * H + ih) * W + iw) * C + c;
                                    float32_t val = (float32_t)psrc[idx];
                                    if (val > max_val) max_val = val;
                                }
                            }
                        }
                        int out_idx = ((n * OH + oh) * OW + ow) * OC + c;
                        pdst[out_idx] = (float16_t)max_val;
                    } else if (pool_params->pool_type == SBI_ML_POOL_AVG) {
                        // 平均池化
                        float32_t sum = 0.0f;
                        int count = 0;
                        for (int ph = 0; ph < kh; ph++) {
                            for (int pw = 0; pw < kw; pw++) {
                                int ih = oh * stride_h + ph - pad_h;
                                int iw = ow * stride_w + pw - pad_w;
                                if (ih >= 0 && ih < H && iw >= 0 && iw < W) {
                                    int idx = ((n * H + ih) * W + iw) * C + c;
                                    sum += (float32_t)psrc[idx];
                                    count++;
                                }
                            }
                        }
                        float32_t avg_val = count > 0 ? sum / count : 0.0f;
                        int out_idx = ((n * OH + oh) * OW + ow) * OC + c;
                        pdst[out_idx] = (float16_t)avg_val;
                    }
                }
            }
        }
    }
    return SBI_SUCCESS;
}

// 激活函数 - ReLU
/*
static int relu_1(Tensor *src)
{
    int i;
    for (i = 0; i < src->size; i++) {
        src->data[i] = _ReLU(src->data[i]);
    }
    return SBI_SUCCESS;
}*/

static int relu(Tensor *dst, Tensor *src, int use_fxdpt)
{
    int size = src->size;
    if (use_fxdpt) {
        fxdpt_t *psrc = (fxdpt_t *)src->data;
        fxdpt_t *pdst = (fxdpt_t *)dst->data;
        for (int i = 0; i < size; i++) {
            fxdpt_t val = psrc[i];
            pdst[i] = val > 0 ? val : 0;
        }
    } else {
        float16_t *psrc = (float16_t *)src->data;
        float16_t *pdst = (float16_t *)dst->data;
        for (int i = 0; i < size; i++) {
            float32_t val = (float32_t)psrc[i];
            float32_t relu_val = val > 0 ? val : 0;
            pdst[i] = (float16_t)relu_val;
        }
    }

    return SBI_SUCCESS;
}

// 激活函数 - Sigmoid
static int sigmoid(Tensor *dst, Tensor *src)
{
    int size = src->size;
    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    for (int i = 0; i < size; i++) {
        float32_t val = (float32_t)psrc[i];
        float32_t sigmoid_val = 1.0f / (1.0f + my_expf(-val));
        pdst[i] = (float16_t)sigmoid_val;
    }
    return SBI_SUCCESS;
}

// 激活函数 - Tanh
static int tanh_activation(Tensor *dst, Tensor *src)
{
    int size = src->size;
    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    for (int i = 0; i < size; i++) {
        float32_t val = (float32_t)psrc[i];
        float32_t tanh_val = my_tanhf(val);
        pdst[i] = (float16_t)tanh_val;
    }
    return SBI_SUCCESS;
}
static int softmax(Tensor *dst, Tensor *src)
{
    int size = src->size;
    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Find max value for numerical stability
    float32_t max_val = MY_FLOAT_NEG_INFINITY;
    for (int i = 0; i < size; i++) {
        float32_t val = (float32_t)psrc[i];
        if (val > max_val) max_val = val;
    }

    // Compute exponentials and sum
    float32_t sum = 0.0f;
    for (int i = 0; i < size; i++) {
        float32_t val = (float32_t)psrc[i];
        float32_t exp_val = my_expf(val - max_val);
        pdst[i] = (float16_t)exp_val;
        sum += exp_val;
    }

    // Normalize
    for (int i = 0; i < size; i++) {
        float32_t val = (float32_t)pdst[i];
        pdst[i] = (float16_t)(val / sum);
    }

    return SBI_SUCCESS;
}
// Softmax


// 全连接层
static int fully_connected(Tensor *dst, Tensor *src, Tensor *weight, Tensor *bias)
{
    int batch_size = src->shape[0];
    int input_size = src->shape[1];  // Assuming 2D tensor [batch, input_size]
    int output_size = dst->shape[1]; // Assuming 2D tensor [batch, output_size]

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pweight = (float16_t *)weight->data;
    float16_t *pbias = bias ? (float16_t *)bias->data : NULL;
    float16_t *pdst = (float16_t *)dst->data;

    for (int b = 0; b < batch_size; b++) {
        for (int o = 0; o < output_size; o++) {
            float32_t sum = 0.0f;
            for (int i = 0; i < input_size; i++) {
                int src_idx = b * input_size + i;
                int weight_idx = o * input_size + i;
                sum += (float32_t)psrc[src_idx] * (float32_t)pweight[weight_idx];
            }
            if (pbias) {
                sum += (float32_t)pbias[o];
            }
            int dst_idx = b * output_size + o;
            pdst[dst_idx] = (float16_t)sum;
        }
    }

    return SBI_SUCCESS;
}

// 张量加法
static int tensor_add(Tensor *dst, Tensor *src1, Tensor *src2, int use_fxdpt)
{
    if (src1->size != src2->size || src1->size != dst->size) {
        return SBI_EINVAL;
    }

    int size = src1->size;
    if (use_fxdpt) {
        //sbi_printf("add_src1->data:%p\n",src1->data);
        //sbi_printf("add_src2->data:%p\n",src2->data);
        //sbi_printf("add_dst->data:%p\n",dst->data);
        fxdpt_t *psrc1 = (fxdpt_t *)src1->data;
        fxdpt_t *psrc2 = (fxdpt_t *)src2->data;
        fxdpt_t *pdst = (fxdpt_t *)dst->data;
        for (int i = 0; i < size; i++) {
            fxdpt_t val = psrc1[i] + psrc2[i];
            pdst[i] = val;
        }
    } else {
        float32_t *psrc1 = (float32_t *)src1->data;
        float32_t *psrc2 = (float32_t *)src2->data;
        float32_t *pdst = (float32_t *)dst->data;
        for (int i = 0; i < size; i++) {
            float32_t val = psrc1[i] + psrc2[i];
            pdst[i] = val;
        }
    }

    return SBI_SUCCESS;
}

// 张量减法
static int tensor_sub(Tensor *dst, Tensor *src1, Tensor *src2, int use_fxdpt)
{
    if (src1->size != src2->size || src1->size != dst->size) {
        return SBI_EINVAL;
    }

    int size = src1->size;
    if (use_fxdpt == 1) {
        fxdpt_t *psrc1 = (fxdpt_t *)src1->data;
        fxdpt_t *psrc2 = (fxdpt_t *)src2->data;
        fxdpt_t *pdst = (fxdpt_t *)dst->data;
        for (int i = 0; i < size; i++) {
            fxdpt_t val = psrc1[i] - psrc2[i];
            pdst[i] = val;
        }
    } else {
        float32_t *psrc1 = (float32_t *)src1->data;
        float32_t *psrc2 = (float32_t *)src2->data;
        float32_t *pdst = (float32_t *)dst->data;
        for (int i = 0; i < size; i++) {
            float32_t val = psrc1[i] - psrc2[i];
            pdst[i] = val;
        }
    }
    return SBI_SUCCESS;
}

// 张量变换 - Crop
static int tensor_crop(Tensor *dst, Tensor *src, tensor_transform_params_t *params)
{
    int start_n = params->start[0];
    int start_h = params->start[1];
    int start_w = params->start[2];
    int start_c = params->start[3];

    int end_n = params->end[0];
    int end_h = params->end[1];
    int end_w = params->end[2];
    int end_c = params->end[3];

    int crop_n = end_n - start_n;
    int crop_h = end_h - start_h;
    int crop_w = end_w - start_w;
    int crop_c = end_c - start_c;

    // Validate dimensions
    if (crop_n != dst->shape[0] || crop_h != dst->shape[1] ||
        crop_w != dst->shape[2] || crop_c != dst->shape[3]) {
        return SBI_EINVAL;
    }

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    //int src_n = src->shape[0];
    int src_h = src->shape[1];
    int src_w = src->shape[2];
    int src_c = src->shape[3];

    for (int n = 0; n < crop_n; n++) {
        for (int h = 0; h < crop_h; h++) {
            for (int w = 0; w < crop_w; w++) {
                for (int c = 0; c < crop_c; c++) {
                    int src_idx = ((start_n + n) * src_h + (start_h + h)) * src_w + (start_w + w) * src_c + (start_c + c);
                    int dst_idx = ((n * crop_h + h) * crop_w + w) * crop_c + c;
                    pdst[dst_idx] = psrc[src_idx];
                }
            }
        }
    }

    return SBI_SUCCESS;
}

// 张量变换 - Reshape
static int tensor_reshape(Tensor *dst, Tensor *src)
{
    if (src->size != dst->size) {
        return SBI_EINVAL;
    }

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Simple memcpy since total size is the same
    for (int i = 0; i < src->size; i++) {
        pdst[i] = psrc[i];
    }

    return SBI_SUCCESS;
}

// 张量变换 - Slice
static int tensor_slice(Tensor *dst, Tensor *src, tensor_transform_params_t *params)
{
    int axis = params->axis;
    int start = params->start[axis];
    int end = params->end[axis];

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Calculate slice size and copy data
    int slice_size = 1;
    for (int i = axis + 1; i < 4; i++) {
        slice_size *= src->shape[i];
    }

    int slice_count = end - start;
    int total_slices_before = start * slice_size;
    //int total_slices_after = (src->shape[axis] - end) * slice_size;

    // Copy the sliced data
    for (int i = 0; i < slice_count * slice_size; i++) {
        pdst[i] = psrc[total_slices_before + i];
    }

    return SBI_SUCCESS;
}

// 张量变换 - Concat
static int tensor_concat(Tensor *dst, tensor_transform_params_t *params)
{
    //int axis = params->axis;
    int num_tensors = params->num_tensors;
    
    Tensor **tensor_list = (Tensor **)params->tensor_list_paddr;
    
    float16_t *pdst = (float16_t *)dst->data;

    int offset = 0;
    for (int t = 0; t < num_tensors; t++) {
        Tensor *src = tensor_list[t];
        float16_t *psrc = (float16_t *)src->data;
        int copy_size = src->size;

        for (int i = 0; i < copy_size; i++) {
            pdst[offset + i] = psrc[i];
        }
        offset += copy_size;
    }

    return SBI_SUCCESS;
}

// ROIPooling
static int roi_pooling(Tensor *dst, Tensor *src, roipool_params_t *params)
{
    int roi_num = params->roi_num;
    float *roi_coords = (float *)params->roi_paddr;
    int pool_h = params->pool_size_h;
    int pool_w = params->pool_size_w;
    float spatial_scale = params->spatial_scale;

    //int N = src->shape[0];
    int H = src->shape[1];
    int W = src->shape[2];
    int C = src->shape[3];

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    for (int roi = 0; roi < roi_num; roi++) {
        float x1 = roi_coords[roi * 4 + 0] * spatial_scale;
        float y1 = roi_coords[roi * 4 + 1] * spatial_scale;
        float x2 = roi_coords[roi * 4 + 2] * spatial_scale;
        float y2 = roi_coords[roi * 4 + 3] * spatial_scale;

        int roi_width = (int)(x2 - x1 + 1.0f);
        int roi_height = (int)(y2 - y1 + 1.0f);

        float bin_size_h = (float)roi_height / (float)pool_h;
        float bin_size_w = (float)roi_width / (float)pool_w;

        for (int c = 0; c < C; c++) {
            for (int ph = 0; ph < pool_h; ph++) {
                for (int pw = 0; pw < pool_w; pw++) {
                    // Define the spatial bin
                    float hstart = y1 + ph * bin_size_h;
                    float wstart = x1 + pw * bin_size_w;
                    float hend = y1 + (ph + 1) * bin_size_h;
                    float wend = x1 + (pw + 1) * bin_size_w;

                    // Clamp to image boundaries
                    hstart = hstart < 0 ? 0 : hstart;
                    wstart = wstart < 0 ? 0 : wstart;
                    hend = hend > H - 1 ? H - 1 : hend;
                    wend = wend > W - 1 ? W - 1 : wend;

                    // Max pooling within the bin
                    float32_t max_val = MY_FLOAT_NEG_INFINITY;
                    for (int h = (int)hstart; h <= (int)hend; h++) {
                        for (int w = (int)wstart; w <= (int)wend; w++) {
                            int idx = (0 * H + h) * W * C + w * C + c; // Assuming batch=0
                            float32_t val = (float32_t)psrc[idx];
                            if (val > max_val) max_val = val;
                        }
                    }

                    int out_idx = (roi * pool_h * pool_w * C) + ph * pool_w * C + pw * C + c;
                    pdst[out_idx] = (float16_t)max_val;
                }
            }
        }
    }

    return SBI_SUCCESS;
}

// Proposal (简化的实现)
/*static int proposal(Tensor *dst, proposal_params_t *params)
{
    // This is a simplified implementation
    // In a real implementation, this would involve:
    // 1. Generate anchor boxes
    // 2. Apply deltas from RPN
    // 3. Clip to image boundaries
    // 4. Remove small boxes
    // 5. Apply NMS

    sbi_printf("Proposal operation called - simplified implementation\n");
    return SBI_SUCCESS;
}*/


// Proposal 算子（简化的实现）
static int proposal(Tensor *dst, proposal_params_t *params)
{
    // 1. 严格入参检查（避免空指针访问）
    if (dst == NULL || dst->data == NULL) {
        return SBI_EINVAL; // 输出Tensor为空
    }
    if (params == NULL) {
        return SBI_EINVAL; // 参数结构体为空
    }

    // 2. 读取结构体字段
    // 核心用到的字段：post_nms_topN（控制生成数量）
    int post_nms_topN = params->post_nms_topN;
    
    // 其他字段：若需保留则标记为已使用（避免编译器警告），无需则可删除
    (void)params->feat_stride;      // 占位，标记变量已使用
    (void)params->anchor_scales;    // 占位（数组需整体标记）
    (void)params->rpn_nms_thresh;   // 占位
    (void)params->pre_nms_topN;     // 占位
    (void)params->min_size;         // 占位

    // 3. 确定生成的候选框数量
    int num_proposals = post_nms_topN > 0 ? post_nms_topN : 1000;
    float16_t *pdst = (float16_t *)dst->data;

    // 4. 生成简化的候选框 [x1, y1, x2, y2, score]（测试用假数据）
    for (int i = 0; i < num_proposals; i++) {
        // 生成0-1范围内的示例坐标（无实际物理意义，仅测试格式）
        float x1 = 0.1f * (i % 10);            // x1: 0.0,0.1,...,0.9循环
        float y1 = 0.1f * ((i / 10) % 10);     // y1: 每10个循环一次
        float x2 = x1 + 0.2f;                  // 框宽度固定0.2
        float y2 = y1 + 0.2f;                  // 框高度固定0.2
        float score = 0.9f - (i * 0.001f);     // 分数从0.9递减

        // 写入输出Tensor（每个候选框占5个float16元素）
        int base_idx = i * 5;
        pdst[base_idx + 0] = (float16_t)x1;
        pdst[base_idx + 1] = (float16_t)y1;
        pdst[base_idx + 2] = (float16_t)x2;
        pdst[base_idx + 3] = (float16_t)y2;
        pdst[base_idx + 4] = (float16_t)score;
    }

    // 5. 返回成功
    return SBI_SUCCESS;
}
// Basic RNN
static int basic_rnn(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params)
{
    rnn_params_t *rnn_params = (rnn_params_t *)params->params_paddr;

    int batch_size = src->shape[0];
    int seq_len = src->shape[1];
    int input_size = rnn_params->input_size;
    int hidden_size = rnn_params->hidden_size;

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Simplified RNN implementation
    for (int b = 0; b < batch_size; b++) {
        for (int t = 0; t < seq_len; t++) {
            for (int h = 0; h < hidden_size; h++) {
                float32_t sum = 0.0f;
                for (int i = 0; i < input_size; i++) {
                    int src_idx = b * seq_len * input_size + t * input_size + i;
                    sum += (float32_t)psrc[src_idx];
                }
                // Apply tanh activation
                float32_t rnn_out = my_tanhf(sum / input_size);
                int dst_idx = b * seq_len * hidden_size + t * hidden_size + h;
                pdst[dst_idx] = (float16_t)rnn_out;
            }
        }
    }

    return SBI_SUCCESS;
}
// LSTM (简化的单层实现)
static int lstm(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params)
{
    rnn_params_t *rnn_params = (rnn_params_t *)params->params_paddr;

    int batch_size = src->shape[0];
    int seq_len = src->shape[1];
    int input_size = rnn_params->input_size;
    int hidden_size = rnn_params->hidden_size;

    float16_t *psrc = (float16_t *)src->data;
    float16_t *pdst = (float16_t *)dst->data;

    // Simplified LSTM implementation
    // In a real implementation, this would include proper LSTM gates and states

    for (int b = 0; b < batch_size; b++) {
        for (int t = 0; t < seq_len; t++) {
            for (int h = 0; h < hidden_size; h++) {
                float32_t sum = 0.0f;
                for (int i = 0; i < input_size; i++) {
                    int src_idx = b * seq_len * input_size + t * input_size + i;
                    // Simplified: just copy input to output
                    sum += (float32_t)psrc[src_idx];
                }
                int dst_idx = b * seq_len * hidden_size + t * hidden_size + h;
                pdst[dst_idx] = (float16_t)(sum / input_size);
            }
        }
    }

    return SBI_SUCCESS;
}


static int sbi_ecall_ml_handler(unsigned long extid, unsigned long funcid,
				    struct sbi_trap_regs *regs,
				    struct sbi_ecall_return *out)
{
    out->skip_regs_update = false;
    out->value = 0;

    int ret = SBI_SUCCESS;
	switch (funcid) {
        case SBI_EXT_ML_MATMUL: {
            //sbi_printf("matmul\n");
            Tensor *dst =(Tensor *)regs->a0;
            Tensor *src1 =(Tensor *)regs->a1;
            Tensor *src2 =(Tensor *)regs->a2;
            int use_fxdpt = (int)regs->a3;
            // out->value=regs->a0+regs->a1;
            ret=matmul(dst,src1,src2,use_fxdpt);
            break;
        }
        case SBI_EXT_ML_CONV: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            Tensor *weight = (Tensor *)regs->a2;
            sbi_ml_conv_params_t *params = (sbi_ml_conv_params_t *)regs->a3;
            ret = conv2d(dst, src, weight, params);
            break;
        }
        case SBI_EXT_ML_POOLING: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            sbi_ml_pool_params_t *params = (sbi_ml_pool_params_t *)regs->a2;
            ret = pooling(dst, src, params);
            break;
        }
        case SBI_EXT_ML_RELU: {
            //sbi_printf("relu\n");
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            int use_fxdpt = (int)regs->a2;
            ret = relu(dst, src, use_fxdpt);
            break;
        }
        case SBI_EXT_ML_SIGMOID: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            ret = sigmoid(dst, src);
            break;
        }
        case SBI_EXT_ML_TANH: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            ret = tanh_activation(dst, src);
            break;
        }
        case SBI_EXT_ML_SOFTMAX: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            ret = softmax(dst, src);
            break;
        }
        case SBI_EXT_ML_FC: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            Tensor *weight = (Tensor *)regs->a2;
            Tensor *bias = (Tensor *)regs->a3;
            ret = fully_connected(dst, src, weight, bias);
            break;
        }
        case SBI_EXT_ML_TENSOR_ADD: {
            //sbi_printf("add\n");
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src1 = (Tensor *)regs->a1;
            Tensor *src2 = (Tensor *)regs->a2;
            int use_fxdpt = (int)regs->a3;
            ret = tensor_add(dst, src1, src2, use_fxdpt);
            break;
        }
        case SBI_EXT_ML_TENSOR_SUB: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src1 = (Tensor *)regs->a1;
            Tensor *src2 = (Tensor *)regs->a2;
            int use_fxdpt = (int)regs->a3;
            ret = tensor_sub(dst, src1, src2, use_fxdpt);
            break;
        }
        case SBI_EXT_ML_TENSOR_TRANSFORM_CROP: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            tensor_transform_params_t *params = (tensor_transform_params_t *)regs->a2;
            ret = tensor_crop(dst, src, params);
            break;
        }
        case SBI_EXT_ML_TENSOR_TRANSFORM_RESHAPE: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            ret = tensor_reshape(dst, src);
            break;
        }
        case SBI_EXT_ML_TENSOR_TRANSFORM_SLICE: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            tensor_transform_params_t *params = (tensor_transform_params_t *)regs->a2;
            ret = tensor_slice(dst, src, params);
            break;
        }
        case SBI_EXT_ML_TENSOR_TRANSFORM_CONCAT: {
            Tensor *dst = (Tensor *)regs->a0;
            tensor_transform_params_t *params = (tensor_transform_params_t *)regs->a1;
            ret = tensor_concat(dst, params);
            break;
        }
        case SBI_EXT_ML_ROIPOOLING: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            roipool_params_t *params = (roipool_params_t *)regs->a2;
            ret = roi_pooling(dst, src, params);
            break;
        }
        case SBI_EXT_ML_PROPOSAL: {
            Tensor *dst = (Tensor *)regs->a0;
            proposal_params_t *params = (proposal_params_t *)regs->a1;
            ret = proposal(dst, params);
            break;
        }
        case SBI_EXT_ML_LSTM: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            sbi_ml_recurrent_params_t *params = (sbi_ml_recurrent_params_t *)regs->a2;
            ret = lstm(dst, src, params);
            break;
        }
        case SBI_EXT_ML_BASICRNN: {
            Tensor *dst = (Tensor *)regs->a0;
            Tensor *src = (Tensor *)regs->a1;
            sbi_ml_recurrent_params_t *params = (sbi_ml_recurrent_params_t *)regs->a2;
            ret = basic_rnn(dst, src, params);
            break;
        }
	}
    out->value = SBI_ML_SET_ERR(0, ret);
	return 0;
}

struct sbi_ecall_extension ecall_ml;

static int sbi_ecall_ml_register_extensions(void)
{
	return sbi_ecall_register_extension(&ecall_ml);
}

struct sbi_ecall_extension ecall_ml = {
	.name			= "ml",
	.extid_start		= SBI_EXT_ML,
	.extid_end		= SBI_EXT_ML,
	.register_extensions	= sbi_ecall_ml_register_extensions,
	.handle			= sbi_ecall_ml_handler,
};
