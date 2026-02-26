#ifndef _SBI_ML_H_
#define _SBI_ML_H_

#define VLEN  (read_csr(vlenb) * 8)
#define VLENB  (read_csr(vlenb))
typedef _Float16 float16_t;

typedef float float32_t;
typedef double float64_t;

#define CACHELINE 64

typedef struct {
  void *data;
  int shape[4]; // Feature Map: [N, H, W, C], Weight: [H, W, Cin, Cout]
  int size;
} Tensor;

#define create_tensor2d(_name, _data, d1, d2)                                  \
  Tensor _name = {                                                             \
      .data = (void *)_data, .shape = {1, d1, d2, 1}, .size = (d1 * d2)}

#define create_tensor3d(_name, _data, d1, d2, d3)                              \
  Tensor _name = {                                                             \
      .data = (void *)_data, .shape = {1, d1, d2, d3}, .size = (d1 * d2 * d3)}

#define create_tensor4d(_name, _data, d1, d2, d3, d4)                          \
  Tensor _name = {.data = (void *)_data,                                       \
                  .shape = {d1, d2, d3, d4},                                   \
                  .size = (d1 * d2 * d3 * d4)}

#define INCBIN(var, binfile, section)                                          \
  __asm__(".section " section ", \"a\", @progbits\n\t"                         \
          ".type " #var ", @object\n\t"                                        \
          ".global " #var "\n\t"                                               \
          ".align 8\n" #var ":\n\t"                                            \
          ".incbin \"" binfile "\""                                            \
          "\n\t"                                                               \
          ".align 8\n")

typedef struct {
  unsigned long bias_paddr;    // 偏置张量的物理地址（如果没有偏置，则为 0）
  unsigned long params_paddr;  // 存储步幅（stride）、填充（padding）、扩张（dilation）、组（groups）等参数的结构体的物理地址
} sbi_ml_conv_params_t;

typedef enum { SBI_ML_POOL_MAX=0, SBI_ML_POOL_AVG=1 } sbi_ml_pool_type_t;
typedef struct {
  sbi_ml_pool_type_t pool_type; // 池化类型（最大池化或平均池化）
  unsigned long params_paddr;   // 存储池化参数（如核大小、步幅、填充等）的结构体的物理地址
} sbi_ml_pool_params_t;

typedef struct {
  unsigned long states_in_paddr;  // 输入状态（如 h_init, c_init）的结构体的物理地址
  unsigned long states_out_paddr; // 输出状态（如 h_final, c_final）应写入的结构体的物理地址
  unsigned long params_paddr;     // 存储权重、偏置和其他配置（如双向性）的结构体的物理地址
} sbi_ml_recurrent_params_t;

// ========== 新增：Tensor变换参数结构体（Crop/Slice/Concat） ==========
typedef struct {
    int start[4];  // 起始坐标 [N, H, W, C]
    int end[4];    // 结束坐标 [N, H, W, C]
    int axis;      // 切片/拼接维度（仅Slice/Concat用）
    int num_tensors; // 拼接的Tensor数量（仅Concat用）
    unsigned long *tensor_list_paddr; // 拼接的Tensor数组物理地址（仅Concat用）
} tensor_transform_params_t;

// ========== 新增：ROIPooling参数结构体 ==========
typedef struct {
    int roi_num;          // ROI数量
    unsigned long roi_paddr; // ROI坐标数组（每个ROI：x1,y1,x2,y2）
    int pool_size_h;      // 池化核高度
    int pool_size_w;      // 池化核宽度
    float spatial_scale;  // 空间缩放因子（ROI坐标→特征图坐标）
} roipool_params_t;

// ========== 新增：Proposal参数结构体 ==========
typedef struct {
    int feat_stride;      // 特征图步长（如16）
    int anchor_scales[3]; // 锚点缩放尺度（如8,16,32）
    float rpn_nms_thresh; // NMS阈值
    int pre_nms_topN;     // NMS前保留的框数量
    int post_nms_topN;    // NMS后保留的框数量
    float min_size;       // 最小框尺寸
} proposal_params_t;

// ========== 新增：RNN/LSTM参数结构体 ==========
typedef struct {
    Tensor *weight_ih; // 输入→隐藏层权重 [hidden_size, input_size]
    Tensor *weight_hh; // 隐藏层→隐藏层权重 [hidden_size, hidden_size]
    Tensor *bias_ih;   // 输入偏置 [hidden_size]
    Tensor *bias_hh;   // 隐藏层偏置 [hidden_size]
    int input_size;    // 输入维度
    int hidden_size;   // 隐藏层维度
    int num_layers;    // 层数（简化为1层）
    int bidirectional; // 是否双向（0/1）
} rnn_params_t;

// ========== 新增：卷积参数补充（原sbi_ml_conv_params_t仅声明指针，补充具体结构） ==========
typedef struct {
    int stride_h;
    int stride_w;
    int pad_h;
    int pad_w;
    int groups;
} conv_params_t;

// ========== 新增：池化参数补充（原sbi_ml_pool_params_t仅声明指针，补充具体结构） ==========
typedef struct {
    int kh;
    int kw;
    int stride_h;
    int stride_w;
    int pad_h;
    int pad_w;
} pool_params_t;

typedef struct {
    Tensor *input;      // 输入
    Tensor *W1;         // 第一层权重
    Tensor *B1;         // 第一层偏置
    Tensor *out1;       // 第一层输出
    Tensor *W2;         // 第二层权重
    Tensor *B2;         // 第二层偏置
    Tensor *out2;       // 最终输出
    int use_fxdpt;      // 是否使用定点数
} mlp_forward_params_t;

// 定点数核心定义
typedef int fxdpt_t;       // 等价于int32_t（RV32 M-mode）
typedef signed long fxdpt_ext;// 等价于int64_t（RV32 M-mode）
#define FXDPT_FBITS 11
#define FXDPT_ONE ((fxdpt_t)((fxdpt_t)1 << FXDPT_FBITS))

// 定点数运算宏
#define float_to_fxdpt(F) ((fxdpt_t)((F) * FXDPT_ONE + ((F) >= 0? 0.5 : -0.5)))
#define int_to_fxdpt(F) ((fxdpt_t)((F) * FXDPT_ONE))
#define fxdpt_mul(A, B) ((fxdpt_t)(((fxdpt_ext)(A) * (fxdpt_ext)(B)) >> FXDPT_FBITS))
#define fxdpt_div(A, B) ((fxdpt_t)(((fxdpt_ext)(A) * FXDPT_ONE) / (B)))
#define tofloat(T) ((float) ((T)*((float)(1)/(float)(1L << FXDPT_FBITS))))

// 32位浮点数运算宏（对齐S-mode的float）
#define float32_mul(A, B) ((A) * (B))
#define float32_div(A, B) ((A) / (B))

#endif // _SBI_ML_H_