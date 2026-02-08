#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/slab.h>  // 添加kmalloc支持
#include <linux/ktime.h>
#include <linux/printk.h>
#include <linux/spinlock.h>
#include <asm/io.h>
#include <asm/page.h>
#include <asm/sbi.h>
#include "jc_sbi_ml.h"

#include "jc_mlp.h"

// 添加全局变量记录forward_pass的统计信息
static atomic64_t forward_pass_count = ATOMIC64_INIT(0);
static atomic64_t forward_pass_total_time_ns = ATOMIC64_INIT(0);

// 添加数组记录前1000次执行时间
static s64 forward_pass_times[1000];
static int times_index = 0;
static DEFINE_SPINLOCK(times_lock);  // 保护times_index的锁

#define NR_FEAT     15
#define ftod(F)     ftodtype(F)

// 全局共享内存池
static struct ml_shared_mem {
    dtype input[NR_FEAT];      // 定点数格式
    dtype o1[10];              // 第一层输出定点数格式
    dtype o2[1];               // 第二层输出定点数格式
    Tensor t_input;
    Tensor t_W1;
    Tensor t_B1;
    Tensor t_out1;
    Tensor t_W2;
    Tensor t_B2;
    Tensor t_out2;
} *ml_shared;

static int ml_shared_initialized = 0;
static DEFINE_SPINLOCK(ml_lock);

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
static int init_ml_shared_mem(void)
{
    ml_shared = kmalloc(sizeof(*ml_shared), GFP_KERNEL);
    if (!ml_shared) {
        pr_err("RVSML-MLLB: Failed to allocate shared memory\n");
        return -ENOMEM;
    }
    
    memset(ml_shared, 0, sizeof(*ml_shared));

    // 初始化Tensor结构体 (使用虚拟地址，shape格式: [N, H, W, C])
    // 所有tensor都指向定点数数组
    create_tensor4d(ml_shared->t_input,
            __pa(ml_shared->input), 1, 1, NR_FEAT, 1);  // [1, 1, 15, 1] - 1x15向量
    create_tensor4d(ml_shared->t_W1,
            __pa(w1), 1, NR_FEAT, 10, 1);                 // [1, 15, 10, 1] - 15x10矩阵
    create_tensor4d(ml_shared->t_B1,
            __pa(b1), 1, 1, 10, 1);                       // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_out1,
            __pa(ml_shared->o1), 1, 1, 10, 1);            // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_W2,
            __pa(w2), 1, 10, 1, 1);                       // [1, 10, 1, 1] - 10x1矩阵
    create_tensor4d(ml_shared->t_B2,
            __pa(b2), 1, 1, 1, 1);                        // [1, 1, 1, 1] - 1x1标量
    create_tensor4d(ml_shared->t_out2,
            __pa(ml_shared->o2), 1, 1, 1, 1);             // [1, 1, 1, 1] - 1x1标量
    
    ml_shared_initialized = 1;
    pr_info("RVSML-MLLB: Shared memory initialized\n");
    return 0;
}

    

// 安全的内存屏障
static inline void ml_memory_barrier(void)
{
    mb();
}

// forward_pass函数（作为内核组件）
static int forward_pass(dtype *input_data) {
    struct sbiret ret;
    unsigned long flags;
    
    // 确保共享内存已初始化
    if (!ml_shared_initialized) {
        if (init_ml_shared_mem() != 0) {
            return -1;
        }
    }
    
    // 加锁保护共享内存访问
    spin_lock_irqsave(&ml_lock, flags);
    
    // 1. 复制输入数据（定点数格式）
    memcpy(ml_shared->input, input_data, NR_FEAT * sizeof(dtype));
    
    create_tensor4d(ml_shared->t_input,
            __pa(ml_shared->input), 1, 1, NR_FEAT, 1);  // [1, 1, 15, 1] - 1x15向量
    create_tensor4d(ml_shared->t_W1,
            __pa(w1), 1, NR_FEAT, 10, 1);                 // [1, 15, 10, 1] - 15x10矩阵
    create_tensor4d(ml_shared->t_B1,
            __pa(b1), 1, 1, 10, 1);                       // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_out1,
            __pa(ml_shared->o1), 1, 1, 10, 1);            // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_W2,
            __pa(w2), 1, 10, 1, 1);                       // [1, 10, 1, 1] - 10x1矩阵
    create_tensor4d(ml_shared->t_B2,
            __pa(b2), 1, 1, 1, 1);                        // [1, 1, 1, 1] - 1x1标量
    create_tensor4d(ml_shared->t_out2,
            __pa(ml_shared->o2), 1, 1, 1, 1);             // [1, 1, 1, 1] - 1x1标量

    // 2. 内存屏障确保数据同步
    ml_memory_barrier();
    
    // 3. 执行MLP推理
    pr_debug("RVSML-MLLB: Forward pass via SBI starting...\n");
    
    // Layer 1: Matmul
    ret = matmul(&ml_shared->t_out1, &ml_shared->t_input, &ml_shared->t_W1);
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 1) failed: %ld\n", ret.error);
        spin_unlock_irqrestore(&ml_lock, flags);
        return -1;
    }

    // Layer 2: Add Bias
    ret = tensor_add(&ml_shared->t_out1, &ml_shared->t_out1, &ml_shared->t_B1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 1 bias) failed: %ld\n", ret.error);
        spin_unlock_irqrestore(&ml_lock, flags);
        return -1;
    }

    // Layer 3: ReLU
    ret = tensor_relu(&ml_shared->t_out1, &ml_shared->t_out1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_relu (layer 1) failed: %ld\n", ret.error);
        spin_unlock_irqrestore(&ml_lock, flags);
        return -1;
    }

    // Layer 4: Matmul
    ret = matmul(&ml_shared->t_out2, &ml_shared->t_out1, &ml_shared->t_W2);
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 4) failed: %ld\n", ret.error);
        spin_unlock_irqrestore(&ml_lock, flags);
        return -1;
    }

    // Layer 5: Add Bias
    ret = tensor_add(&ml_shared->t_out2, &ml_shared->t_out2, &ml_shared->t_B2);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 5 bias) failed: %ld\n", ret.error);
        spin_unlock_irqrestore(&ml_lock, flags);
        return -1;
    }
    
    // 4. 内存屏障确保结果同步
    ml_memory_barrier();
    
    // 5. 获取最终结果 (定点数格式)
    dtype final_output = ml_shared->o2[0];
    
    spin_unlock_irqrestore(&ml_lock, flags);

    return final_output > ftod(0.5) ? 1 : 0;
}

// 保持原有的jc_mlp_main函数，仅修改forward_pass调用
#ifdef CONFIG_JC_SCHED_FXDPT
int jc_mlp_main(struct jc_lb_data *data)
{
    int output;
    dtype input[NR_FEAT];
    dtype delta_faults;
    ktime_t start_time, end_time;
    s64 elapsed_time_ns;
    unsigned long flags;

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

    // 更新统计信息
    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_time_ns, &forward_pass_total_time_ns);

    // 记录执行时间到数组
    spin_lock_irqsave(&times_lock, flags);
    
    if (times_index < 1000) {
        forward_pass_times[times_index] = elapsed_time_ns;
        times_index++;
        
        // 如果达到1000次，打印所有记录的时间
        if (times_index == 1000) {
            int i;
            s64 total_time_ns = 0;
            s64 min_time_ns = forward_pass_times[0];
            s64 max_time_ns = forward_pass_times[0];
            
            for (i = 0; i < 1000; i++) {
                s64 time = forward_pass_times[i];
                total_time_ns += time;
                if (time < min_time_ns) min_time_ns = time;
                if (time > max_time_ns) max_time_ns = time;
            }
            total_time_ns -= min_time_ns;
            total_time_ns -= max_time_ns;
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %lld ns\n", total_time_ns / 998);
            printk(KERN_INFO "===================================================\n");
            
            // 重置统计
            times_index = 0;
            // 不清除数组，下次写入会覆盖
        }
    }
    
    spin_unlock_irqrestore(&times_lock, flags);
    
    return output;
}
#else
int jc_mlp_main(struct jc_lb_data *data)
{
    int output;
    dtype input[NR_FEAT];
    dtype delta_faults;
    ktime_t start_time, end_time;
    s64 elapsed_time_ns;
    unsigned long flags;

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

    // 更新统计信息
    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_time_ns, &forward_pass_total_time_ns);

    // 记录执行时间到数组
    spin_lock_irqsave(&times_lock, flags);
    
    if (times_index < 1000) {
        forward_pass_times[times_index] = elapsed_time_ns;
        times_index++;
        
        // 如果达到1000次，打印所有记录的时间
        if (times_index == 1000) {
            int i;
            s64 total_time_ns = 0;
            s64 min_time_ns = forward_pass_times[0];
            s64 max_time_ns = forward_pass_times[0];
            
            for (i = 0; i < 1000; i++) {
                s64 time = forward_pass_times[i];
                total_time_ns += time;
                if (time < min_time_ns) min_time_ns = time;
                if (time > max_time_ns) max_time_ns = time;
            }
            total_time_ns -= min_time_ns;
            total_time_ns -= max_time_ns;
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %lld ns\n", total_time_ns / 998);
            printk(KERN_INFO "===================================================\n");
            
            // 重置统计
            times_index = 0;
            // 不清除数组，下次写入会覆盖
        }
    }
    
    spin_unlock_irqrestore(&times_lock, flags);
    
    return output;
}
#endif


