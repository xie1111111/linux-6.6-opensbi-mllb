// SPDX-License-Identifier: GPL-2.0
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/atomic.h>
#include <linux/compiler.h>
#include <linux/smp.h>
#include <linux/cpuhotplug.h>
#include <asm/io.h>
#include <asm/page.h>
#include <asm/sbi.h>
#include "jc_sbi_ml.h"
#include "jc_mlp.h"

// 添加全局变量记录forward_pass的统计信息
static atomic64_t forward_pass_count = ATOMIC64_INIT(0);
static atomic64_t forward_pass_total_cycle = ATOMIC64_INIT(0);

static inline unsigned long long rdcycle_read(void) {
    unsigned long long cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}
#define NR_FEAT     15
#define ftod(F)     ftodtype(F)

// 全局共享内存池
static struct ml_shared_mem {
    Tensor t_W1;
    Tensor t_B1;
    Tensor t_W2;
    Tensor t_B2;
} ml_shared;

static int ml_shared_inited = 0;

int is_jc_sched = 0;
EXPORT_SYMBOL(is_jc_sched);

/* 权重数据（保持不变） */
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

/* ---------- per-CPU 标志和启用函数 ---------- */
static DEFINE_PER_CPU(bool, cycle_counter_enabled);

static void enable_cycle_counter_on_cpu(void *info)
{
    struct sbiret ret;
    unsigned long counter_idx;
    int cpu = smp_processor_id();

    if (__this_cpu_read(cycle_counter_enabled)) {
        pr_info("RVSML-MLLB: CPU%d already enabled, skipping\n", cpu);
        return;
    }

    pr_info("RVSML-MLLB: CPU%d: Attempting to enable cycle counter...\n", cpu);

    /* 配置计数器，让 OpenSBI 分配一个计数器监控 CPU 周期事件 */
    ret = sbi_ecall(SBI_EXT_PMU, SBI_EXT_PMU_COUNTER_CFG_MATCH,
                    0, 0x3FFFFUL, 0, SBI_PMU_HW_CPU_CYCLES, 0, 0);
    if (ret.error) {
        pr_err("RVSML-MLLB: CPU%d: sbi_ecall(CFG_MATCH) failed, error=%ld\n", cpu, ret.error);
        return;
    }
    counter_idx = ret.value;
    pr_info("RVSML-MLLB: CPU%d: got counter index %lu\n", cpu, counter_idx);

    /* 假设计数器已自动启动，不再显式调用 START */
    __this_cpu_write(cycle_counter_enabled, true);
    pr_info("RVSML-MLLB: CPU%d: cycle counter enabled (assumed started).\n", cpu);

    /* 验证：读取一次 rdcycle 值 */
    unsigned long long val = rdcycle_read();
    pr_info("RVSML-MLLB: CPU%d: rdcycle = %llu\n", cpu, val);
}

/* CPU hotplug 回调：每个 CPU 上线时调用启用函数 */
static int sched_pmu_cpu_online(unsigned int cpu)
{
    smp_call_function_single(cpu, enable_cycle_counter_on_cpu, NULL, 1);
    return 0;
}
/* ---------- 结束 ---------- */

// 初始化共享内存
static int jc_mlp_sched_init(void)
{
    if (READ_ONCE(ml_shared_inited)) {
        return 0;
    }
    memset(&ml_shared, 0, sizeof(struct ml_shared_mem));
    create_tensor4d(ml_shared.t_W1, __pa(w1), 1, NR_FEAT, 10, 1);
    create_tensor4d(ml_shared.t_B1, __pa(b1), 1, 1, 10, 1);
    create_tensor4d(ml_shared.t_W2, __pa(w2), 1, 10, 1, 1);
    create_tensor4d(ml_shared.t_B2, __pa(b2), 1, 1, 1, 1);
    
    WRITE_ONCE(ml_shared_inited, 1);
    pr_info("RVSML-MLLB: Shared memory initialized\n");
    return 0;
}

// forward_pass函数（作为内核组件）
static int forward_pass(dtype *input_data) {
    struct sbiret ret;
    dtype *o1;
    dtype *o2;
    Tensor *input;
    Tensor *out1;
    Tensor *out2;
    
    o1 = kmalloc(sizeof(dtype) * 10, GFP_ATOMIC);
    o2 = kmalloc(sizeof(dtype) * 1, GFP_ATOMIC);
    input = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    out1 = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    out2 = kmalloc(sizeof(Tensor), GFP_ATOMIC);
    
    if (!o1 || !o2 || !input || !out1 || !out2) {
        pr_err("RVSML-MLLB: kmalloc failed\n");
        kfree(input); kfree(out1); kfree(out2); kfree(o1); kfree(o2);
        return -1;
    }
    
    if (jc_mlp_sched_init() != 0) {
        pr_err("RVSML-MLLB: jc_mlp_sched_init failed\n");
        kfree(input); kfree(out1); kfree(out2); kfree(o1); kfree(o2);
        return -1;
    }
    
    create_tensor4d(*input, __pa(input_data), 1, 1, NR_FEAT, 1);
    create_tensor4d(*out1, __pa(o1), 1, 1, 10, 1);
    create_tensor4d(*out2, __pa(o2), 1, 1, 1, 1);
    
    pr_debug("RVSML-MLLB: Forward pass via SBI starting...\n");
    
    ret = matmul(out1, input, &ml_shared.t_W1);
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 1) failed: %ld\n", ret.error);
        goto fail;
    }
    ret = tensor_add(out1, out1, &ml_shared.t_B1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 1 bias) failed: %ld\n", ret.error);
        goto fail;
    }
    ret = tensor_relu(out1, out1);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_relu (layer 1) failed: %ld\n", ret.error);
        goto fail;
    }
    ret = matmul(out2, out1, &ml_shared.t_W2);
    if (ret.error) {
        pr_err("RVSML-MLLB: matmul (layer 4) failed: %ld\n", ret.error);
        goto fail;
    }
    ret = tensor_add(out2, out2, &ml_shared.t_B2);
    if (ret.error) {
        pr_err("RVSML-MLLB: tensor_add (layer 5 bias) failed: %ld\n", ret.error);
        goto fail;
    }
    
    dtype final_output = o2[0];
    kfree(input); kfree(out1); kfree(out2); kfree(o1); kfree(o2);
    return final_output > ftod(0.5) ? 1 : 0;

fail:
    kfree(input); kfree(out1); kfree(out2); kfree(o1); kfree(o2);
    return -1;
}

// 保持原有的jc_mlp_main函数，仅修改forward_pass调用
#ifdef CONFIG_JC_SCHED_FXDPT
int jc_mlp_main(struct jc_lb_data *data)
{
    int output;
    dtype *input;
    dtype delta_faults;
    unsigned long long start_cycle, end_cycle;
    unsigned long long elapsed_cycle;

    input = kmalloc(sizeof(dtype) * NR_FEAT, GFP_ATOMIC);
    if (!input) {
        pr_err("RVSML-MLLB: kmalloc input failed\n");
        return -1;
    }
    
    if (data->total_faults)
        delta_faults = dtype_div(itodtype(data->delta_faults), itodtype(data->total_faults));
    else
        delta_faults = itodtype(data->delta_faults);

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

    start_cycle = rdcycle_read();
    output = forward_pass(input);
    end_cycle = rdcycle_read();
    elapsed_cycle = end_cycle - start_cycle;
    
    kfree(input);

    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_cycle, &forward_pass_total_cycle);
    
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_cycle = atomic64_xchg(&forward_pass_total_cycle, 0);
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %llu cycle\n",
                   total_cycle / total_count);
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
    dtype delta_faults;
    unsigned long long start_cycle, end_cycle;
    unsigned long long elapsed_cycle;

    input = kmalloc(sizeof(dtype) * NR_FEAT, GFP_ATOMIC);
    if (!input) {
        pr_err("RVSML-MLLB: kmalloc input failed\n");
        return -1;
    }
    
    if (data->total_faults)
        delta_faults = (dtype)data->delta_faults / data->total_faults;
    else
        delta_faults = (dtype)data->delta_faults;

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

    start_cycle = rdcycle_read();
    output = forward_pass(input);
    end_cycle = rdcycle_read();
    elapsed_cycle = end_cycle - start_cycle;

    kfree(input);

    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed_cycle, &forward_pass_total_cycle);
    
    if (atomic64_read(&forward_pass_count) % 1000 == 0) {
        u64 total_count = atomic64_xchg(&forward_pass_count, 0);
        u64 total_cycle = atomic64_xchg(&forward_pass_total_cycle, 0);
        if (total_count == 1000) {
            printk(KERN_INFO "=== jc_mlp forward_pass average time per execution ===\n");
            printk(KERN_INFO "Average time per execution: %llu cycle\n",
                   total_cycle / total_count);
            printk(KERN_INFO "===================================================\n");
        }
    }
    
    return output;
}
#endif

/* ---------- initcall 注册 hotplug 回调 ---------- */
static int __init jc_mlp_initcall(void)
{
    int ret;

    jc_mlp_sched_init();

    ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN,
                            "sched/jc_mlp:online",
                            sched_pmu_cpu_online,
                            NULL);
    if (ret < 0)
        pr_err("RVSML-MLLB: Failed to register CPU hotplug callback, error=%d\n", ret);
    else
        pr_info("RVSML-MLLB: CPU hotplug callback registered (state=%d)\n", ret);

    return 0;
}
core_initcall(jc_mlp_initcall);
/* ---------- 结束 ---------- */