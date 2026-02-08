#include "sbi.h"
#include <sbi/riscv_asm.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_init.h>

void *memset(void *ptr, int value, unsigned long num) {
    if (ptr == NULL || num == 0) return ptr;
    unsigned char *p = (unsigned char *)ptr;
    unsigned char val = (unsigned char)value;
    while (num--) *p++ = val;
    return ptr;
}
// void my_printf(const char *format, ...);
// void printf(const char *format, ...);
int putchar(int c) {
  SBI_PUTCHAR(c);
  return 1;
}

int puts(const char *s) {
  //这是不安全的函数
    while (*s)
        s+=putchar(*s);
    putchar('\n');
    return 1;  // 返回一个非负值表示成功
}
void clear(){
  puts("\033[2J");
}

void itoa(int num, char *str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
    } else {
        while (num != 0) {
            int rem = num % 10;
            str[i++] = rem + 0x30;
            num = num / 10;
        }
        str[i] = '\0';
        // 反转字符串
        int start = 0;
        int end = i - 1;
        while (start < end) {
            char temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start++;
            end--;
        }
    }
}

// 适配float16_t的浮点数数组打印函数
void print_float16_array(float16_t *arr, int size, const char *label) {
    char str[20];
    puts(label);
    puts(": [");

    for (int i = 0; i < size; i++) {
        float val = (float)arr[i];
        // 转换为整数部分
        int int_part = (int)val;
        // 计算小数部分（只显示前两位）
        int frac_part = (int)((val - int_part) * 100);

        if (int_part < 0) {
            putchar('-');
            int_part = -int_part;
        }

        itoa(int_part, str);
        puts(str);
        putchar('.');

        if (frac_part < 10) {
            putchar('0');
        }
        itoa(frac_part, str);
        puts(str);

        if (i < size - 1) {
            puts(", ");
        }
    }
    puts("]\n");
}

void print_tensor_data(Tensor *tensor, const char *label) {//用于打印Tensor结构体中data数据
    if (tensor->data) {
        // 适配float16_t转float打印
        print_float16_array((float16_t *)tensor->data, tensor->size, label);
    } else {
        puts(label);
        puts(": NULL data\n");
    }
}


void test_matmul1();
typedef unsigned int u32;


   

#include <riscv_vector.h>
#include "rvv_test.h"
void main(unsigned int a0, unsigned int a1) {
u32 cur_halt=a0;
u32 dtb_address_baes=a1;
  char str[20];
  itoa(cur_halt, str);
  puts("\n################\nSBI TO Kernel");
  puts("Boot From Core:");
  puts(str);
  if(dtb_address_baes==0x80800000 )
    puts("dt address get");
  puts("Hello World!");
  
  #ifdef ML_TEST
  struct sbiret r1;
 
 

float16_t proposal_dist[20] = {0.0f};
    
    // 预期输出（匹配算子生成逻辑）
    float16_t proposal_answ[] = {
        (float16_t)0.00f, (float16_t)0.00f, (float16_t)0.20f, (float16_t)0.20f, (float16_t)0.90f,
        (float16_t)0.10f, (float16_t)0.00f, (float16_t)0.30f, (float16_t)0.20f, (float16_t)0.89f,
        (float16_t)0.20f, (float16_t)0.00f, (float16_t)0.40f, (float16_t)0.20f, (float16_t)0.88f,
        (float16_t)0.30f, (float16_t)0.00f, (float16_t)0.50f, (float16_t)0.20f, (float16_t)0.87f
    };

    // Proposal参数初始化（严格匹配你的结构体）
    proposal_params_t proposal_params = {
        .feat_stride = 16,
        .anchor_scales = {8, 16, 32},
        .rpn_nms_thresh = 0.7f,
        .pre_nms_topN = 6000,
        .post_nms_topN = 4,
        .min_size = 16.0f
    };

    // 创建Tensor（匹配算子输出维度）
    create_tensor4d(tensor_proposal_dist, (void *)proposal_dist, 1, 4, 5, 1);
    create_tensor4d(tensor_proposal_answ, (void *)proposal_answ, 1, 4, 5, 1);

    // 打印预期输出
    puts("\n================ Proposal ECALL Test ================\n");
    print_tensor_data(&tensor_proposal_answ, "Proposal Expected Output");

    // 调用ECALL（原调用形式，无修改）
    r1 = tensor_basic_proposal(&tensor_proposal_dist, &proposal_params);

    // 打印实际输出
    print_tensor_data(&tensor_proposal_dist, "Proposal Actual Output");

    // 结果验证
    float prop_dst_float[20], prop_ans_float[20];
    for (int i=0; i<20; i++) {
        prop_dst_float[i] = (float)proposal_dist[i];
        prop_ans_float[i] = (float)proposal_answ[i];
    }

    if (r1.error == 0) {
        char str_prop[20];
        itoa(r1.value, str_prop);
        puts("ML_TENSOR_PROPOSAL_ECALL_TEST ");
        EXCEPT_FP32_ARRAY_LAX_EQ(prop_ans_float, prop_dst_float, 20,
                               "Proposal ECALL [4 anchors] -> 4 proposals (5D)");
        puts(str_prop);
    } else {
        puts("Proposal ECALL Test Error\n");
        char err_str[20];
        itoa(r1.error, err_str);
        puts("Error Code: ");
        puts(err_str);
    }
    #endif

    shutdown();
}