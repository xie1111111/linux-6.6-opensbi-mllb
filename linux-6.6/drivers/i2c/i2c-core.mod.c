#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

KSYMTAB_FUNC(i2c_freq_mode_string, "_gpl", "");
KSYMTAB_FUNC(i2c_match_id, "_gpl", "");
KSYMTAB_FUNC(i2c_get_match_data, "", "");
KSYMTAB_FUNC(i2c_generic_scl_recovery, "_gpl", "");
KSYMTAB_FUNC(i2c_recover_bus, "_gpl", "");
KSYMTAB_DATA(i2c_bus_type, "_gpl", "");
KSYMTAB_DATA(i2c_client_type, "_gpl", "");
KSYMTAB_FUNC(i2c_verify_client, "", "");
KSYMTAB_FUNC(i2c_new_client_device, "_gpl", "");
KSYMTAB_FUNC(i2c_unregister_device, "_gpl", "");
KSYMTAB_FUNC(i2c_find_device_by_fwnode, "", "");
KSYMTAB_FUNC(i2c_new_dummy_device, "_gpl", "");
KSYMTAB_FUNC(devm_i2c_new_dummy_device, "_gpl", "");
KSYMTAB_FUNC(i2c_new_ancillary_device, "_gpl", "");
KSYMTAB_FUNC(i2c_adapter_depth, "_gpl", "");
KSYMTAB_DATA(i2c_adapter_type, "_gpl", "");
KSYMTAB_FUNC(i2c_verify_adapter, "", "");
KSYMTAB_FUNC(i2c_handle_smbus_host_notify, "_gpl", "");
KSYMTAB_FUNC(i2c_add_adapter, "", "");
KSYMTAB_FUNC(i2c_add_numbered_adapter, "_gpl", "");
KSYMTAB_FUNC(i2c_del_adapter, "", "");
KSYMTAB_FUNC(devm_i2c_add_adapter, "_gpl", "");
KSYMTAB_FUNC(i2c_find_adapter_by_fwnode, "", "");
KSYMTAB_FUNC(i2c_get_adapter_by_fwnode, "", "");
KSYMTAB_FUNC(i2c_parse_fw_timings, "_gpl", "");
KSYMTAB_FUNC(i2c_for_each_dev, "_gpl", "");
KSYMTAB_FUNC(i2c_register_driver, "", "");
KSYMTAB_FUNC(i2c_del_driver, "", "");
KSYMTAB_FUNC(i2c_clients_command, "", "");
KSYMTAB_FUNC(__i2c_transfer, "", "");
KSYMTAB_FUNC(i2c_transfer, "", "");
KSYMTAB_FUNC(i2c_transfer_buffer_flags, "", "");
KSYMTAB_FUNC(i2c_get_device_id, "_gpl", "");
KSYMTAB_FUNC(i2c_client_get_device_id, "_gpl", "");
KSYMTAB_FUNC(i2c_probe_func_quick_read, "_gpl", "");
KSYMTAB_FUNC(i2c_new_scanned_device, "_gpl", "");
KSYMTAB_FUNC(i2c_get_adapter, "", "");
KSYMTAB_FUNC(i2c_put_adapter, "", "");
KSYMTAB_FUNC(i2c_get_dma_safe_msg_buf, "_gpl", "");
KSYMTAB_FUNC(i2c_put_dma_safe_msg_buf, "_gpl", "");
KSYMTAB_FUNC(i2c_smbus_pec, "", "");
KSYMTAB_FUNC(i2c_smbus_read_byte, "", "");
KSYMTAB_FUNC(i2c_smbus_write_byte, "", "");
KSYMTAB_FUNC(i2c_smbus_read_byte_data, "", "");
KSYMTAB_FUNC(i2c_smbus_write_byte_data, "", "");
KSYMTAB_FUNC(i2c_smbus_read_word_data, "", "");
KSYMTAB_FUNC(i2c_smbus_write_word_data, "", "");
KSYMTAB_FUNC(i2c_smbus_read_block_data, "", "");
KSYMTAB_FUNC(i2c_smbus_write_block_data, "", "");
KSYMTAB_FUNC(i2c_smbus_read_i2c_block_data, "", "");
KSYMTAB_FUNC(i2c_smbus_write_i2c_block_data, "", "");
KSYMTAB_FUNC(i2c_smbus_xfer, "", "");
KSYMTAB_FUNC(__i2c_smbus_xfer, "", "");
KSYMTAB_FUNC(i2c_smbus_read_i2c_block_data_or_emulated, "", "");
KSYMTAB_FUNC(i2c_new_smbus_alert_device, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_get_i2c_resource, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_client_count, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_find_bus_speed, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_find_adapter_by_handle, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_new_device_by_fwnode, "_gpl", "");
KSYMTAB_FUNC(i2c_acpi_waive_d0_probe, "_gpl", "");
KSYMTAB_FUNC(of_i2c_get_board_info, "_gpl", "");
KSYMTAB_FUNC(i2c_of_match_device, "_gpl", "");

MODULE_INFO(depends, "");

