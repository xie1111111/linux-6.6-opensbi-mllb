#!/bin/bash
# QEMU Ubuntu中的模块测试脚本

echo "=== JC_MLP模块测试脚本 ==="

# 配置
MODULE_NAME="jc_mlp_module"
MODULE_FILE="./${MODULE_NAME}.ko"
DEBUGFS_DIR="/sys/kernel/debug/jc_mlp"

# 检查模块文件
if [ ! -f "$MODULE_FILE" ]; then
    echo "错误: 模块文件不存在: $MODULE_FILE"
    echo "请确保模块文件已传输到当前目录"
    exit 1
fi

# 1. 清理旧模块
echo "1. 清理旧模块..."
if lsmod | grep -q $MODULE_NAME; then
    sudo rmmod $MODULE_NAME
    echo "  已卸载旧模块"
else
    echo "  无旧模块"
fi

# 2. 挂载debugfs（如果未挂载）
if [ ! -d "/sys/kernel/debug" ]; then
    echo "2. 挂载debugfs..."
    sudo mount -t debugfs none /sys/kernel/debug
    echo "  debugfs已挂载"
fi

# 3. 加载模块
echo "3. 加载模块..."
sudo insmod "$MODULE_FILE"

# 检查是否加载成功
if lsmod | grep -q $MODULE_NAME; then
    echo "  ✓ 模块加载成功"
    echo "  模块信息:"
    sudo modinfo $MODULE_NAME | grep -E "version|description"
else
    echo "  ✗ 模块加载失败"
    echo "  错误信息:"
    dmesg | tail -10
    exit 1
fi

# 4. 检查debugfs接口
echo "4. 检查debugfs接口..."
if [ -d "$DEBUGFS_DIR" ]; then
    echo "  ✓ Debugfs接口已创建"
    echo "  可用文件:"
    ls -la $DEBUGFS_DIR/
else
    echo "  ✗ Debugfs接口未创建"
    dmesg | tail -10
    exit 1
fi

# 5. 查看初始统计
echo -e "\n5. 初始统计信息:"
cat $DEBUGFS_DIR/stats

# 6. 执行测试推理
echo -e "\n6. 执行MLP推理测试:"
for i in {1..3}; do
    echo "  第 $i 次推理..."
    echo "1" | sudo tee $DEBUGFS_DIR/run > /dev/null
    sleep 0.1
done

# 7. 查看内核日志
echo -e "\n7. 内核日志:"
dmesg | tail -15 | grep -E "JC_MLP|forward_pass|completed"

# 8. 查看最终统计
echo -e "\n8. 最终统计信息:"
cat $DEBUGFS_DIR/stats

# 9. 卸载模块
echo -e "\n9. 卸载模块..."
sudo rmmod $MODULE_NAME
if [ $? -eq 0 ]; then
    echo "  ✓ 模块已卸载"
else
    echo "  ✗ 模块卸载失败"
fi

# 10. 最终验证
echo -e "\n10. 验证模块已卸载:"
if lsmod | grep -q $MODULE_NAME; then
    echo "  ✗ 模块仍在加载"
else
    echo "  ✓ 模块已成功卸载"
fi

echo -e "\n=== 测试完成 ==="
echo ""
echo "说明:"
echo "  要再次测试，只需运行: sudo ./test_module.sh"
echo "  或手动操作:"
echo "    sudo insmod jc_mlp_test_module.ko"
echo "    echo 1 > /sys/kernel/debug/jc_mlp/run"
echo "    cat /sys/kernel/debug/jc_mlp/stats"
echo "    sudo rmmod jc_mlp_test_module"