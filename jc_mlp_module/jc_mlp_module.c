#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/atomic.h>
#include <linux/compiler.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <asm/io.h>
#include <asm/page.h>
#include "jc_mlp_module.h"

// ==================== 模块信息 ====================
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Standalone MLP Test Module");
MODULE_VERSION("1.0");

// ==================== 参数定义 ====================
#define NR_FEAT     15  // 特征数量
#define ftod(F)     ftodtype(F)
// ==================== 全局变量 ====================
// 权重和偏置数组（保持与原始jc_mlp.c相同）
static dtype w1[] = {
    ftod(0.565644),  ftod(0.384824), ftod(-0.042528), ftod(-0.264426),  ftod(0.472312),
    ftod(-0.282259), ftod(-0.014167), ftod(-0.528233),  ftod(0.622656), ftod(-0.373769),
    ftod(0.287381),  ftod(1.005889),  ftod(0.181242), ftod(-1.291967),  ftod(1.100194),
    ftod(-0.772200), ftod(-0.235354), ftod(-0.829178),  ftod(0.248697),  ftod(1.168082),
    ftod(-0.281433), ftod(-0.546903),  ftod(0.032876),  ftod(0.559641), ftod(-0.228221),
    ftod(0.103177),  ftod(0.620234),  ftod(0.318789), ftod(-0.633047), ftod(-0.006017),
    ftod(0.047218),  ftod(0.084886), ftod(-0.134755),  ftod(0.645489), ftod(-0.277912),
    ftod(0.517039),  ftod(0.651821), ftod(-0.285480), ftod(-0.003520), ftod(-0.437448),
    ftod(-0.161385), ftod(-0.442559), ftod(-0.035489),  ftod(0.570436),  ftod(0.079949),
    ftod(0.741253),  ftod(0.291243),  ftod(0.586947), ftod(-0.180183), ftod(-0.177284),
    ftod(-0.396542),  ftod(0.055728),  ftod(0.112597),  ftod(0.317440), ftod(-0.177967),
    ftod(0.211646), ftod(-0.254014), ftod(-0.166693), ftod(-0.414425),  ftod(0.561991),
    ftod(0.407785),  ftod(0.664266), ftod(-0.077182), ftod(-0.454090),  ftod(0.397967),
    ftod(0.089694), ftod(-0.946674), ftod(-0.246415),  ftod(0.240792), ftod(-0.013765),
    ftod(-0.322740), ftod(-0.332058),  ftod(0.104680),  ftod(0.449407), ftod(-0.545375),
    ftod(0.934457),  ftod(0.600992),  ftod(0.594059), ftod(-0.398014),  ftod(0.048134),
    ftod(0.199440),  ftod(0.236234), ftod(-0.549774),  ftod(0.362871),  ftod(0.128888),
    ftod(-0.064394),  ftod(0.194858),  ftod(0.173756), ftod(-0.087557),  ftod(0.147654),
    ftod(0.133639),  ftod(0.000841), ftod(-0.001098),  ftod(0.626147), ftod(-0.152287),
    ftod(0.110689),  ftod(0.108449), ftod(-0.463610),  ftod(0.171219),  ftod(0.310098),
    ftod(-0.440701),  ftod(0.361575), ftod(-0.302418),  ftod(0.573317),  ftod(0.322387),
    ftod(0.602443), ftod(-0.314726),  ftod(0.031837),  ftod(0.124628), ftod(-0.135573),
    ftod(0.159068), ftod(-0.059842), ftod(-0.526570), ftod(-0.010963),  ftod(0.311802),
    ftod(0.360409), ftod(-0.103766),  ftod(0.363927), ftod(-0.428252),  ftod(0.085832),
    ftod(-0.080852),  ftod(0.010944), ftod(-0.331394),  ftod(0.068851),  ftod(0.145650),
    ftod(0.842668),  ftod(0.369900), ftod(-0.027606), ftod(-0.326165), ftod(-0.271815),
    ftod(-0.219882), ftod(-0.526053), ftod(-0.540803),  ftod(0.893084), ftod(-1.002251),
    ftod(0.007923),  ftod(1.298324),  ftod(0.295529), ftod(-0.469116), ftod(-0.790421),
    ftod(0.936136),  ftod(0.879596), ftod(-0.094900), ftod(-0.326074),  ftod(0.891442),
    ftod(-1.032957), ftod(-0.173408), ftod(-0.906972),  ftod(0.650875),  ftod(0.917579),
};

static dtype b1[] = {
    ftod(-0.257286), ftod(-0.220656), ftod(-0.312300),
    ftod(0.485314), ftod(-0.377361), ftod(0.445350),
    ftod(0.321995), ftod(0.456795), ftod(-0.164362), ftod(-0.260494),
};

static dtype w2[] = {
    ftod(-0.409050), ftod(-0.578690), ftod(-0.446989),
    ftod(0.361227), ftod(-0.401546), ftod(0.258594),
    ftod(0.760240), ftod(0.524665), ftod(-0.385637), ftod(-0.721390),
};

static dtype b2[] = { ftod(0.405319) };

// 共享内存结构体
static struct ml_shared_mem {
    Tensor t_W1;
    Tensor t_B1;
    Tensor t_W2;
    Tensor t_B2;
} ml_shared;

static int ml_shared_inited = 0;

// 统计信息
static atomic64_t forward_pass_count = ATOMIC64_INIT(0);
static atomic64_t forward_pass_total_cycles = ATOMIC64_INIT(0);

// DebugFS相关
static struct dentry *jc_mlp_dir;
static struct dentry *jc_mlp_run_file;
static struct dentry *jc_mlp_stats_file;

// ==================== 辅助函数 ====================
// 读取cycle计数器
static inline unsigned long long rdcycle_read(void) {
    unsigned long long cycles;
    // 使用memory clobber防止优化
    asm volatile (
        "rdcycle %0\n"
        : "=r"(cycles)
        : 
        : "memory"
    );
    return cycles;
}

// SBI扩展测试函数
static void test_sbi_ml_extension(void) {
    struct sbiret ret;
    
    pr_info("=== SBI环境测试 ===\n");
    
    // 测试SBI基础扩展
    ret = sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_GET_SBI_VERSION, 
                    0, 0, 0, 0, 0, 0);
    pr_info("SBI版本测试: error=%s, value=%lx\n", 
           sbi_error_str(ret.error), ret.value);
    
    // 探测ML扩展
    ret = sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_PROBE_EXTENSION,
                    SBI_EXT_ML, 0, 0, 0, 0, 0);
    pr_info("ML扩展探测: error=%s, value=%ld (1=存在, 0=不存在)\n", 
           sbi_error_str(ret.error), ret.value);
    
    if (ret.value != 1) {
        pr_err("❌ SBI ML扩展不可用！这是Matmul错误的根本原因。\n");
        pr_err("   请检查QEMU是否启用了ML扩展，或OpenSBI是否编译了ML支持。\n");
    } else {
        pr_info("✅ SBI ML扩展可用\n");
    }
}

// 初始化共享内存 - 关键修复部分
static int jc_mlp_sched_init(void) {
    if (READ_ONCE(ml_shared_inited)) {
        return 0;
    }
    
    memset(&ml_shared, 0, sizeof(struct ml_shared_mem));
    
    // 关键修复：正确设置Tensor形状
    // 注意：create_tensor4d参数顺序是(tensor, data, N, H, W, C)
    
    // W1: 15x10权重矩阵 [N=1, H=15, W=10, C=1]
    // 您的w1数组有150个元素，应该是15行×10列
    create_tensor4d(ml_shared.t_W1, __pa(w1), 1, 15, 10, 1);
    
    // B1: 10维偏置向量 [N=1, H=1, W=10, C=1]
    create_tensor4d(ml_shared.t_B1, __pa(b1), 1, 1, 10, 1);
    
    // W2: 10x1权重矩阵 [N=1, H=10, W=1, C=1]
    create_tensor4d(ml_shared.t_W2, __pa(w2), 1, 10, 1, 1);
    
    // B2: 1维标量 [N=1, H=1, W=1, C=1]
    create_tensor4d(ml_shared.t_B2, __pa(b2), 1, 1, 1, 1);
    
    WRITE_ONCE(ml_shared_inited, 1);
    
    // 详细调试信息
    pr_info("JC_MLP_TEST: Tensor形状设置:\n");
    pr_info("  W1: [%d,%d,%d,%d] (应有150元素，实际%d)\n",
           ml_shared.t_W1.shape[0], ml_shared.t_W1.shape[1],
           ml_shared.t_W1.shape[2], ml_shared.t_W1.shape[3],
           ml_shared.t_W1.size);
    pr_info("  B1: [%d,%d,%d,%d]\n",
           ml_shared.t_B1.shape[0], ml_shared.t_B1.shape[1],
           ml_shared.t_B1.shape[2], ml_shared.t_B1.shape[3]);
    pr_info("  W2: [%d,%d,%d,%d] (应有10元素，实际%d)\n",
           ml_shared.t_W2.shape[0], ml_shared.t_W2.shape[1],
           ml_shared.t_W2.shape[2], ml_shared.t_W2.shape[3],
           ml_shared.t_W2.size);
    pr_info("  B2: [%d,%d,%d,%d]\n",
           ml_shared.t_B2.shape[0], ml_shared.t_B2.shape[1],
           ml_shared.t_B2.shape[2], ml_shared.t_B2.shape[3]);
    
    // 验证物理地址
    pr_info("JC_MLP_TEST: 物理地址验证:\n");
    pr_info("  w1数组: va=%p, pa=%lx\n", w1, __pa(w1));
    pr_info("  &ml_shared.t_W1: va=%p, pa=%lx\n", 
            &ml_shared.t_W1, __pa(&ml_shared.t_W1));
    pr_info("  W1行地址: va=%p, pa=%lx\n",
            &ml_shared.t_W1.shape[1], __pa(&ml_shared.t_W1.shape[1]));
    pr_info("  W2行地址: va=%p, pa=%lx\n",
            &ml_shared.t_W2.shape[1], __pa(&ml_shared.t_W2.shape[1]));
    
    return 0;
}

// ==================== forward_pass函数 ====================
static int forward_pass(dtype *input_data) {
    struct sbiret ret;
    dtype *o1, *o2;
    Tensor *input, *out1, *out2;
    unsigned long long start_cycles, end_cycles;
    int result = 0;
    
    // 验证rdcycle是否工作
    unsigned long long test1 = rdcycle_read();
    for (int i = 0; i < 100; i++) {
        asm volatile("nop");
    }
    unsigned long long test2 = rdcycle_read();
    pr_debug("JC_MLP_DEBUG: rdcycle测试: %llu -> %llu (delta=%llu)\n",
             test1, test2, test2 - test1);
    
    // 开始测量
    barrier();
    start_cycles = rdcycle_read();
    
    // 动态分配内存
    o1 = kmalloc(sizeof(dtype) * 10, GFP_KERNEL);
    o2 = kmalloc(sizeof(dtype) * 1, GFP_KERNEL);
    input = kmalloc(sizeof(Tensor), GFP_KERNEL);
    out1 = kmalloc(sizeof(Tensor), GFP_KERNEL);
    out2 = kmalloc(sizeof(Tensor), GFP_KERNEL);
    
    if (!o1 || !o2 || !input || !out1 || !out2) {
        pr_err("JC_MLP_TEST: kmalloc失败\n");
        kfree(o1); kfree(o2); kfree(input); kfree(out1); kfree(out2);
        return -1;
    }
    
    // 初始化Tensor
    // 输入: [1, 1, 15, 1] (1行15列)
    create_tensor4d(*input, __pa(input_data), 1, 1, NR_FEAT, 1);
    create_tensor4d(*out1, __pa(o1), 1, 1, 10, 1);
    create_tensor4d(*out2, __pa(o2), 1, 1, 1, 1);
    
    pr_debug("JC_MLP_DEBUG: 输入形状: [%d,%d,%d,%d]\n",
            input->shape[0], input->shape[1], 
            input->shape[2], input->shape[3]);
    
    // Layer 1: Matmul (输入 * W1)
    pr_debug("JC_MLP_DEBUG: 执行第一层Matmul...\n");
    pr_info("matmul第三个参数的全部内容1:\ndata地址:%p\nshape:[%d,%d,%d,%d]\nsize:%d\n",
            ml_shared.t_W1.data,ml_shared.t_W1.shape[0],ml_shared.t_W1.shape[1],
            ml_shared.t_W1.shape[2],ml_shared.t_W1.shape[3],ml_shared.t_W1.size);
    ret = matmul(out1, input, &ml_shared.t_W1);
    pr_info("matmul第三个参数的全部内容2:\ndata地址:%p\nshape:[%d,%d,%d,%d]\nsize:%d\n",
            ml_shared.t_W1.data,ml_shared.t_W1.shape[0],ml_shared.t_W1.shape[1],
            ml_shared.t_W1.shape[2],ml_shared.t_W1.shape[3],ml_shared.t_W1.size);
    if (ret.error) {
        pr_err("JC_MLP_TEST: matmul (layer 1)失败: %s (error=%ld, value=%ld)\n", 
               sbi_error_str(ret.error), ret.error, ret.value);
        pr_err("JC_MLP_TEST: 输入列数=%d, W1行数=%d\n",
               input->shape[2], ml_shared.t_W1.shape[1]);
        goto cleanup;
    }
    
    // Layer 2: Add Bias
    pr_debug("JC_MLP_DEBUG: 执行第一层偏置...\n");
    ret = tensor_add(out1, out1, &ml_shared.t_B1);
    if (ret.error) {
        pr_err("JC_MLP_TEST: tensor_add (layer 1 bias)失败: %s\n", 
               sbi_error_str(ret.error));
        goto cleanup;
    }
    
    // Layer 3: ReLU
    pr_debug("JC_MLP_DEBUG: 执行ReLU激活...\n");
    ret = tensor_relu(out1, out1);
    if (ret.error) {
        pr_err("JC_MLP_TEST: tensor_relu失败: %s\n", sbi_error_str(ret.error));
        goto cleanup;
    }
    
    // Layer 4: Matmul (out1 * W2)
    pr_debug("JC_MLP_DEBUG: 执行第二层Matmul...\n");
    ret = matmul(out2, out1, &ml_shared.t_W2);
    if (ret.error) {
        pr_err("JC_MLP_TEST: matmul (layer 2)失败: %s (error=%ld, value=%ld)\n", 
               sbi_error_str(ret.error), ret.error, ret.value);
        pr_err("JC_MLP_TEST: out1列数=%d, W2行数=%d\n",
               out1->shape[2], ml_shared.t_W2.shape[1]);
        goto cleanup;
    }
    
    // Layer 5: Add Bias
    pr_debug("JC_MLP_DEBUG: 执行第二层偏置...\n");
    ret = tensor_add(out2, out2, &ml_shared.t_B2);
    if (ret.error) {
        pr_err("JC_MLP_TEST: tensor_add (layer 2 bias)失败: %s\n", 
               sbi_error_str(ret.error));
        goto cleanup;
    }
    
    // 结束测量
    end_cycles = rdcycle_read();
    barrier();
    
    unsigned long long elapsed = end_cycles - start_cycles;
    
    // 获取结果
    dtype final_output = o2[0];
    result = final_output > ftod(0.5) ? 1 : 0;
    
    pr_info("JC_MLP_TEST: forward_pass完成, 耗时=%llu cycles, 结果=%d, 输出值=%d\n", 
            elapsed, result, (int)final_output);
    
    // 如果elapsed为0，可能是QEMU限制
    if (elapsed == 0) {
        pr_warn("JC_MLP_TEST: 警告: cycle计数为0。可能是:\n");
        pr_warn("  1. QEMU未模拟cycle计数器\n");
        pr_warn("  2. SBI调用失败导致提前返回\n");
        pr_warn("  3. 代码被编译器优化\n");
    }
    
    // 更新统计
    atomic64_inc(&forward_pass_count);
    atomic64_add(elapsed, &forward_pass_total_cycles);
    
cleanup:
    // 清理内存
    kfree(input); kfree(out1); kfree(out2); kfree(o1); kfree(o2);
    
    return result;
}

// ==================== jc_mlp_main函数（无参数版本） ====================
int jc_mlp_main(void) {
    int result;
    dtype *input;
    
    pr_info("JC_MLP_TEST: 开始MLP推理...\n");
    
    // 1. 确保共享内存已初始化
    if (jc_mlp_sched_init() != 0) {
        pr_err("JC_MLP_TEST: 初始化失败\n");
        return -1;
    }
    
    // 2. 分配输入内存
    input = kmalloc(sizeof(dtype) * NR_FEAT, GFP_KERNEL);
    if (!input) {
        pr_err("JC_MLP_TEST: 无法分配输入内存\n");
        return -1;
    }
    
    // 3. 生成测试输入数据
    pr_debug("JC_MLP_TEST: 准备测试输入...\n");
    input[0] = itodtype(10);   // src_non_pref
    input[1] = itodtype(5);    // delta_hot
    input[2] = itodtype(3);    // cpu_idle (定点数表示0.3)
    input[3] = itodtype(7);    // cpu_not_idle
    input[4] = itodtype(2);    // cpu_newly_idle
    input[5] = itodtype(1);    // same_node
    input[6] = itodtype(0);    // prefer_src
    input[7] = itodtype(1);    // prefer_dst
    input[8] = itodtype(3);    // src_len - 2
    input[9] = itodtype(50);   // src_load / 1000
    input[10] = itodtype(30);  // dst_load / 1000
    input[11] = itodtype(4);   // dst_len
    input[12] = itodtype(1);   // delta_faults (定点数表示0.1)
    input[13] = itodtype(2);   // extra_fails
    input[14] = itodtype(1);   // buddy_hot
    
    // 4. 执行推理
    result = forward_pass(input);
    
    // 5. 释放输入内存
    kfree(input);
    
    pr_info("JC_MLP_TEST: MLP推理完成，结果: %d (1=迁移, 0=不迁移)\n", result);
    
    return result;
}
EXPORT_SYMBOL(jc_mlp_main);

// ==================== DebugFS接口 ====================
static ssize_t jc_mlp_run_write(struct file *file, const char __user *buf,
                                size_t count, loff_t *ppos)
{
    int result;
    char cmd;
    
    if (count == 0 || count > 2) {
        pr_err("JC_MLP_TEST: 期望1-2个字符\n");
        return -EINVAL;
    }
    
    if (copy_from_user(&cmd, buf, 1)) {
        return -EFAULT;
    }
    
    // 接受"1"或"1\n"
    if (cmd != '1') {
        pr_err("JC_MLP_TEST: 只接受'1' (收到0x%x)\n", cmd);
        return -EINVAL;
    }
    
    // 执行MLP推理
    result = jc_mlp_main();
    
    pr_info("JC_MLP_TEST: DebugFS触发推理，结果=%d\n", result);
    
    return count;  // 返回处理的字符数
}

static ssize_t jc_mlp_run_read(struct file *file, char __user *buf,
                               size_t count, loff_t *ppos)
{
    const char *msg = "写入 '1' 到此文件以触发MLP推理\n";
    return simple_read_from_buffer(buf, count, ppos, msg, strlen(msg));
}

static int jc_mlp_stats_show(struct seq_file *m, void *v)
{
    u64 count = atomic64_read(&forward_pass_count);
    u64 total_cycles = atomic64_read(&forward_pass_total_cycles);
    
    seq_printf(m, "JC_MLP 模块统计信息\n");
    seq_printf(m, "===================\n");
    seq_printf(m, "总推理次数: %llu\n", count);
    
    if (count > 0) {
        seq_printf(m, "总消耗CPU周期: %llu\n", total_cycles);
        seq_printf(m, "平均每次推理周期: %llu\n", total_cycles / count);
        
        // 如果平均周期为0，显示警告
        if (total_cycles / count == 0) {
            seq_printf(m, "\n⚠️  警告: 平均周期为0\n");
            seq_printf(m, "可能原因:\n");
            seq_printf(m, "1. QEMU未模拟cycle计数器\n");
            seq_printf(m, "2. SBI调用失败\n");
            seq_printf(m, "3. 代码被优化\n");
        }
    } else {
        seq_printf(m, "尚未执行任何推理\n");
    }
    
    seq_printf(m, "\n使用方法:\n");
    seq_printf(m, "触发推理: echo 1 > /sys/kernel/debug/jc_mlp/run\n");
    seq_printf(m, "查看统计: cat /sys/kernel/debug/jc_mlp/stats\n");
    seq_printf(m, "卸载模块: sudo rmmod jc_mlp_test_module\n");
    
    return 0;
}

static int jc_mlp_stats_open(struct inode *inode, struct file *file)
{
    return single_open(file, jc_mlp_stats_show, NULL);
}

static const struct file_operations jc_mlp_run_fops = {
    .owner = THIS_MODULE,
    .read = jc_mlp_run_read,
    .write = jc_mlp_run_write,
};

static const struct file_operations jc_mlp_stats_fops = {
    .owner = THIS_MODULE,
    .open = jc_mlp_stats_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

// ==================== 模块初始化函数 ====================
static int __init jc_mlp_test_init(void)
{
    pr_info("JC_MLP_TEST: 模块加载中...\n");
    
    // 1. 首先测试SBI环境
    test_sbi_ml_extension();
    
    // 2. 初始化共享内存
    if (jc_mlp_sched_init() != 0) {
        pr_err("JC_MLP_TEST: 共享内存初始化失败\n");
        return -ENOMEM;
    }
    
    // 3. 创建debugfs目录和文件
    jc_mlp_dir = debugfs_create_dir("jc_mlp", NULL);
    if (!jc_mlp_dir) {
        pr_err("JC_MLP_TEST: 创建debugfs目录失败\n");
        return -ENOMEM;
    }
    
    jc_mlp_run_file = debugfs_create_file("run", 0644, jc_mlp_dir, NULL, &jc_mlp_run_fops);
    jc_mlp_stats_file = debugfs_create_file("stats", 0444, jc_mlp_dir, NULL, &jc_mlp_stats_fops);
    
    if (!jc_mlp_run_file || !jc_mlp_stats_file) {
        pr_err("JC_MLP_TEST: 创建debugfs文件失败\n");
        debugfs_remove_recursive(jc_mlp_dir);
        return -ENOMEM;
    }
    
    pr_info("JC_MLP_TEST: 模块加载成功\n");
    pr_info("JC_MLP_TEST: Debugfs接口位于 /sys/kernel/debug/jc_mlp/\n");
    
    // 4. 执行一次初始测试
    pr_info("JC_MLP_TEST: 执行初始测试推理...\n");
    int result = jc_mlp_main();
    pr_info("JC_MLP_TEST: 初始测试结果: %d\n", result);
    
    return 0;
}

// ==================== 模块退出函数 ====================
static void __exit jc_mlp_test_exit(void)
{
    // 打印最终统计
    u64 total_count = atomic64_read(&forward_pass_count);
    u64 total_cycles = atomic64_read(&forward_pass_total_cycles);
    
    pr_info("JC_MLP_TEST: 最终统计:\n");
    pr_info("  总推理次数: %llu\n", total_count);
    
    if (total_count > 0) {
        pr_info("  总周期数: %llu\n", total_cycles);
        pr_info("  平均周期/次: %llu\n", total_cycles / total_count);
        
        if (total_cycles / total_count == 0) {
            pr_warn("JC_MLP_TEST: 注意: 平均周期为0\n");
            pr_warn("  这可能表明QEMU未正确模拟cycle计数器，或SBI调用失败\n");
        }
    }
    
    // 清理debugfs
    debugfs_remove_recursive(jc_mlp_dir);
    
    // 清理标志
    WRITE_ONCE(ml_shared_inited, 0);
    
    pr_info("JC_MLP_TEST: 模块卸载完成\n");
}

module_init(jc_mlp_test_init);
module_exit(jc_mlp_test_exit);