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

KSYMTAB_DATA(halt_poll_ns, "_gpl", "");
KSYMTAB_DATA(halt_poll_ns_grow, "_gpl", "");
KSYMTAB_DATA(halt_poll_ns_grow_start, "_gpl", "");
KSYMTAB_DATA(halt_poll_ns_shrink, "_gpl", "");
KSYMTAB_DATA(kvm_debugfs_dir, "_gpl", "");
KSYMTAB_FUNC(vcpu_load, "_gpl", "");
KSYMTAB_FUNC(vcpu_put, "_gpl", "");
KSYMTAB_FUNC(kvm_make_all_cpus_request, "_gpl", "");
KSYMTAB_FUNC(kvm_flush_remote_tlbs, "_gpl", "");
KSYMTAB_FUNC(kvm_destroy_vcpus, "_gpl", "");
KSYMTAB_FUNC(kvm_get_kvm, "_gpl", "");
KSYMTAB_FUNC(kvm_get_kvm_safe, "_gpl", "");
KSYMTAB_FUNC(kvm_put_kvm, "_gpl", "");
KSYMTAB_FUNC(kvm_put_kvm_no_destroy, "_gpl", "");
KSYMTAB_FUNC(__kvm_set_memory_region, "_gpl", "");
KSYMTAB_FUNC(kvm_set_memory_region, "_gpl", "");
KSYMTAB_FUNC(gfn_to_memslot, "_gpl", "");
KSYMTAB_FUNC(kvm_is_visible_gfn, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_is_visible_gfn, "_gpl", "");
KSYMTAB_FUNC(gfn_to_hva_memslot, "_gpl", "");
KSYMTAB_FUNC(gfn_to_hva, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_gfn_to_hva, "_gpl", "");
KSYMTAB_FUNC(__gfn_to_pfn_memslot, "_gpl", "");
KSYMTAB_FUNC(gfn_to_pfn_prot, "_gpl", "");
KSYMTAB_FUNC(gfn_to_pfn_memslot, "_gpl", "");
KSYMTAB_FUNC(gfn_to_pfn_memslot_atomic, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_gfn_to_pfn_atomic, "_gpl", "");
KSYMTAB_FUNC(gfn_to_pfn, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_gfn_to_pfn, "_gpl", "");
KSYMTAB_FUNC(gfn_to_page_many_atomic, "_gpl", "");
KSYMTAB_FUNC(gfn_to_page, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_map, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_unmap, "_gpl", "");
KSYMTAB_FUNC(kvm_release_page_clean, "_gpl", "");
KSYMTAB_FUNC(kvm_release_pfn_clean, "_gpl", "");
KSYMTAB_FUNC(kvm_release_page_dirty, "_gpl", "");
KSYMTAB_FUNC(kvm_release_pfn_dirty, "_gpl", "");
KSYMTAB_FUNC(kvm_set_pfn_dirty, "_gpl", "");
KSYMTAB_FUNC(kvm_set_pfn_accessed, "_gpl", "");
KSYMTAB_FUNC(kvm_read_guest_page, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_read_guest_page, "_gpl", "");
KSYMTAB_FUNC(kvm_read_guest, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_read_guest, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_read_guest_atomic, "_gpl", "");
KSYMTAB_FUNC(kvm_write_guest_page, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_write_guest_page, "_gpl", "");
KSYMTAB_FUNC(kvm_write_guest, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_write_guest, "_gpl", "");
KSYMTAB_FUNC(kvm_gfn_to_hva_cache_init, "_gpl", "");
KSYMTAB_FUNC(kvm_write_guest_offset_cached, "_gpl", "");
KSYMTAB_FUNC(kvm_write_guest_cached, "_gpl", "");
KSYMTAB_FUNC(kvm_read_guest_offset_cached, "_gpl", "");
KSYMTAB_FUNC(kvm_read_guest_cached, "_gpl", "");
KSYMTAB_FUNC(kvm_clear_guest, "_gpl", "");
KSYMTAB_FUNC(mark_page_dirty_in_slot, "_gpl", "");
KSYMTAB_FUNC(mark_page_dirty, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_mark_page_dirty, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_halt, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_wake_up, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_kick, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_yield_to, "_gpl", "");
KSYMTAB_FUNC(kvm_vcpu_on_spin, "_gpl", "");
KSYMTAB_FUNC(kvm_are_all_memslots_empty, "_gpl", "");
KSYMTAB_FUNC(file_is_kvm, "_gpl", "");
KSYMTAB_DATA(kvm_rebooting, "_gpl", "");
KSYMTAB_FUNC(kvm_io_bus_write, "_gpl", "");
KSYMTAB_FUNC(kvm_io_bus_get_dev, "_gpl", "");
KSYMTAB_FUNC(kvm_get_running_vcpu, "_gpl", "");
KSYMTAB_FUNC(kvm_init, "_gpl", "");
KSYMTAB_FUNC(kvm_exit, "_gpl", "");
KSYMTAB_FUNC(kvm_irq_has_notifier, "_gpl", "");

MODULE_INFO(depends, "");

