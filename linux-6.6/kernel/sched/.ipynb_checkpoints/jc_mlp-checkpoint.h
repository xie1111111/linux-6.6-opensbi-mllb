#ifndef _SCHED_JC_MLP_H
#define _SCHED_JC_MLP_H

#define SBI_SET_TIMER 0
#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_CLEAR_IPI 3
#define SBI_SEND_IPI 4
#define SBI_REMOTE_FENCE_I 5
#define SBI_REMOTE_SFENCE_VMA 6
#define SBI_REMOTE_SFENCE_VMA_ASID 7
#define SBI_SHUTDOWN 8

#include <linux/sched.h>
#include <asm/sbi.h>
#include "jc_sbi_ml.h"

extern int is_jc_sched;

struct jc_lb_data {
    int src_non_pref;
    int delta_hot;
    int cpu_idle;
    int cpu_not_idle;
    int cpu_newly_idle;
    int same_node;
    int prefer_src;
    int prefer_dst;
    int src_len;
    unsigned long src_load;
    unsigned long dst_load;
    int dst_len;
    long delta_faults;
    int extra_fails;
    int buddy_hot;
    unsigned long total_faults;
};

int jc_mlp_main(struct jc_lb_data *data);

void jc_mlp_perf_init_early(void);

#ifdef CONFIG_JC_SCHED_FXDPT
typedef s32 fxdpt_t;
typedef s64 fxdpt_ext;

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

static inline struct sbiret matmul(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
        __pa(dst), __pa(src1), __pa(src2), 1, 0, 0);
}

static inline struct sbiret tensor_add(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_ADD, __pa(dst), __pa(src1), __pa(src2), 1, 0, 0);
}

static inline struct sbiret tensor_sub(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_SUB, __pa(dst), __pa(src1), __pa(src2), 1, 0, 0);
}

static inline struct sbiret tensor_relu(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_RELU, __pa(dst), __pa(src), 1, 0, 0, 0);
}

#else
#define dtype               float
#define dtype_mul(A, B)     ((A) * (B))
#define dtype_div(A, B)     ((A) / (B))
#define ftodtype(F)          ((float)(F))
#define itodtype(F)          ((float)(F))
#define todtype(F)          ((float)(F))
#define tofloat(F)          ((float)(F))

static inline struct sbiret matmul(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
        __pa(dst), __pa(src1), __pa(src2), 0, 0, 0);
}

static inline struct sbiret tensor_add(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_ADD, __pa(dst), __pa(src1), __pa(src2), 0, 0, 0);
}

static inline struct sbiret tensor_sub(Tensor *dst, Tensor *src1, Tensor *src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_SUB, __pa(dst), __pa(src1), __pa(src2), 0, 0, 0);
}

static inline struct sbiret tensor_relu(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_RELU, __pa(dst), __pa(src), 0, 0, 0, 0);
}
#endif  // JC_SCHED_FXDPT

//
static inline struct sbiret tensor_crop(Tensor *dst, Tensor *src, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_TRANSFORM_CROP,__pa(dst),__pa(src),__pa(params),0, 0, 0);
}

static inline struct sbiret tensor_reshape(Tensor *dst, Tensor *src){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_RESHAPE,__pa(dst), __pa(src), 0, 0, 0, 0);
}

static inline struct sbiret tensor_slice(Tensor *dst, Tensor *src, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_SLICE,__pa(dst), __pa(src), __pa(params), 0, 0, 0);
}

static inline struct sbiret tensor_concat(Tensor *dst, tensor_transform_params_t *params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_CONCAT,__pa(dst), __pa(params), 0, 0, 0, 0);
}

static inline struct sbiret tensor_sigmoid(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SIGMOID,__pa(dst), __pa(src), 0, 0, 0, 0);
}

static inline struct sbiret tensor_tanh(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TANH,__pa(dst), __pa(src), 0, 0, 0, 0);
}

static inline struct sbiret tensor_softmax(Tensor *dst, Tensor *src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SOFTMAX,__pa(dst), __pa(src), 0, 0, 0, 0);
}

static inline struct sbiret tensor_conv2d(Tensor *dst, Tensor *src, Tensor *weight, sbi_ml_conv_params_t *conv_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_CONV,__pa(dst),__pa(src),__pa(weight),__pa(conv_params),0, 0 );
}

static inline struct sbiret tensor_fully_connected(Tensor *dst, Tensor *src, Tensor *weight, Tensor *bias) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_FC,__pa(dst),__pa(src),__pa(weight),__pa(bias),0,0);
}

static inline struct sbiret tensor_pooling(Tensor *dst, Tensor *src, sbi_ml_pool_params_t *pool_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_POOLING,__pa(dst),__pa(src),__pa(pool_params),0, 0, 0);
}

static inline struct sbiret tensor_basic_rnn(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params) {
    return sbi_ecall( SBI_EXT_ML,SBI_EXT_ML_BASICRNN,__pa(dst),__pa(src),__pa(params),0, 0, 0);
}

static inline struct sbiret tensor_basic_lstm(Tensor *dst, Tensor *src, sbi_ml_recurrent_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_LSTM, __pa(dst), __pa(src), __pa(params), 0, 0, 0);
}

static inline struct sbiret tensor_basic_roipooling(Tensor *dst, Tensor *src, roipool_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_ROIPOOLING, __pa(dst), __pa(src), __pa(params), 0, 0, 0);
}

static inline struct sbiret tensor_basic_proposal(Tensor *dst, proposal_params_t *params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_PROPOSAL,
                    __pa(dst), __pa(params),
                    0, 0, 0, 0);      
}

#define wfi()                                             \
	do {                                              \
		__asm__ __volatile__("wfi" ::: "memory"); \
	} while (0)


#endif