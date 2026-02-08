#include "sbi.h"
#include <sbi/riscv_asm.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_init.h>

#define NR_FEAT     15
#define ftod(F)     ftodtype(F)

dtype w1[] = {
    ftod(0.565644),  ftod(0.384824), ftod(-0.042528), ftod(-0.264426),  ftod(0.472312), ftod(-0.282259), ftod(-0.014167), ftod(-0.528233),  ftod(0.622656), ftod(-0.373769),
    ftod(0.287381),  ftod(1.005889),  ftod(0.181242), ftod(-1.291967),  ftod(1.100194), ftod(-0.772200), ftod(-0.235354), ftod(-0.829178),  ftod(0.248697),  ftod(1.168082),
    ftod(-0.281433), ftod(-0.546903),  ftod(0.032876),  ftod(0.559641), ftod(-0.228221),  ftod(0.103177),  ftod(0.620234),  ftod(0.318789), ftod(-0.633047), ftod(-0.006017),
    ftod(0.047218),  ftod(0.084886), ftod(-0.134755),  ftod(0.645489), ftod(-0.277912),  ftod(0.517039),  ftod(0.651821), ftod(-0.285480), ftod(-0.003520), ftod(-0.437448),
    ftod(-0.161385), ftod(-0.442559), ftod(-0.035489),  ftod(0.570436),  ftod(0.079949),  ftod(0.741253),  ftod(0.291243),  ftod(0.586947), ftod(-0.180183), ftod(-0.177284),
    ftod(-0.396542),  ftod(0.055728),  ftod(0.112597),  ftod(0.317440), ftod(-0.177967),  ftod(0.211646), ftod(-0.254014), ftod(-0.166693), ftod(-0.414425),  ftod(0.561991),
    ftod(0.407785),  ftod(0.664266), ftod(-0.077182), ftod(-0.454090),  ftod(0.397967),  ftod(0.089694), ftod(-0.946674), ftod(-0.246415),  ftod(0.240792), ftod(-0.013765),
    ftod(-0.322740), ftod(-0.332058),  ftod(0.104680),  ftod(0.449407), ftod(-0.545375),  ftod(0.934457),  ftod(0.600992),  ftod(0.594059), ftod(-0.398014),  ftod(0.048134),
    ftod(0.199440),  ftod(0.236234), ftod(-0.549774),  ftod(0.362871),  ftod(0.128888), ftod(-0.064394),  ftod(0.194858),  ftod(0.173756), ftod(-0.087557),  ftod(0.147654),
    ftod(0.133639),  ftod(0.000841), ftod(-0.001098),  ftod(0.626147), ftod(-0.152287),  ftod(0.110689),  ftod(0.108449), ftod(-0.463610),  ftod(0.171219),  ftod(0.310098),
    ftod(-0.440701),  ftod(0.361575), ftod(-0.302418),  ftod(0.573317),  ftod(0.322387),  ftod(0.602443), ftod(-0.314726),  ftod(0.031837),  ftod(0.124628), ftod(-0.135573),
    ftod(0.159068), ftod(-0.059842), ftod(-0.526570), ftod(-0.010963),  ftod(0.311802),  ftod(0.360409), ftod(-0.103766),  ftod(0.363927), ftod(-0.428252),  ftod(0.085832),
    ftod(-0.080852),  ftod(0.010944), ftod(-0.331394),  ftod(0.068851),  ftod(0.145650),  ftod(0.842668),  ftod(0.369900), ftod(-0.027606), ftod(-0.326165), ftod(-0.271815),
    ftod(-0.219882), ftod(-0.526053), ftod(-0.540803),  ftod(0.893084), ftod(-1.002251),  ftod(0.007923),  ftod(1.298324),  ftod(0.295529), ftod(-0.469116), ftod(-0.790421),
    ftod(0.936136),  ftod(0.879596), ftod(-0.094900), ftod(-0.326074),  ftod(0.891442), ftod(-1.032957), ftod(-0.173408), ftod(-0.906972),  ftod(0.650875),  ftod(0.917579),
};

dtype b1[] = {
    ftod(-0.257286), ftod(-0.220656), ftod(-0.312300), ftod(0.485314), ftod(-0.377361), ftod(0.445350), ftod(0.321995), ftod(0.456795), ftod(-0.164362), ftod(-0.260494),
};

dtype w2[] = { ftod(-0.409050), ftod(-0.578690), ftod(-0.446989), ftod(0.361227), ftod(-0.401546), ftod(0.258594), ftod(0.760240), ftod(0.524665), ftod(-0.385637), ftod(-0.721390),};

dtype b2[] = { ftod(0.405319) };
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
    //putchar('\n');
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

void print_c(int a){
    char str[20];
    itoa(a,str);
    puts(str);
    puts("\n");
}

// 适配float16_t的浮点数数组打印函数
void print_float16_array(float32_t *arr, int size, const char *label) {
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
        if(i%5==0)
            puts("\n");
    }
    puts("]\n");
}


void print_k(fxdpt_t *a,int size,const char *label){
    char str[40];
    puts(label);
    puts(": [");
    for (int i = 0; i < size; i++) {
        fxdpt_t x = a[i];
        int b =(int)x;
        if(b<0){
            putchar('-');
            b=-b;
        }
        itoa(b,str);
        puts(str);
        if (i < size - 1) {
            puts(", ");
        }
        if(i%5 == 0 && i!=0)
            puts("\n");
    }
    puts("]\n");
}

void print_tensor_data(Tensor *tensor, const char *label) {//用于打印Tensor结构体中data数据
    if (tensor->data) {
        // 适配float16_t转float打印
        print_k((fxdpt_t *)tensor->data, tensor->size, label);
    } else {
        puts(label);
        puts(": NULL data\n");
    }
}

void test_matmul1();
typedef unsigned int u32 ;

#include <riscv_vector.h>
#include "rvv_test.h"
void main(unsigned int a0, unsigned int a1) {
    u32 cur_halt=a0;
    u32 dtb_address_baes=a1;
    dtype input[NR_FEAT] = {
        ftod(1),ftod(0),ftod(0),ftod(0),ftod(1),ftod(0),ftod(0),ftod(0),ftod(0),ftod(0.008),ftod(0.009000000000000001),ftod(0),ftod(0.0),ftod(0),ftod(0)
    };      // 定点数格式
    dtype o1[10];              // 第一层输出定点数格式
    dtype o2[1];
    char str[20]; // 假设数字最多20位
    itoa(cur_halt, str); // 将数字转换为字符串
    puts("\n################\nSBI TO Kernel");
    puts("Boot From Core:");
    puts(str);
    // itoa(x2, str); // 将数字转换为字符串
    if(dtb_address_baes==0x80800000 )
        puts("dt address get");
    puts("Hello World!");
    test_main();
    #ifdef ML_TEST
    struct sbiret ret;
    // test_matmul1();
    create_tensor4d(t_input, input, 1, 1, NR_FEAT, 1);
    create_tensor4d(W1, w1, 1, NR_FEAT, 10, 1);
    create_tensor4d(B1, b1, 1, 1, 10, 1);
    create_tensor4d(out1, o1, 1, 1, 10, 1);
    create_tensor4d(W2, w2, 1, 10, 1, 1);
    create_tensor4d(B2, b2, 1, 1, 1, 1);
    create_tensor4d(out2, o2, 1, 1, 1, 1);
    puts("=============================\n");
    ret = matmul(&out1,&t_input,&W1,1);
    ret = matmul(&out1,&t_input,&W1,1);
    ret = matmul(&out1,&t_input,&W1,1);
    puts("=============================\n");
    //print_k((&out1)->data);
    print_tensor_data(&out1, "answer");
    if(ret.error ==  -1){         
        puts("error\n");     
    }
    ret = tensor_add(&out1, &out1, &B1,1);
    if(ret.error ==  -1){         
        puts("error\n");     
    }
    ret = tensor_relu(&out1, &out1,1);
    if(ret.error ==  -1){         
        puts("error\n");     
    }
    ret = matmul(&out2, &out1, &W2,1);
    if(ret.error ==  -1){         
        puts("error\n");     
    }
    ret = tensor_add(&out2, &out2, &B2,1);
    if(ret.error ==  -1){
        puts("error\n");
    }
    print_tensor_data(&out2,"answer_finnal");
    #endif
    // clear();
    shutdown();
}
