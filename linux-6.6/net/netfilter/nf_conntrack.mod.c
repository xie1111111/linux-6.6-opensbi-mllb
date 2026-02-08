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

KSYMTAB_DATA(nf_conntrack_locks, "_gpl", "");
KSYMTAB_DATA(nf_conntrack_expect_lock, "_gpl", "");
KSYMTAB_DATA(nf_conntrack_hash, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_lock, "_gpl", "");
KSYMTAB_DATA(nf_conntrack_htable_size, "_gpl", "");
KSYMTAB_DATA(nf_conntrack_max, "_gpl", "");
KSYMTAB_FUNC(nf_ct_get_tuplepr, "_gpl", "");
KSYMTAB_FUNC(nf_ct_invert_tuple, "_gpl", "");
KSYMTAB_FUNC(nf_ct_get_id, "_gpl", "");
KSYMTAB_FUNC(nf_ct_tmpl_alloc, "_gpl", "");
KSYMTAB_FUNC(nf_ct_tmpl_free, "_gpl", "");
KSYMTAB_FUNC(nf_ct_destroy, "", "");
KSYMTAB_FUNC(nf_ct_delete, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_find_get, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_hash_check_insert, "_gpl", "");
KSYMTAB_FUNC(nf_ct_acct_add, "_gpl", "");
KSYMTAB_FUNC(__nf_conntrack_confirm, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_tuple_taken, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_alloc, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_free, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_in, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_alter_reply, "_gpl", "");
KSYMTAB_FUNC(__nf_ct_refresh_acct, "_gpl", "");
KSYMTAB_FUNC(nf_ct_kill_acct, "_gpl", "");
KSYMTAB_FUNC(nf_ct_iterate_cleanup_net, "_gpl", "");
KSYMTAB_FUNC(nf_ct_iterate_destroy, "_gpl", "");
KSYMTAB_FUNC(nf_ct_alloc_hashtable, "_gpl", "");
KSYMTAB_FUNC(__nf_ct_change_timeout, "_gpl", "");
KSYMTAB_FUNC(__nf_ct_change_status, "_gpl", "");
KSYMTAB_FUNC(nf_ct_change_status_common, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_count, "_gpl", "");
KSYMTAB_DATA(nf_ct_expect_hsize, "_gpl", "");
KSYMTAB_DATA(nf_ct_expect_hash, "_gpl", "");
KSYMTAB_FUNC(nf_ct_unlink_expect_report, "_gpl", "");
KSYMTAB_FUNC(nf_ct_remove_expect, "_gpl", "");
KSYMTAB_FUNC(__nf_ct_expect_find, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_find_get, "_gpl", "");
KSYMTAB_FUNC(nf_ct_remove_expectations, "_gpl", "");
KSYMTAB_FUNC(nf_ct_unexpect_related, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_alloc, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_init, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_put, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_related_report, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_iterate_destroy, "_gpl", "");
KSYMTAB_FUNC(nf_ct_expect_iterate_net, "_gpl", "");
KSYMTAB_DATA(nf_ct_helper_hash, "_gpl", "");
KSYMTAB_DATA(nf_ct_helper_hsize, "_gpl", "");
KSYMTAB_FUNC(__nf_conntrack_helper_find, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helper_try_module_get, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helper_put, "_gpl", "");
KSYMTAB_FUNC(nf_nat_helper_try_module_get, "_gpl", "");
KSYMTAB_FUNC(nf_nat_helper_put, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_ext_add, "_gpl", "");
KSYMTAB_FUNC(__nf_ct_try_assign_helper, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_expectfn_register, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_expectfn_unregister, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_expectfn_find_by_name, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_expectfn_find_by_symbol, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_log, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helper_register, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helper_unregister, "_gpl", "");
KSYMTAB_FUNC(nf_ct_helper_init, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helpers_register, "_gpl", "");
KSYMTAB_FUNC(nf_conntrack_helpers_unregister, "_gpl", "");
KSYMTAB_FUNC(nf_nat_helper_register, "_gpl", "");
KSYMTAB_FUNC(nf_nat_helper_unregister, "_gpl", "");
KSYMTAB_FUNC(nf_l4proto_log_invalid, "_gpl", "");
KSYMTAB_FUNC(nf_ct_l4proto_log_invalid, "_gpl", "");
KSYMTAB_FUNC(nf_ct_l4proto_find, "_gpl", "");
KSYMTAB_FUNC(nf_confirm, "_gpl", "");
KSYMTAB_FUNC(nf_ct_netns_get, "_gpl", "");
KSYMTAB_FUNC(nf_ct_netns_put, "_gpl", "");
KSYMTAB_FUNC(nf_ct_bridge_register, "_gpl", "");
KSYMTAB_FUNC(nf_ct_bridge_unregister, "_gpl", "");
KSYMTAB_FUNC(nf_ct_ext_add, "", "");
KSYMTAB_FUNC(__nf_ct_ext_find, "", "");
KSYMTAB_FUNC(nf_ct_seqadj_init, "_gpl", "");
KSYMTAB_FUNC(nf_ct_seqadj_set, "_gpl", "");
KSYMTAB_FUNC(nf_ct_tcp_seqadj_set, "_gpl", "");
KSYMTAB_FUNC(nf_ct_seq_adjust, "_gpl", "");
KSYMTAB_FUNC(nf_ct_seq_offset, "_gpl", "");

MODULE_INFO(depends, "nf_defrag_ipv4,nf_defrag_ipv6,libcrc32c");

