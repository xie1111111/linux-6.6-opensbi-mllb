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

KSYMTAB_FUNC(drm_gem_shmem_create, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_free, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_put_pages, "", "");
KSYMTAB_FUNC(drm_gem_shmem_pin, "", "");
KSYMTAB_FUNC(drm_gem_shmem_unpin, "", "");
KSYMTAB_FUNC(drm_gem_shmem_vmap, "", "");
KSYMTAB_FUNC(drm_gem_shmem_vunmap, "", "");
KSYMTAB_FUNC(drm_gem_shmem_madvise, "", "");
KSYMTAB_FUNC(drm_gem_shmem_purge, "", "");
KSYMTAB_FUNC(drm_gem_shmem_dumb_create, "_gpl", "");
KSYMTAB_DATA(drm_gem_shmem_vm_ops, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_mmap, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_print_info, "", "");
KSYMTAB_FUNC(drm_gem_shmem_get_sg_table, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_get_pages_sgt, "_gpl", "");
KSYMTAB_FUNC(drm_gem_shmem_prime_import_sg_table, "_gpl", "");

MODULE_INFO(depends, "drm");

