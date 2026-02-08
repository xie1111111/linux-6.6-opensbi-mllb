#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/printk.h>
#include <linux/slab.h>  // 引入 kmalloc/kfree 头文件
#include <linux/types.h>
#include <linux/atomic.h>
#include <linux/compiler.h> // 引入 READ_ONCE/WRITE_ONCE
#include <asm/io.h>
#include <asm/page.h>
#include <asm/sbi.h>
#include "jc_sbi_ml.h"

#include "jc_mlp.h"

// 添加全局变量记录forward_pass的统计信息
static atomic64_t forward_pass_count = ATOMIC64_INIT(0);
static atomic64_t forward_pass_total_time_ns = ATOMIC64_INIT(0);
static atomic64_t time1 = ATOMIC64_INIT(0);
static atomic64_t time2 = ATOMIC64_INIT(0);
static atomic64_t time3 = ATOMIC64_INIT(0);
static atomic64_t time4 = ATOMIC64_INIT(0);
static atomic64_t time5 = ATOMIC64_INIT(0);
static atomic64_t time6 = ATOMIC64_INIT(0);
static atomic64_t time7 = ATOMIC64_INIT(0);
static atomic64_t time8 = ATOMIC64_INIT(0);
static atomic64_t time9 = ATOMIC64_INIT(0);
static atomic64_t time10 = ATOMIC64_INIT(0);
static atomic64_t time11 = ATOMIC64_INIT(0);
static atomic64_t time12 = ATOMIC64_INIT(0);

#define NR_FEAT     15
#define ftod(F)     ftodtype(F)

// 全局共享内存池
static struct ml_shared_mem {
    Tensor t_W1;
    Tensor t_B1;
    Tensor t_W2;
    Tensor t_B2;
}ml_shared;

static int ml_shared_inited = 0;
//static DEFINE_SPINLOCK(ml_lock);

int is_jc_sched = 0;
EXPORT_SYMBOL(is_jc_sched);

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

// 初始化共享内存
static int jc_mlp_sched_init(void)
{
    if (READ_ONCE(ml_shared_inited)) {
        return 0;
    }
    memset(&ml_shared, 0, sizeof(struct ml_shared_mem));
    // 初始化Tensor结构体 (使用虚拟地址，shape格式: [N, H, W, C])
    // 所有tensor都指向定点数数组
    create_tensor4d(ml_shared.t_W1,
            __pa(w1), 1, NR_FEAT, 10, 1);                 // [1, 15, 10, 1] - 15x10矩阵
    create_tensor4d(ml_shared.t_B1,
            __pa(b1), 1, 1, 10, 1);                       // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared.t_W2,
            __pa(w2), 1, 10, 1, 1);                       // [1, 10, 1, 1] - 10x1矩阵
    create_tensor4d(ml_shared.t_B2,
            __pa(b2), 1, 1, 1, 1);                        // [1, 1, 1, 1] - 1x1标量
    
    WRITE_ONCE(ml_shared_inited, 1);
    pr_info("RVSML-MLLB: Shared memory initialized\n");
    return 0;
}

// forward_pass函数（作为内核组件）
static int forward_pass(dtype *input_data) {
    ktime_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13;
    struct sbiret ret;
    dtype *o1;              // 第一层输出定点数格式
    dtype *o2;               // 第二层输出定点数格式
    Tensor *input;           // 改为 Tensor 指针，动态分配
    Tensor *out1;            // 改为 Tensor 指针，动态分配
    Tensor *out2;            // 改为 Tensor 指针，动态分配
    t1 = ktime_get_ns();
    // 动态分配 o1、o2 数据缓冲区（内核线性地址，独立内存，无共享）
    o1 = kmalloc(sizeof(dtype) * 10, GFP_ATOMIC);
    o2 = kmalloc(sizeof(dtype) * 1, GFP_ATOMIC);
    
    // 动态分配 Tensor 结构体内存（内核线性地址，合法可__pa()转换）
    input = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    out1 = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    out2 = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    
    // 检查所有分配结果，任一失败则释放所有已分配内存
    if (!o1 || !o2 || !input || !out1 || !out2) {
        pr_err("RVSML-MLLB: kmalloc o1/o2 or Tensor failed (out of memory)\n");
        // kfree(NULL) 安全，直接按顺序释放所有资源
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t2 = ktime_get_ns();
    // 确保共享内存已初始化
    if (jc_mlp_sched_init() != 0) {
        pr_err("RVSML-MLLB: jc_mlp_sched_init failed\n");
        // 异常分支：释放所有动态分配内存，避免泄漏
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t3 = ktime_get_ns();
    // 初始化 Tensor 结构体（解引用指针，适配原 create_tensor4d 函数）
    create_tensor4d(*input, __pa(input_data), 1, 1, NR_FEAT, 1);  // [1, 1, 15, 1]
    create_tensor4d(*out1, __pa(o1), 1, 1, 10, 1);            // [1, 1, 10, 1]
    create_tensor4d(*out2, __pa(o2), 1, 1, 1, 1);             // [1, 1, 1, 1]
    t4 = ktime_get_ns();
    // 3. 执行MLP推理
    pr_debug("RVSML-MLLB: Forward pass via SBI starting...\n");
    
    // 日志打印：适配 Tensor 指针（-> 访问成员）
    //pr_err("input的地址:%p\n", &(input->shape));
    //pr_err("input的行:%d\n", input->shape[1]);
    //pr_err("input的列:%d\n", input->shape[2]);
    
    // Layer 1: Matmul（直接传递 Tensor 指针，无需 & 取地址）
    t5 = ktime_get_ns();
    ret = matmul(out1, input, &ml_shared.t_W1);
    t6 = ktime_get_ns();
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 1) failed: %ld\n", ret.error);
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t7 = ktime_get_ns();

    // Layer 2: Add Bias
    ret = tensor_add(out1, out1, &ml_shared.t_B1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 1 bias) failed: %ld\n", ret.error);
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t8 = ktime_get_ns();

    // Layer 3: ReLU
    ret = tensor_relu(out1, out1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_relu (layer 1) failed: %ld\n", ret.error);
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t9 = ktime_get_ns();

    // Layer 4: Matmul
    ret = matmul(out2, out1, &ml_shared.t_W2);
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 4) failed: %ld\n", ret.error);
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t10 = ktime_get_ns();

    // Layer 5: Add Bias
    ret = tensor_add(out2, out2, &ml_shared.t_B2);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 5 bias) failed: %ld\n", ret.error);
        kfree(input);
        kfree(out1);
        kfree(out2);
        kfree(o1);
        kfree(o2);
        return -1;
    }
    t11 = ktime_get_ns();
    
    // 5. 获取最终结果 (定点数格式)
    dtype final_output = o2[0];
    t12 = ktime_get_ns();

    // 7. 释放所有动态分配的内存（Tensor 指针 + 数据缓冲区）
    kfree(input);
    kfree(out1);
    kfree(out2);
    kfree(o1);
    kfree(o2);
    t13 = ktime_get_ns();
    atomic64_add(t2-t1, &time1);
    atomic64_add(t3-t2, &time2);
    atomic64_add(t4-t3, &time3);
    atomic64_add(t5-t4, &time4);
    atomic64_add(t6-t5, &time5);
    atomic64_add(t7-t6, &time6);
    atomic64_add(t8-t7, &time7);
    atomic64_add(t9-t8, &time8);
    atomic64_add(t10-t9, &time9);
    atomic64_add(t11-t10, &time10);
    atomic64_add(t12-t11, &time11);
    atomic64_add(t13-t12, &time12);
    
    return final_output > ftod(0.5) ? 1 : 0;
}

// 保持原有的jc_mlp_main函数，仅修改forward_pass调用
#ifdef CONFIG_JC_SCHED_FXDPT
int jc_mlp_main(struct jc_lb_data *data)
{
    int output;
    dtype *input;
    //dtype input[NR_FEAT];
    dtype delta_faults;
    ktime_t start_time, end_time;
    s64 elapsed_time_ns;

    // 1. 动态分配 input（内核线性地址，GFP_ATOMIC 适合内核态非中断上下文）
    // 每个调用分配一块独立内存，无共享
    input = kmalloc(sizeof(dtype) * NR_FEAT, GFP_ATOMIC);
    if (!input) {  // 必做：检查分配是否失败，避免空指针访问
        pr_err("RVSML-MLLB: kmalloc input failed (out of memory)\n");
        return -1;
    }
    
    if (data->total_faults)
        delta_faults = dtype_div(itodtype(data->delta_faults), itodtype(data->total_faults));
    else
        delta_faults = itodtype(data->delta_faults);

    // 准备输入数据
    input[0] = itodtype(data->src_non_pref);
    input[1] = itodtype(data->delta_hot);
    input[2] = itodtype(data->cpu_idle);
    input[3] = itodtype(data->cpu_not_idle);
    input[4] = itodtype(data->cpu_newly_idle);
    input[5] = itodtype(data->same_node);
    input[6] = itodtype(data->prefer_src);
    input[7] = itodtype(data->prefer_dst);
    input[8] = itodtype(data->src_len) - itodtype(2);
    input[9] = dtype_div(itodtype(data->src_load), itodtype(1000));
    input[10] = dtype_div(itodtype(data->dst_load), itodtype(1000));
    input[11] = itodtype(data->dst_len);
    input[12] = delta_faults;
    input[13] = itodtype(data->extra_fails);
    input[14] = itodtype(data->buddy_hot);

    // 记录开始时间
    start_time = ktime_get_ns();
    
    // 调用forward_pass
    output = forward_pass(input);

    // 记录结束时间并计算耗时
    end_time = ktime_get_ns();
    elapsed_time_ns = end_time - start_time;
    
    kfree(input);

    // 更新统计信息
    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_time_ns, &forward_pass_total_time_ns);
    
    // 每1000次打印统计，然后重置数据（避免值过大）
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        // 原子交换：读取当前值，并将原子变量重置为 0（无锁安全）
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_time = atomic64_xchg(&forward_pass_total_time_ns, 0);
        u64 total_t1 = atomic64_xchg(&time1, 0);
        u64 total_t2 = atomic64_xchg(&time2, 0);
        u64 total_t3 = atomic64_xchg(&time3, 0);
        u64 total_t4 = atomic64_xchg(&time4, 0);
        u64 total_t5 = atomic64_xchg(&time5, 0);
        u64 total_t6 = atomic64_xchg(&time6, 0);
        u64 total_t7 = atomic64_xchg(&time7, 0);
        u64 total_t8 = atomic64_xchg(&time8, 0);
        u64 total_t9 = atomic64_xchg(&time9, 0);
        u64 total_t10 = atomic64_xchg(&time10, 0);
        u64 total_t11 = atomic64_xchg(&time11, 0);
        u64 total_t12 = atomic64_xchg(&time12, 0);

        // 这里判断 total_count 是否为 1000（避免多核并发时，多次触发打印）
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %lld ns\n", total_time / total_count);
            printk(KERN_INFO "Average time for five kmalloc: %lld ns\n",total_t1 / total_count);
            printk(KERN_INFO "Average time for sched init: %lld ns\n",total_t2 / total_count);
            printk(KERN_INFO "Average time for create tensor: %lld ns\n",total_t3 / total_count);
            printk(KERN_INFO "Average time for pr_debug: %lld ns\n",total_t4 / total_count);
            printk(KERN_INFO "Average time for only matmul: %lld ns\n",total_t5 / total_count);
            printk(KERN_INFO "Average time for if ret.error: %lld ns\n",total_t6 / total_count);
            printk(KERN_INFO "Average time for tensor add and if ret.error1: %lld ns\n",total_t7 / total_count);
            printk(KERN_INFO "Average time for relu and if ret.error: %lld ns\n",total_t8 / total_count);
            printk(KERN_INFO "Average time for matmul and ret.error: %lld ns\n",total_t9 / total_count);
            printk(KERN_INFO "Average time for tensor add and if ret.error2: %lld ns\n",total_t10 / total_count);
            printk(KERN_INFO "Average time for finnal_output: %lld ns\n",total_t11 / total_count);
            printk(KERN_INFO "Average time for kfree the five kmalloc: %lld ns\n",total_t12 / total_count);
            printk(KERN_INFO "===================================================\n");
        }
    }
    
    return output;
}
#else
int jc_mlp_main(struct jc_lb_data *data)
{
    int output;
    dtype *input;
    //dtype input[NR_FEAT];
    dtype delta_faults;
    ktime_t start_time, end_time;
    s64 elapsed_time_ns;

    // 1. 动态分配 input（内核线性地址，GFP_ATOMIC 适合内核态非中断上下文）
    // 每个调用分配一块独立内存，无共享
    input = kmalloc(sizeof(dtype) * NR_FEAT, GFP_ATOMIC);
    if (!input) {  // 必做：检查分配是否失败，避免空指针访问
        pr_err("RVSML-MLLB: kmalloc input failed (out of memory)\n");
        return -1;
    }
    
    if (data->total_faults)
        delta_faults = (dtype)data->delta_faults / data->total_faults;
    else
        delta_faults = (dtype)data->delta_faults;

    // 准备输入数据
    input[0] = (dtype)data->src_non_pref;
    input[1] = (dtype)data->delta_hot;
    input[2] = (dtype)data->cpu_idle;
    input[3] = (dtype)data->cpu_not_idle;
    input[4] = (dtype)data->cpu_newly_idle;
    input[5] = (dtype)data->same_node;
    input[6] = (dtype)data->prefer_src;
    input[7] = (dtype)data->prefer_dst;
    input[8] = (dtype)data->src_len - 2;
    input[9] = (dtype)data->src_load / 1000;
    input[10] = (dtype)data->dst_load / 1000;
    input[11] = (dtype)data->dst_len;
    input[12] = delta_faults;
    input[13] = (dtype)data->extra_fails;
    input[14] = (dtype)data->buddy_hot;

    // 记录开始时间
    start_time = ktime_get_ns();
    
    // 调用forward_pass
    output = forward_pass(input);

    // 记录结束时间并计算耗时
    end_time = ktime_get_ns();
    elapsed_time_ns = end_time - start_time;

    kfree(input);
    // 更新统计信息
    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_time_ns, &forward_pass_total_time_ns);
    
    // 每1000次打印统计，然后重置数据（避免值过大）
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        // 原子交换：读取当前值，并将原子变量重置为 0（无锁安全）
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_time = atomic64_xchg(&forward_pass_total_time_ns, 0);
        u64 total_t1 = atomic64_xchg(&time1, 0);
        u64 total_t2 = atomic64_xchg(&time2, 0);
        u64 total_t3 = atomic64_xchg(&time3, 0);
        u64 total_t4 = atomic64_xchg(&time4, 0);
        u64 total_t5 = atomic64_xchg(&time5, 0);
        u64 total_t6 = atomic64_xchg(&time6, 0);
        u64 total_t7 = atomic64_xchg(&time7, 0);
        u64 total_t8 = atomic64_xchg(&time8, 0);
        u64 total_t9 = atomic64_xchg(&time9, 0);
        u64 total_t10 = atomic64_xchg(&time10, 0);
        u64 total_t11 = atomic64_xchg(&time11, 0);
        u64 total_t12 = atomic64_xchg(&time12, 0);

        // 这里判断 total_count 是否为 1000（避免多核并发时，多次触发打印）
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %lld ns\n", total_time / total_count);
            printk(KERN_INFO "Average time for five kmalloc: %lld ns\n",total_t1 / total_count);
            printk(KERN_INFO "Average time for sched init: %lld ns\n",total_t2 / total_count);
            printk(KERN_INFO "Average time for create tensor: %lld ns\n",total_t3 / total_count);
            printk(KERN_INFO "Average time for pr_debug: %lld ns\n",total_t4 / total_count);
            printk(KERN_INFO "Average time for only matmul: %lld ns\n",total_t5 / total_count);
            printk(KERN_INFO "Average time for if ret.error: %lld ns\n",total_t6 / total_count);
            printk(KERN_INFO "Average time for tensor add and if ret.error1: %lld ns\n",total_t7 / total_count);
            printk(KERN_INFO "Average time for relu and if ret.error: %lld ns\n",total_t8 / total_count);
            printk(KERN_INFO "Average time for matmul and ret.error: %lld ns\n",total_t9 / total_count);
            printk(KERN_INFO "Average time for tensor add and if ret.error2: %lld ns\n",total_t10 / total_count);
            printk(KERN_INFO "Average time for finnal_output: %lld ns\n",total_t11 / total_count);
            printk(KERN_INFO "Average time for kfree the five kmalloc: %lld ns\n",total_t12 / total_count);
            printk(KERN_INFO "===================================================\n");
        }
    }
    return output;
}
#endif


