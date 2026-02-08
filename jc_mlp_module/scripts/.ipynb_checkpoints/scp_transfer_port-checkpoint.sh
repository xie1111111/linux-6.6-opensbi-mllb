#!/bin/bash
# SCP传输脚本 - 适配端口2222

set -e  # 遇到错误退出

echo "=== JC_MLP模块编译与传输脚本（端口2222）==="

# 配置参数（与您的SCP指令匹配）
SCP_PORT="2222"
SCP_USER="ubuntu"
SCP_HOST="localhost"  # 由于端口转发，使用localhost
REMOTE_DIR="/home/$SCP_USER/modules"
MODULE_FILE="jc_mlp_test_module.ko"

# 检查内核目录
if [ -z "$KERNEL_DIR" ]; then
    export KERNEL_DIR="$HOME/autodl-tmp/linux-6.6"
fi

if [ ! -d "$KERNEL_DIR" ]; then
    echo "错误: 内核目录不存在: $KERNEL_DIR"
    echo "请确保已设置正确的KERNEL_DIR环境变量"
    exit 1
fi

echo "内核目录: $KERNEL_DIR"
echo "目标地址: $SCP_USER@$SCP_HOST:$REMOTE_DIR"
echo "端口: $SCP_PORT"

# 1. 编译模块
echo "步骤1: 编译模块..."
make

if [ $? -ne 0 ]; then
    echo "✗ 编译失败!"
    exit 1
fi
echo "✓ 编译成功: $MODULE_FILE"

# 2. 检查模块文件
if [ ! -f "$MODULE_FILE" ]; then
    echo "✗ 模块文件不存在: $MODULE_FILE"
    exit 1
fi

# 3. 传输模块文件
echo "步骤2: 传输模块到QEMU Ubuntu..."
echo "命令: scp -P $SCP_PORT $MODULE_FILE $SCP_USER@$SCP_HOST:$REMOTE_DIR/"

scp -P $SCP_PORT $MODULE_FILE $SCP_USER@$SCP_HOST:$REMOTE_DIR/

if [ $? -eq 0 ]; then
    echo "✓ 传输成功!"
else
    echo "✗ 传输失败!"
    echo "可能的错误原因:"
    echo "  1. SSH端口2222未正确转发"
    echo "  2. QEMU Ubuntu未运行SSH服务"
    echo "  3. 用户名或密码错误"
    exit 1
fi

# 4. 可选：传输测试脚本
echo "步骤3: 传输测试脚本..."
if [ -f "scripts/test_module.sh" ]; then
    scp -P $SCP_PORT scripts/test_module.sh $SCP_USER@$SCP_HOST:$REMOTE_DIR/
    ssh -p $SCP_PORT $SCP_USER@$SCP_HOST "chmod +x $REMOTE_DIR/test_module.sh"
    echo "✓ 测试脚本传输完成"
else
    echo "⚠  测试脚本不存在，跳过"
fi

echo ""
echo "================== 操作完成 =================="
echo ""
echo "在QEMU Ubuntu中执行以下命令:"
echo "1. 连接到QEMU Ubuntu:"
echo "   ssh -p $SCP_PORT $SCP_USER@$SCP_HOST"
echo ""
echo "2. 加载和测试模块:"
echo "   cd $REMOTE_DIR"
echo "   # 如果传输了测试脚本"
echo "   sudo ./test_module.sh"
echo "   # 或者手动执行"
echo "   sudo insmod $MODULE_FILE"
echo "   echo 1 > /sys/kernel/debug/jc_mlp/run"
echo "   cat /sys/kernel/debug/jc_mlp/stats"
echo "   sudo rmmod jc_mlp_test_module"
echo ""
echo "3. 查看内核日志:"
echo "   dmesg | tail -20"
echo ""
echo "============================================"