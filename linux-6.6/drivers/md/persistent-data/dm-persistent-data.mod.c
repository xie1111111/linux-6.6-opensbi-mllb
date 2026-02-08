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
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

KSYMTAB_FUNC(dm_array_info_init, "_gpl", "");
KSYMTAB_FUNC(dm_array_empty, "_gpl", "");
KSYMTAB_FUNC(dm_array_resize, "_gpl", "");
KSYMTAB_FUNC(dm_array_new, "_gpl", "");
KSYMTAB_FUNC(dm_array_del, "_gpl", "");
KSYMTAB_FUNC(dm_array_get_value, "_gpl", "");
KSYMTAB_FUNC(dm_array_set_value, "_gpl", "");
KSYMTAB_FUNC(dm_array_walk, "_gpl", "");
KSYMTAB_FUNC(dm_array_cursor_begin, "_gpl", "");
KSYMTAB_FUNC(dm_array_cursor_end, "_gpl", "");
KSYMTAB_FUNC(dm_array_cursor_next, "_gpl", "");
KSYMTAB_FUNC(dm_array_cursor_skip, "_gpl", "");
KSYMTAB_FUNC(dm_array_cursor_get_value, "_gpl", "");
KSYMTAB_FUNC(dm_disk_bitset_init, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_empty, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_new, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_resize, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_del, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_flush, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_set_bit, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_clear_bit, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_test_bit, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_cursor_begin, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_cursor_end, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_cursor_next, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_cursor_skip, "_gpl", "");
KSYMTAB_FUNC(dm_bitset_cursor_get_value, "_gpl", "");
KSYMTAB_FUNC(dm_block_location, "_gpl", "");
KSYMTAB_FUNC(dm_block_data, "_gpl", "");
KSYMTAB_FUNC(dm_block_manager_create, "_gpl", "");
KSYMTAB_FUNC(dm_block_manager_destroy, "_gpl", "");
KSYMTAB_FUNC(dm_block_manager_reset, "_gpl", "");
KSYMTAB_FUNC(dm_bm_block_size, "_gpl", "");
KSYMTAB_FUNC(dm_bm_read_lock, "_gpl", "");
KSYMTAB_FUNC(dm_bm_write_lock, "_gpl", "");
KSYMTAB_FUNC(dm_bm_write_lock_zero, "_gpl", "");
KSYMTAB_FUNC(dm_bm_unlock, "_gpl", "");
KSYMTAB_FUNC(dm_bm_flush, "_gpl", "");
KSYMTAB_FUNC(dm_bm_is_read_only, "_gpl", "");
KSYMTAB_FUNC(dm_bm_set_read_only, "_gpl", "");
KSYMTAB_FUNC(dm_bm_set_read_write, "_gpl", "");
KSYMTAB_FUNC(dm_bm_checksum, "_gpl", "");
KSYMTAB_FUNC(dm_sm_disk_create, "_gpl", "");
KSYMTAB_FUNC(dm_sm_disk_open, "_gpl", "");
KSYMTAB_FUNC(dm_tm_create_non_blocking_clone, "_gpl", "");
KSYMTAB_FUNC(dm_tm_destroy, "_gpl", "");
KSYMTAB_FUNC(dm_tm_pre_commit, "_gpl", "");
KSYMTAB_FUNC(dm_tm_commit, "_gpl", "");
KSYMTAB_FUNC(dm_tm_shadow_block, "_gpl", "");
KSYMTAB_FUNC(dm_tm_read_lock, "_gpl", "");
KSYMTAB_FUNC(dm_tm_unlock, "_gpl", "");
KSYMTAB_FUNC(dm_tm_inc, "_gpl", "");
KSYMTAB_FUNC(dm_tm_inc_range, "_gpl", "");
KSYMTAB_FUNC(dm_tm_dec, "_gpl", "");
KSYMTAB_FUNC(dm_tm_dec_range, "_gpl", "");
KSYMTAB_FUNC(dm_tm_with_runs, "_gpl", "");
KSYMTAB_FUNC(dm_tm_issue_prefetches, "_gpl", "");
KSYMTAB_FUNC(dm_tm_create_with_sm, "_gpl", "");
KSYMTAB_FUNC(dm_tm_open_with_sm, "_gpl", "");
KSYMTAB_FUNC(dm_btree_empty, "_gpl", "");
KSYMTAB_FUNC(dm_btree_del, "_gpl", "");
KSYMTAB_FUNC(dm_btree_lookup, "_gpl", "");
KSYMTAB_FUNC(dm_btree_lookup_next, "_gpl", "");
KSYMTAB_FUNC(dm_btree_insert, "_gpl", "");
KSYMTAB_FUNC(dm_btree_insert_notify, "_gpl", "");
KSYMTAB_FUNC(dm_btree_find_highest_key, "_gpl", "");
KSYMTAB_FUNC(dm_btree_find_lowest_key, "_gpl", "");
KSYMTAB_FUNC(dm_btree_walk, "_gpl", "");
KSYMTAB_FUNC(dm_btree_cursor_begin, "_gpl", "");
KSYMTAB_FUNC(dm_btree_cursor_end, "_gpl", "");
KSYMTAB_FUNC(dm_btree_cursor_next, "_gpl", "");
KSYMTAB_FUNC(dm_btree_cursor_skip, "_gpl", "");
KSYMTAB_FUNC(dm_btree_cursor_get_value, "_gpl", "");
KSYMTAB_FUNC(dm_btree_remove, "_gpl", "");
KSYMTAB_FUNC(dm_btree_remove_leaves, "_gpl", "");

MODULE_INFO(depends, "dm-bufio,libcrc32c");

