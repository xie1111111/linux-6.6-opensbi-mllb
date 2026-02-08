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

KSYMTAB_FUNC(xt_register_target, "", "");
KSYMTAB_FUNC(xt_unregister_target, "", "");
KSYMTAB_FUNC(xt_register_targets, "", "");
KSYMTAB_FUNC(xt_unregister_targets, "", "");
KSYMTAB_FUNC(xt_register_match, "", "");
KSYMTAB_FUNC(xt_unregister_match, "", "");
KSYMTAB_FUNC(xt_register_matches, "", "");
KSYMTAB_FUNC(xt_unregister_matches, "", "");
KSYMTAB_FUNC(xt_find_match, "", "");
KSYMTAB_FUNC(xt_request_find_match, "_gpl", "");
KSYMTAB_FUNC(xt_request_find_target, "_gpl", "");
KSYMTAB_FUNC(xt_data_to_user, "_gpl", "");
KSYMTAB_FUNC(xt_match_to_user, "_gpl", "");
KSYMTAB_FUNC(xt_target_to_user, "_gpl", "");
KSYMTAB_FUNC(xt_find_revision, "_gpl", "");
KSYMTAB_FUNC(xt_check_proc_name, "", "");
KSYMTAB_FUNC(xt_check_match, "_gpl", "");
KSYMTAB_FUNC(xt_check_table_hooks, "", "");
KSYMTAB_FUNC(xt_check_entry_offsets, "", "");
KSYMTAB_FUNC(xt_alloc_entry_offsets, "", "");
KSYMTAB_FUNC(xt_find_jump_offset, "", "");
KSYMTAB_FUNC(xt_check_target, "_gpl", "");
KSYMTAB_FUNC(xt_copy_counters, "_gpl", "");
KSYMTAB_FUNC(xt_alloc_table_info, "", "");
KSYMTAB_FUNC(xt_free_table_info, "", "");
KSYMTAB_FUNC(xt_find_table, "", "");
KSYMTAB_FUNC(xt_find_table_lock, "_gpl", "");
KSYMTAB_FUNC(xt_request_find_table_lock, "_gpl", "");
KSYMTAB_FUNC(xt_table_unlock, "_gpl", "");
KSYMTAB_DATA(xt_recseq, "_gpl", "");
KSYMTAB_DATA(xt_tee_enabled, "_gpl", "");
KSYMTAB_FUNC(xt_counters_alloc, "", "");
KSYMTAB_FUNC(xt_replace_table, "_gpl", "");
KSYMTAB_FUNC(xt_register_table, "_gpl", "");
KSYMTAB_FUNC(xt_unregister_table, "_gpl", "");
KSYMTAB_FUNC(xt_hook_ops_alloc, "_gpl", "");
KSYMTAB_FUNC(xt_register_template, "_gpl", "");
KSYMTAB_FUNC(xt_unregister_template, "_gpl", "");
KSYMTAB_FUNC(xt_proto_init, "_gpl", "");
KSYMTAB_FUNC(xt_proto_fini, "_gpl", "");
KSYMTAB_FUNC(xt_percpu_counter_alloc, "_gpl", "");
KSYMTAB_FUNC(xt_percpu_counter_free, "_gpl", "");

MODULE_INFO(depends, "");

