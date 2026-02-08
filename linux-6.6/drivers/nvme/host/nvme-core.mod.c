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

KSYMTAB_DATA(admin_timeout, "_gpl", "");
KSYMTAB_DATA(nvme_io_timeout, "_gpl", "");
KSYMTAB_DATA(nvme_wq, "_gpl", "");
KSYMTAB_DATA(nvme_reset_wq, "_gpl", "");
KSYMTAB_DATA(nvme_delete_wq, "_gpl", "");
KSYMTAB_FUNC(nvme_try_sched_reset, "_gpl", "");
KSYMTAB_FUNC(nvme_reset_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_delete_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_complete_rq, "_gpl", "");
KSYMTAB_FUNC(nvme_complete_batch_req, "_gpl", "");
KSYMTAB_FUNC(nvme_host_path_error, "_gpl", "");
KSYMTAB_FUNC(nvme_cancel_request, "_gpl", "");
KSYMTAB_FUNC(nvme_cancel_tagset, "_gpl", "");
KSYMTAB_FUNC(nvme_cancel_admin_tagset, "_gpl", "");
KSYMTAB_FUNC(nvme_change_ctrl_state, "_gpl", "");
KSYMTAB_FUNC(nvme_wait_reset, "_gpl", "");
KSYMTAB_FUNC(nvme_put_ns, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(nvme_init_request, "_gpl", "");
KSYMTAB_FUNC(nvme_fail_nonready_command, "_gpl", "");
KSYMTAB_FUNC(__nvme_check_ready, "_gpl", "");
KSYMTAB_FUNC(nvme_cleanup_cmd, "_gpl", "");
KSYMTAB_FUNC(nvme_setup_cmd, "_gpl", "");
KSYMTAB_FUNC(nvme_execute_rq, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(__nvme_submit_sync_cmd, "_gpl", "");
KSYMTAB_FUNC(nvme_submit_sync_cmd, "_gpl", "");
KSYMTAB_FUNC(nvme_command_effects, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(nvme_passthru_start, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(nvme_passthru_end, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(nvme_stop_keep_alive, "_gpl", "");
KSYMTAB_FUNC(nvme_set_features, "_gpl", "");
KSYMTAB_FUNC(nvme_get_features, "_gpl", "");
KSYMTAB_FUNC(nvme_set_queue_count, "_gpl", "");
KSYMTAB_FUNC(nvme_disable_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_enable_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_init_ctrl_finish, "_gpl", "");
KSYMTAB_FUNC(nvme_find_get_ns, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_FUNC(nvme_remove_namespaces, "_gpl", "");
KSYMTAB_FUNC(nvme_complete_async_event, "_gpl", "");
KSYMTAB_FUNC(nvme_alloc_admin_tag_set, "_gpl", "");
KSYMTAB_FUNC(nvme_remove_admin_tag_set, "_gpl", "");
KSYMTAB_FUNC(nvme_alloc_io_tag_set, "_gpl", "");
KSYMTAB_FUNC(nvme_remove_io_tag_set, "_gpl", "");
KSYMTAB_FUNC(nvme_stop_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_start_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_uninit_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_init_ctrl, "_gpl", "");
KSYMTAB_FUNC(nvme_mark_namespaces_dead, "_gpl", "");
KSYMTAB_FUNC(nvme_unfreeze, "_gpl", "");
KSYMTAB_FUNC(nvme_wait_freeze_timeout, "_gpl", "");
KSYMTAB_FUNC(nvme_wait_freeze, "_gpl", "");
KSYMTAB_FUNC(nvme_start_freeze, "_gpl", "");
KSYMTAB_FUNC(nvme_quiesce_io_queues, "_gpl", "");
KSYMTAB_FUNC(nvme_unquiesce_io_queues, "_gpl", "");
KSYMTAB_FUNC(nvme_quiesce_admin_queue, "_gpl", "");
KSYMTAB_FUNC(nvme_unquiesce_admin_queue, "_gpl", "");
KSYMTAB_FUNC(nvme_sync_io_queues, "_gpl", "");
KSYMTAB_FUNC(nvme_sync_queues, "_gpl", "");
KSYMTAB_FUNC(nvme_ctrl_from_file, "_gpl", "NVME_TARGET_PASSTHRU");
KSYMTAB_DATA(nvme_dev_attrs_group, "_gpl", "");

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "F8C7B4639CEEA502EACA7F9");
