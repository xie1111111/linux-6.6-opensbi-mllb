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

KSYMTAB_FUNC(dm_bufio_get, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_read, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_new, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_prefetch, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_release, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_mark_partial_buffer_dirty, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_mark_buffer_dirty, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_write_dirty_buffers_async, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_write_dirty_buffers, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_issue_flush, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_issue_discard, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_forget, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_forget_buffers, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_set_minimum_buffers, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_block_size, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_device_size, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_dm_io_client, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_block_number, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_block_data, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_aux_data, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_get_client, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_client_create, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_client_destroy, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_client_reset, "_gpl", "");
KSYMTAB_FUNC(dm_bufio_set_sector_offset, "_gpl", "");

MODULE_INFO(depends, "dm-mod");

