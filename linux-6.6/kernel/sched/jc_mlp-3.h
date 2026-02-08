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

static inline struct sbiret matmul(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
        dst, src1, src2, 1, 0, 0);
}

static inline struct sbiret tensor_add(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_ADD,dst,src1,src2,0,0,0);
}

static inline struct sbiret tensor_sub(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_SUB,dst,src1,src2,0,0,0);
}

static inline struct sbiret tensor_relu(unsigned long dst, unsigned long src){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_RELU,dst,src,0,0,0,0);
}

#else
#define dtype               float
#define dtype_mul(A, B)     ((A) * (B))
#define dtype_div(A, B)     ((A) / (B))
#define ftodtype(F)          ((float)(F))
#define itodtype(F)          ((float)(F))
#define todtype(F)          ((float)(F))
#define tofloat(F)          ((float)(F))

static inline struct sbiret matmul(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_MATMUL,
        dst, src1, src2, 0, 0, 0);
}

static inline struct sbiret tensor_add(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_ADD,dst,src1,src2,0,0,0);
}

static inline struct sbiret tensor_sub(unsigned long dst, unsigned long src1, unsigned long src2){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_SUB,dst,src1,src2,0,0,0);
}

static inline struct sbiret tensor_relu(unsigned long dst, unsigned long src){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_RELU,dst, src,0,0,0,0);
}
#endif  // JC_SCHED_FXDPT


static inline struct sbiret tensor_crop(unsigned long dst, unsigned long src, unsigned long params){
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_TENSOR_TRANSFORM_CROP,dst,src,params,0, 0, 0);
}

static inline struct sbiret tensor_reshape(unsigned long dst, unsigned long src){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_RESHAPE,dst, src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_slice(unsigned long dst, unsigned long src, unsigned long params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_SLICE,dst, src, params, 0, 0, 0);
}

static inline struct sbiret tensor_concat(unsigned long dst, unsigned long params){
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TENSOR_TRANSFORM_CONCAT,dst, params, 0, 0, 0, 0);
}

static inline struct sbiret tensor_sigmoid(unsigned long dst, unsigned long src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SIGMOID,dst, src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_tanh(unsigned long dst, unsigned long src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_TANH,dst, src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_softmax(unsigned long dst, unsigned long src) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_SOFTMAX,dst, src, 0, 0, 0, 0);
}

static inline struct sbiret tensor_conv2d(unsigned long dst, unsigned long src, unsigned long weight, unsigned long conv_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_CONV,dst,src,weight,conv_params,0, 0);
}

static inline struct sbiret tensor_fully_connected(unsigned long dst, unsigned long src, unsigned long weight, unsigned long bias) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_FC,dst,src,weight,bias,0,0);
}

static inline struct sbiret tensor_pooling(unsigned long dst, unsigned long src, unsigned long pool_params) {
    return sbi_ecall(SBI_EXT_ML,SBI_EXT_ML_POOLING,dst,src,pool_params,0, 0, 0);
}

static inline struct sbiret tensor_basic_rnn(unsigned long dst, unsigned long src, unsigned long params) {
    return sbi_ecall( SBI_EXT_ML,SBI_EXT_ML_BASICRNN,dst,src,params,0, 0, 0);
}

static inline struct sbiret tensor_basic_lstm(unsigned long dst, unsigned long src, unsigned long params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_LSTM, dst, src, params, 0, 0, 0);
}

static inline struct sbiret tensor_basic_roipooling(unsigned long dst, unsigned long src, unsigned long params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_ROIPOOLING, dst, src, params, 0, 0, 0);
}

static inline struct sbiret tensor_basic_proposal(unsigned long dst, unsigned long params) {
    return sbi_ecall(SBI_EXT_ML, SBI_EXT_ML_PROPOSAL,
                    dst, params,
                    0, 0, 0, 0);      
}           
#define wfi()                                             \
	do {                                              \
		__asm__ __volatile__("wfi" ::: "memory"); \
	} while (0)


#endif