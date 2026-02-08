/* Local copy of minimal SBI ML interface constants and types
 * derived from opensbi/include/sbi/sbi_ecall_interface.h
 * and opensbi/include/sbi/sbi_ml.h.
 */

#ifndef _JC_SBI_ML_MODULE_H
#define _JC_SBI_ML_MODULE_H

//下面的来自opensbi/include/sbi_ecall_interface.h

/* SBI SBI ML Extension IDs*/
#define SBI_EXT_ML 0x4D4C45 //"MLE" in ASCII
/* SBI function IDs for ML extension*/
#define SBI_EXT_ML_MATMUL 0x0
//常见神经网络算子
#define SBI_EXT_ML_CONV    0x1 //卷积
#define SBI_EXT_ML_POOLING 0x2 //池化
#define SBI_EXT_ML_RELU    0x3 //激活（ReLU）
#define SBI_EXT_ML_SIGMOID 0x4 //激活（Sigmoid）
#define SBI_EXT_ML_TANH    0x5 //激活（TANH）
#define SBI_EXT_ML_SOFTMAX 0x6 //Softmax
#define SBI_EXT_ML_FC      0x7 //全连接
#define SBI_EXT_ML_TENSOR_ADD 0x8 //张量加
#define SBI_EXT_ML_TENSOR_SUB 0x9 //张量减
#define SBI_EXT_ML_TENSOR_TRANSFORM_CROP    0xA //Tensor变换（Crop）
#define SBI_EXT_ML_TENSOR_TRANSFORM_RESHAPE 0xB //Tensor变换（Reshape）
#define SBI_EXT_ML_TENSOR_TRANSFORM_SLICE   0xC //Tensor变换（Slice）
#define SBI_EXT_ML_TENSOR_TRANSFORM_CONCAT  0xD //Tensor变换（Concat）
#define SBI_EXT_ML_ROIPOOLING 0xE //POIPooling
#define SBI_EXT_ML_PROPOSAL   0xF //Proposal
#define SBI_EXT_ML_LSTM       0x10 //LSTM
#define SBI_EXT_ML_BASICRNN   0x11 //BasicRNN、RNN

//下面的来自opensbi/include/sbi_ml.h

typedef struct {
  void *data;
  int shape[4]; // [N, H, W, C]
  int size;
} Tensor;

#define create_tensor4d(_name, _data, d1, d2, d3, d4)       \
  do {                                                      \
    (_name).data = (void *)(_data);                         \
    (_name).shape[0] = (d1);                                \
    (_name).shape[1] = (d2);                                \
    (_name).shape[2] = (d3);                                \
    (_name).shape[3] = (d4);                                \
    (_name).size = (d1) * (d2) * (d3) * (d4);               \
  } while (0)


typedef struct {
  unsigned long bias_paddr;
  unsigned long params_paddr;
} sbi_ml_conv_params_t;

typedef enum { SBI_ML_POOL_MAX=0, SBI_ML_POOL_AVG=1 } sbi_ml_pool_type_t;

typedef struct {
  sbi_ml_pool_type_t pool_type;
  unsigned long params_paddr;
} sbi_ml_pool_params_t;

typedef struct {
  unsigned long states_in_paddr;
  unsigned long states_out_paddr;
  unsigned long params_paddr;
} sbi_ml_recurrent_params_t;

typedef struct {
  int start[4];
  int end[4];
  int axis;
  int num_tensors;
  unsigned long *tensor_list_paddr;
} tensor_transform_params_t;

typedef struct {
  int roi_num;
  unsigned long roi_paddr;
  int pool_size_h;
  int pool_size_w;
  float spatial_scale;
} roipool_params_t;

typedef struct {
  int feat_stride;
  int anchor_scales[3];
  float rpn_nms_thresh;
  int pre_nms_topN;
  int post_nms_topN;
  float min_size;
} proposal_params_t;

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

#endif /* _JC_SBI_ML_MODULE_H */