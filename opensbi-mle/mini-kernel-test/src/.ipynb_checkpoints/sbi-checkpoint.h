/* mostly come from riscv-spi document */
#ifndef _SBI_H
#define _SBI_H


#define SBI_SET_TIMER 0
#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_CLEAR_IPI 3
#define SBI_SEND_IPI 4
#define SBI_REMOTE_FENCE_I 5
#define SBI_REMOTE_SFENCE_VMA 6
#define SBI_REMOTE_SFENCE_VMA_ASID 7
#define SBI_SHUTDOWN 8

#define SBI_ECALL(__num, __a0, __a1, __a2)                           \
({                                                                  \
    register unsigned long a0 asm("a0") = (unsigned long)(__a0);    \
    register unsigned long a1 asm("a1") = (unsigned long)(__a1);    \
    register unsigned long a2 asm("a2") = (unsigned long)(__a2);    \
    register unsigned long a7 asm("a7") = (unsigned long)(__num);   \
    asm volatile("ecall"                                            \
                 : "+r"(a0)                                         \
                 : "r"(a1), "r"(a2), "r"(a7)                        \
                 : "memory");                                       \
    a0;                                                             \
})

#define SBI_ECALL_0(__num) SBI_ECALL(__num, 0, 0, 0)
#define SBI_ECALL_1(__num, __a0) SBI_ECALL(__num, __a0, 0, 0)
#define SBI_ECALL_2(__num, __a0, __a1) SBI_ECALL(__num, __a0, __a1, 0)

#define SBI_PUTCHAR(__a0) SBI_ECALL_1(SBI_CONSOLE_PUTCHAR, __a0)
#define SBI_TIMER(__a0) SBI_ECALL_1(SBI_SET_TIMER, __a0)
void shutdown(){
    SBI_ECALL_0(SBI_SHUTDOWN);
}
int putchar(int c);
int puts(const char *s);
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_string.h>
#define ML_TEST

#ifdef ML_TEST
#include <sbi/sbi_ml.h>
struct sbiret {
	unsigned long error;
	unsigned long value;
};

struct sbiret sbi_ecall(int ext, int fid, unsigned long arg0,
			unsigned long arg1, unsigned long arg2,
			unsigned long arg3, unsigned long arg4,
			unsigned long arg5)
{
	struct sbiret ret;

	register unsigned long a0 asm ("a0") = (unsigned long)(arg0);
	register unsigned long a1 asm ("a1") = (unsigned long)(arg1);
	register unsigned long a2 asm ("a2") = (unsigned long)(arg2);
	register unsigned long a3 asm ("a3") = (unsigned long)(arg3);
	register unsigned long a4 asm ("a4") = (unsigned long)(arg4);
	register unsigned long a5 asm ("a5") = (unsigned long)(arg5);
	register unsigned long a6 asm ("a6") = (unsigned long)(fid);
	register unsigned long a7 asm ("a7") = (unsigned long)(ext);
	asm volatile ("ecall"
		      : "+r" (a0), "+r" (a1)
		      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
		      : "memory");
	ret.error = a0;
	ret.value = a1;

	return ret;
}

#define FXDPT_FBITS 11

/* Can't left shift negative int */
/* Add 0.5/-0.5 to round to nearest int  */
#define FXDPT_ONE ((fxdpt_t)((fxdpt_t)1 << FXDPT_FBITS))
#define float_to_fxdpt(F) ((fxdpt_t)((F) * FXDPT_ONE + ((F) >= 0? 0.5 : -0.5)))
#define int_to_fxdpt(F) ((fxdpt_t)((F) * FXDPT_ONE))
/* Extend to double length to avoid overflow */
#define fxdpt_mul(A, B)        \
    ((fxdpt_t)(((fxdpt_ext)(A) * (fxdpt_ext)(B)) >> FXDPT_FBITS))
#define fxdpt_div(A, B)                       \
    ((fxdpt_t)(((fxdpt_ext)(A) * FXDPT_ONE) / (B)))

#define tofloat(T) ((float) ((T)*((float)(1)/(float)(1L << FXDPT_FBITS))))

#define dtype               fxdpt_t
#define ftodtype(F)         float_to_fxdpt(F)
#define itodtype(F)         int_to_fxdpt(F)
#define todtype(F)          itodtype(F)
#define dtype_mul(A, B)     fxdpt_mul(A, B)
#define dtype_div(A, B)     fxdpt_div(A, B)


static inline void sbi_ecall_console_puts(const char *str)
{
	sbi_ecall(SBI_EXT_DBCN, SBI_EXT_DBCN_CONSOLE_WRITE,
		  sbi_strlen(str), (unsigned long)str, 0, 0, 0, 0);
}


static inline struct sbiret sbi_ecall_ml_test(int a, int b)
{
	return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
		  a, b, 0, 0, 0, 0);
}

static inline struct sbiret matmul(Tensor *dst, Tensor *src1, Tensor *src2,int use_fxdpt){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
		  (unsigned long)dst, (unsigned long)src1, (unsigned long)src2, (unsigned long)use_fxdpt, 0, 0);
}

static inline struct sbiret tensor_add(Tensor *dst, Tensor *src1, Tensor *src2,int use_fxdpt){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_ADD,(unsigned long)dst,(unsigned long)src1,(unsigned long)src2, (unsigned long)use_fxdpt,0,0);
}

static inline struct sbiret tensor_sub(Tensor *dst, Tensor *src1, Tensor *src2,int use_fxdpt){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_SUB,(unsigned long)dst,(unsigned long)src1,(unsigned long)src2,(unsigned long)use_fxdpt,0,0);
}

static inline struct sbiret tensor_crop(Tensor *dst, Tensor *src, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_TRANSFORM_CROP,(unsigned long)dst,(unsigned long)src,(unsigned long)params,0, 0, 0);
}

static inline struct sbiret tensor_reshape(Tensor *dst, Tensor *src){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_RESHAPE,(unsigned long)dst, (unsigned long)src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_slice(Tensor *dst, Tensor *src, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_SLICE,(unsigned long)dst, (unsigned long)src, (unsigned long)params, 0, 0, 0);
}

static inline struct sbiret tensor_concat(Tensor *dst, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_CONCAT,(unsigned long)dst, (unsigned long)params, 0, 0, 0, 0);
}

static inline struct sbiret tensor_matmul(Tensor *dst, Tensor *src1,Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,(unsigned long)dst, (unsigned long)src1,(unsigned long)src2, 0, 0, 0);
}

static inline struct sbiret tensor_relu(Tensor *dst, Tensor *src,int use_fxdpt) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_RELU,(unsigned long)dst, (unsigned long)src, (unsigned long)use_fxdpt, 0, 0, 0);
}

static inline struct sbiret tensor_sigmoid(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SIGMOID,(unsigned long)dst, (unsigned long)src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_tanh(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TANH,(unsigned long)dst, (unsigned long)src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_softmax(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SOFTMAX,(unsigned long)dst, (unsigned long)src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_conv2d(Tensor *dst, Tensor *src, Tensor *weight, sbi_ml_conv_params_t *conv_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_CONV,(unsigned long)dst,(unsigned long)src,(unsigned long)weight,(unsigned long)conv_params,0, 0 );
}

static inline struct sbiret tensor_fully_connected(Tensor *dst, Tensor *src, Tensor *weight, Tensor *bias) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_FC,(unsigned long)dst,(unsigned long)src,(unsigned long)weight,(unsigned long)bias,0,0);
}

static inline struct sbiret tensor_pooling(Tensor *dst, Tensor *src, sbi_ml_pool_params_t *pool_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_POOLING,(unsigned long)dst,(unsigned long)src,(unsigned long)pool_params,0, 0, 0);
}

static inline struct sbiret tensor_basic_rnn(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params) {
    return sbi_ecall( SBI_EXT_ML,SBI_EXT_ML_BASICRNN,(unsigned long)dst,(unsigned long)src,(unsigned long)params,0, 0, 0);
}

static inline struct sbiret tensor_basic_lstm(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_LSTM, (unsigned long)dst, (unsigned long)src, (unsigned long)params, 0, 0, 0);
}

static inline struct sbiret tensor_basic_roipooling(Tensor *dst, Tensor *src, roipool_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_ROIPOOLING, (unsigned long)dst, (unsigned long)src, (unsigned long)params, 0, 0, 0);
}

static inline struct sbiret tensor_basic_proposal(Tensor *dst, proposal_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_PROPOSAL,
                    (unsigned long)dst, (unsigned long)params,
                    0, 0, 0, 0);      
}           
#define wfi()                                             \
	do {                                              \
		__asm__ __volatile__("wfi" ::: "memory"); \
	} while (0)


// For ML
#include <memory.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <stdio.h>
typedef _Float16 fp16_t;
typedef float fp32_t;
typedef double fp64_t;

static int test_cases = 0;
static int pass_cases = 0;

#define EXCEPT_ARRAY_LAX_EQ_BASE(arr1, arr2, len, type, format, name)          \
  do {                                                                         \
    test_cases++;                                                              \
    int i;                                                                     \
    type *casted_arr1 = (type *)(arr1);                                        \
    type *casted_arr2 = (type *)(arr2);                                        \
    for (i = 0; i < (len); ++i) {                                              \
      if ((casted_arr1[i] - casted_arr2[i] > 1e-1) ||                          \
          (casted_arr1[i] - casted_arr2[i] < -1e-1)) {                         \
          sbi_ecall_console_puts("error\n");\
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    if (i == (len)) {                                                          \
      pass_cases++;                                                            \
      sbi_ecall_console_puts("PASS\n");                 \
    }                                                                          \
  } while (0);

#define EXCEPT_FP32_ARRAY_LAX_EQ(arr1, arr2, len, name)                        \
  EXCEPT_ARRAY_LAX_EQ_BASE(arr1, arr2, len, fp32_t, "%f", name)
#endif
#include <riscv_vector.h>

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

#endif
