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

KSYMTAB_FUNC(dm_per_bio_data, "_gpl", "");
KSYMTAB_FUNC(dm_bio_from_per_bio_data, "_gpl", "");
KSYMTAB_FUNC(dm_bio_get_target_bio_nr, "_gpl", "");
KSYMTAB_FUNC(dm_get_reserved_bio_based_ios, "_gpl", "");
KSYMTAB_FUNC(dm_start_time_ns_from_clone, "_gpl", "");
KSYMTAB_FUNC(dm_set_target_max_io_len, "_gpl", "");
KSYMTAB_FUNC(dm_accept_partial_bio, "_gpl", "");
KSYMTAB_FUNC(dm_submit_bio_remap, "_gpl", "");
KSYMTAB_FUNC(dm_get_md, "_gpl", "");
KSYMTAB_FUNC(dm_hold, "_gpl", "");
KSYMTAB_FUNC(dm_device_name, "_gpl", "");
KSYMTAB_FUNC(dm_put, "_gpl", "");
KSYMTAB_FUNC(dm_internal_suspend_noflush, "_gpl", "");
KSYMTAB_FUNC(dm_internal_resume, "_gpl", "");
KSYMTAB_FUNC(dm_internal_suspend_fast, "_gpl", "");
KSYMTAB_FUNC(dm_internal_resume_fast, "_gpl", "");
KSYMTAB_FUNC(dm_disk, "_gpl", "");
KSYMTAB_FUNC(dm_suspended, "_gpl", "");
KSYMTAB_FUNC(dm_post_suspending, "_gpl", "");
KSYMTAB_FUNC(dm_noflush_suspending, "_gpl", "");
KSYMTAB_FUNC(dm_get_device, "", "");
KSYMTAB_FUNC(dm_put_device, "", "");
KSYMTAB_FUNC(dm_read_arg, "", "");
KSYMTAB_FUNC(dm_read_arg_group, "", "");
KSYMTAB_FUNC(dm_shift_arg, "", "");
KSYMTAB_FUNC(dm_consume_args, "", "");
KSYMTAB_FUNC(dm_table_set_type, "_gpl", "");
KSYMTAB_FUNC(dm_table_event, "", "");
KSYMTAB_FUNC(dm_table_get_size, "", "");
KSYMTAB_FUNC(dm_table_get_mode, "", "");
KSYMTAB_FUNC(dm_table_get_md, "", "");
KSYMTAB_FUNC(dm_table_device_name, "_gpl", "");
KSYMTAB_FUNC(dm_table_run_md_queue_async, "", "");
KSYMTAB_FUNC(dm_register_target, "", "");
KSYMTAB_FUNC(dm_unregister_target, "", "");
KSYMTAB_FUNC(dm_copy_name_and_uuid, "_gpl", "");
KSYMTAB_FUNC(dm_io_client_create, "", "");
KSYMTAB_FUNC(dm_io_client_destroy, "", "");
KSYMTAB_FUNC(dm_io, "", "");
KSYMTAB_FUNC(dm_kcopyd_copy, "", "");
KSYMTAB_FUNC(dm_kcopyd_zero, "", "");
KSYMTAB_FUNC(dm_kcopyd_prepare_callback, "", "");
KSYMTAB_FUNC(dm_kcopyd_do_callback, "", "");
KSYMTAB_FUNC(dm_kcopyd_client_create, "", "");
KSYMTAB_FUNC(dm_kcopyd_client_destroy, "", "");
KSYMTAB_FUNC(dm_kcopyd_client_flush, "", "");
KSYMTAB_FUNC(dm_mq_kick_requeue_list, "", "");

MODULE_INFO(depends, "");

