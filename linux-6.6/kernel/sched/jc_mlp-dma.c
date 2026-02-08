#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/printk.h>
#include <linux/spinlock.h>
#include <linux/dma-mapping.h>  // 添加dma_alloc_coherent支持
#include <asm/io.h>
#include <asm/page.h>
#include <asm/sbi.h>
#include "jc_sbi_ml.h"

#include "jc_mlp.h"

// 添加全局变量记录forward_pass的统计信息
static atomic64_t forward_pass_count = ATOMIC64_INIT(0);
static atomic64_t forward_pass_total_time_ns = ATOMIC64_INIT(0);

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

static dma_addr_t ml_shared_dma_handle;  // DMA映射的物理地址
static atomic_t ml_shared_initialized = ATOMIC_INIT(0); // 原子变量保护初始化状态
static DEFINE_SPINLOCK(ml_lock);

// 静态参数的DMA句柄（替代__pa()，提升兼容性）
static dma_addr_t w1_dma, b1_dma, w2_dma, b2_dma;

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
    // 使用dma_alloc_coherent分配连续物理内存（推荐后续替换为具体dev指针，提升兼容性）
    ml_shared = dma_alloc_coherent(NULL, sizeof(*ml_shared), 
                                   &ml_shared_dma_handle, GFP_KERNEL);
    if (!ml_shared) {
        pr_err("RVSML-MLLB: Failed to allocate DMA-coherent memory\n");
        return -ENOMEM;
    }
    
    pr_info("RVSML-MLLB: DMA-coherent memory allocated: virt=%p, phys=%pad\n", 
            ml_shared, &ml_shared_dma_handle);
    
    memset(ml_shared, 0, sizeof(*ml_shared));

    // 为静态参数映射DMA地址（替代__pa()，提升跨平台兼容性）
    w1_dma = dma_map_single(NULL, w1, sizeof(w1), DMA_TO_DEVICE);
    b1_dma = dma_map_single(NULL, b1, sizeof(b1), DMA_TO_DEVICE);
    w2_dma = dma_map_single(NULL, w2, sizeof(w2), DMA_TO_DEVICE);
    b2_dma = dma_map_single(NULL, b2, sizeof(b2), DMA_TO_DEVICE);
    
    // 检查DMA映射是否成功（部分平台支持dma_mapping_error判断）
    if (dma_mapping_error(NULL, w1_dma) || dma_mapping_error(NULL, b1_dma) ||
        dma_mapping_error(NULL, w2_dma) || dma_mapping_error(NULL, b2_dma)) {
        pr_err("RVSML-MLLB: DMA map for static params failed\n");
        dma_free_coherent(NULL, sizeof(*ml_shared), ml_shared, ml_shared_dma_handle);
        ml_shared = NULL;
        return -EIO;
    }

    // 初始化Tensor结构体 (使用DMA地址，shape格式: [N, H, W, C])
    // 所有tensor都指向定点数数组
    create_tensor4d(ml_shared->t_input,
            ml_shared_dma_handle + offsetof(struct ml_shared_mem, input), 
            1, 1, NR_FEAT, 1);  // [1, 1, 15, 1] - 1x15向量
    create_tensor4d(ml_shared->t_W1,
            w1_dma, 1, NR_FEAT, 10, 1);                 // [1, 15, 10, 1] - 15x10矩阵
    create_tensor4d(ml_shared->t_B1,
            b1_dma, 1, 1, 10, 1);                       // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_out1,
            ml_shared_dma_handle + offsetof(struct ml_shared_mem, o1), 
            1, 1, 10, 1);            // [1, 1, 10, 1] - 1x10向量
    create_tensor4d(ml_shared->t_W2,
            w2_dma, 1, 10, 1, 1);                       // [1, 10, 1, 1] - 10x1矩阵
    create_tensor4d(ml_shared->t_B2,
            b2_dma, 1, 1, 1, 1);                        // [1, 1, 1, 1] - 1x1标量
    create_tensor4d(ml_shared->t_out2,
            ml_shared_dma_handle + offsetof(struct ml_shared_mem, o2), 
            1, 1, 1, 1);             // [1, 1, 1, 1] - 1x1标量
    
    pr_info("RVSML-MLLB: DMA-coherent shared memory initialized\n");
    return 0;
}

// 清理函数（完整释放所有资源，无内存泄漏）
static void cleanup_ml_shared_mem(void)
{
    if (ml_shared) {
        // 解映射静态参数的DMA地址
        dma_unmap_single(NULL, w1_dma, sizeof(w1), DMA_TO_DEVICE);
        dma_unmap_single(NULL, b1_dma, sizeof(b1), DMA_TO_DEVICE);
        dma_unmap_single(NULL, w2_dma, sizeof(w2), DMA_TO_DEVICE);
        dma_unmap_single(NULL, b2_dma, sizeof(b2), DMA_TO_DEVICE);
        
        // 释放共享内存的DMA一致性内存
        dma_free_coherent(NULL, sizeof(*ml_shared), ml_shared, ml_shared_dma_handle);
        ml_shared = NULL;
        atomic_set(&ml_shared_initialized, 0);
        pr_info("RVSML-MLLB: DMA-coherent memory freed\n");
    }
}

// 优化后的精细内存屏障（减少性能开销）
static inline void ml_wmb(void) {
    wmb(); // 写内存屏障：保证之前的所有写操作完成后，再执行后续指令
}

static inline void ml_rmb(void) {
    rmb(); // 读内存屏障：保证后续的所有读操作，获取到最新的内存写入值
}

// forward_pass函数（作为内核组件，优化后更健壮、高效）
static int forward_pass(dtype *input_data) {
    struct sbiret ret;
    unsigned long flags;
    
    // 双重检查+原子保护：避免多核并发重复初始化（高效且安全）
    if (atomic_read(&ml_shared_initialized) == 0) {
        spin_lock(&ml_lock); // 加锁防止并发初始化竞争
        if (atomic_read(&ml_shared_initialized) == 0) { // 二次检查，避免后续核重复初始化
            if (init_ml_shared_mem() == 0) {
                atomic_set(&ml_shared_initialized, 1); // 初始化成功后，设置原子变量为1
            } else {
                pr_err("RVSML-MLLB: Failed to initialize ml shared mem in forward_pass\n");
                spin_unlock(&ml_lock);
                return -1;
            }
        }
        spin_unlock(&ml_lock);
    }
    
    // 加锁保护共享内存访问，防止多核数据竞争
    spin_lock_irqsave(&ml_lock, flags);
    
    // 1. 复制输入数据（定点数格式）
    memcpy(ml_shared->input, input_data, NR_FEAT * sizeof(dtype));

    // 2. 写屏障：保证输入数据完全写入，再执行后续MLP推理（不可移除）
    ml_wmb();
    
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
    
    // 4. 读屏障：保证推理结果完全写入，再读取o2[0]（不可移除）
    ml_rmb();
    
    // 5. 获取最终结果 (定点数格式)
    dtype final_output = ml_shared->o2[0];
    
    spin_unlock_irqrestore(&ml_lock, flags);

    return final_output > ftod(0.5) ? 1 : 0;
}

// 保持原有的jc_mlp_main函数，整合所有优化点
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
    
    // 每1000次打印统计，然后重置数据（避免值过大）
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        // 原子交换：读取当前值，并将原子变量重置为 0（无锁安全）
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_time = atomic64_xchg(&forward_pass_total_time_ns, 0);

        // 这里判断 total_count 是否为 1000（避免多核并发时，多次触发打印）
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %llu ns\n", total_time / total_count); // 优化格式化符为%llu，适配u64
            printk(KERN_INFO "===================================================\n");
        }
    }
    
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
    
    // 每1000次打印统计，然后重置数据（避免值过大）
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        // 原子交换：读取当前值，并将原子变量重置为 0（无锁安全）
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_time = atomic64_xchg(&forward_pass_total_time_ns, 0);

        // 这里判断 total_count 是否为 1000（避免多核并发时，多次触发打印）
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %llu ns\n", total_time / total_count); // 优化格式化符为%llu，适配u64
            printk(KERN_INFO "===================================================\n");
        }
    }

    return output;
}
#endif