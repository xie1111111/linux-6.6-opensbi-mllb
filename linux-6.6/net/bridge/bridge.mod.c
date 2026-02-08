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

KSYMTAB_DATA(nf_br_ops, "_gpl", "");
KSYMTAB_FUNC(br_fdb_find_port, "_gpl", "");
KSYMTAB_FUNC(br_fdb_clear_offload, "_gpl", "");
KSYMTAB_FUNC(br_dev_queue_push_xmit, "_gpl", "");
KSYMTAB_FUNC(br_forward_finish, "_gpl", "");
KSYMTAB_FUNC(br_forward, "_gpl", "");
KSYMTAB_FUNC(br_port_flag_is_set, "_gpl", "");
KSYMTAB_FUNC(br_handle_frame_finish, "_gpl", "");
KSYMTAB_FUNC(br_port_get_stp_state, "_gpl", "");
KSYMTAB_FUNC(br_get_ageing_time, "_gpl", "");
KSYMTAB_FUNC(br_multicast_enabled, "_gpl", "");
KSYMTAB_FUNC(br_multicast_router, "_gpl", "");
KSYMTAB_FUNC(br_multicast_list_adjacent, "_gpl", "");
KSYMTAB_FUNC(br_multicast_has_querier_anywhere, "_gpl", "");
KSYMTAB_FUNC(br_multicast_has_querier_adjacent, "_gpl", "");
KSYMTAB_FUNC(br_multicast_has_router_adjacent, "_gpl", "");
KSYMTAB_FUNC(br_vlan_enabled, "_gpl", "");
KSYMTAB_FUNC(br_vlan_get_proto, "_gpl", "");
KSYMTAB_FUNC(br_vlan_get_pvid, "_gpl", "");
KSYMTAB_FUNC(br_vlan_get_pvid_rcu, "_gpl", "");
KSYMTAB_FUNC(br_vlan_get_info, "_gpl", "");
KSYMTAB_FUNC(br_vlan_get_info_rcu, "_gpl", "");
KSYMTAB_FUNC(br_mst_enabled, "_gpl", "");
KSYMTAB_FUNC(br_mst_get_info, "_gpl", "");
KSYMTAB_FUNC(br_mst_get_state, "_gpl", "");

MODULE_INFO(depends, "llc,stp");


MODULE_INFO(srcversion, "1BE7710A027D057F629C497");
