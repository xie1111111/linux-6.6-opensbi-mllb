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

KSYMTAB_FUNC(drm_gem_dma_create, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_free, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_dumb_create_internal, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_dumb_create, "_gpl", "");
KSYMTAB_DATA(drm_gem_dma_vm_ops, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_print_info, "", "");
KSYMTAB_FUNC(drm_gem_dma_get_sg_table, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_prime_import_sg_table, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_vmap, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_mmap, "_gpl", "");
KSYMTAB_FUNC(drm_gem_dma_prime_import_sg_table_vmap, "", "");
KSYMTAB_FUNC(drm_fbdev_dma_setup, "", "");
KSYMTAB_FUNC(drm_fb_dma_get_gem_obj, "_gpl", "");
KSYMTAB_FUNC(drm_fb_dma_get_gem_addr, "_gpl", "");
KSYMTAB_FUNC(drm_fb_dma_sync_non_coherent, "_gpl", "");

MODULE_INFO(depends, "drm,drm_kms_helper");

