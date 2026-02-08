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

KSYMTAB_FUNC(ttm_tt_init, "", "");
KSYMTAB_FUNC(ttm_tt_fini, "", "");
KSYMTAB_FUNC(ttm_sg_tt_init, "", "");
KSYMTAB_FUNC(ttm_tt_populate, "", "");
KSYMTAB_FUNC(ttm_kmap_iter_tt_init, "", "");
KSYMTAB_FUNC(ttm_tt_pages_limit, "", "");
KSYMTAB_FUNC(ttm_bo_move_to_lru_tail, "", "");
KSYMTAB_FUNC(ttm_bo_set_bulk_move, "", "");
KSYMTAB_FUNC(ttm_bo_put, "", "");
KSYMTAB_FUNC(ttm_bo_eviction_valuable, "", "");
KSYMTAB_FUNC(ttm_bo_pin, "", "");
KSYMTAB_FUNC(ttm_bo_unpin, "", "");
KSYMTAB_FUNC(ttm_bo_mem_space, "", "");
KSYMTAB_FUNC(ttm_bo_validate, "", "");
KSYMTAB_FUNC(ttm_bo_init_reserved, "", "");
KSYMTAB_FUNC(ttm_bo_init_validate, "", "");
KSYMTAB_FUNC(ttm_bo_unmap_virtual, "", "");
KSYMTAB_FUNC(ttm_bo_wait_ctx, "", "");
KSYMTAB_FUNC(ttm_move_memcpy, "", "");
KSYMTAB_FUNC(ttm_bo_move_memcpy, "", "");
KSYMTAB_FUNC(ttm_io_prot, "", "");
KSYMTAB_FUNC(ttm_bo_kmap, "", "");
KSYMTAB_FUNC(ttm_bo_kunmap, "", "");
KSYMTAB_FUNC(ttm_bo_vmap, "", "");
KSYMTAB_FUNC(ttm_bo_vunmap, "", "");
KSYMTAB_FUNC(ttm_bo_move_accel_cleanup, "", "");
KSYMTAB_FUNC(ttm_bo_move_sync_cleanup, "", "");
KSYMTAB_FUNC(ttm_bo_vm_reserve, "", "");
KSYMTAB_FUNC(ttm_bo_vm_fault_reserved, "", "");
KSYMTAB_FUNC(ttm_bo_vm_dummy_page, "", "");
KSYMTAB_FUNC(ttm_bo_vm_fault, "", "");
KSYMTAB_FUNC(ttm_bo_vm_open, "", "");
KSYMTAB_FUNC(ttm_bo_vm_close, "", "");
KSYMTAB_FUNC(ttm_bo_vm_access, "", "");
KSYMTAB_FUNC(ttm_bo_mmap_obj, "", "");
KSYMTAB_FUNC(ttm_eu_backoff_reservation, "", "");
KSYMTAB_FUNC(ttm_eu_reserve_buffers, "", "");
KSYMTAB_FUNC(ttm_eu_fence_buffer_objects, "", "");
KSYMTAB_FUNC(ttm_range_man_init_nocheck, "", "");
KSYMTAB_FUNC(ttm_range_man_fini_nocheck, "", "");
KSYMTAB_FUNC(ttm_lru_bulk_move_init, "", "");
KSYMTAB_FUNC(ttm_lru_bulk_move_tail, "", "");
KSYMTAB_FUNC(ttm_resource_init, "", "");
KSYMTAB_FUNC(ttm_resource_fini, "", "");
KSYMTAB_FUNC(ttm_resource_free, "", "");
KSYMTAB_FUNC(ttm_resource_manager_init, "", "");
KSYMTAB_FUNC(ttm_resource_manager_evict_all, "", "");
KSYMTAB_FUNC(ttm_resource_manager_usage, "", "");
KSYMTAB_FUNC(ttm_resource_manager_debug, "", "");
KSYMTAB_FUNC(ttm_kmap_iter_iomap_init, "", "");
KSYMTAB_FUNC(ttm_resource_manager_create_debugfs, "", "");
KSYMTAB_FUNC(ttm_pool_alloc, "", "");
KSYMTAB_FUNC(ttm_pool_free, "", "");
KSYMTAB_FUNC(ttm_pool_init, "", "");
KSYMTAB_FUNC(ttm_pool_fini, "", "");
KSYMTAB_FUNC(ttm_pool_debugfs, "", "");
KSYMTAB_DATA(ttm_glob, "", "");
KSYMTAB_FUNC(ttm_device_swapout, "", "");
KSYMTAB_FUNC(ttm_device_init, "", "");
KSYMTAB_FUNC(ttm_device_fini, "", "");
KSYMTAB_FUNC(ttm_device_clear_dma_mappings, "", "");

MODULE_INFO(depends, "drm");

