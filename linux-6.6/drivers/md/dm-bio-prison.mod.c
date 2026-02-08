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

KSYMTAB_FUNC(dm_bio_prison_create, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_destroy, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_alloc_cell, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_free_cell, "_gpl", "");
KSYMTAB_FUNC(dm_cell_key_has_valid_range, "", "");
KSYMTAB_FUNC(dm_bio_detain, "_gpl", "");
KSYMTAB_FUNC(dm_get_cell, "_gpl", "");
KSYMTAB_FUNC(dm_cell_release, "_gpl", "");
KSYMTAB_FUNC(dm_cell_release_no_holder, "_gpl", "");
KSYMTAB_FUNC(dm_cell_error, "_gpl", "");
KSYMTAB_FUNC(dm_cell_visit_release, "_gpl", "");
KSYMTAB_FUNC(dm_cell_promote_or_release, "_gpl", "");
KSYMTAB_FUNC(dm_deferred_set_create, "_gpl", "");
KSYMTAB_FUNC(dm_deferred_set_destroy, "_gpl", "");
KSYMTAB_FUNC(dm_deferred_entry_inc, "_gpl", "");
KSYMTAB_FUNC(dm_deferred_entry_dec, "_gpl", "");
KSYMTAB_FUNC(dm_deferred_set_add_work, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_create_v2, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_destroy_v2, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_alloc_cell_v2, "_gpl", "");
KSYMTAB_FUNC(dm_bio_prison_free_cell_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_get_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_put_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_lock_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_quiesce_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_lock_promote_v2, "_gpl", "");
KSYMTAB_FUNC(dm_cell_unlock_v2, "_gpl", "");

MODULE_INFO(depends, "");

