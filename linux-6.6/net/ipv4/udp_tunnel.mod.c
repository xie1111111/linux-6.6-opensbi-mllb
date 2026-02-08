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

KSYMTAB_FUNC(udp_sock_create4, "", "");
KSYMTAB_FUNC(setup_udp_tunnel_sock, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_push_rx_port, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_drop_rx_port, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_notify_add_rx_port, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_notify_del_rx_port, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_xmit_skb, "_gpl", "");
KSYMTAB_FUNC(udp_tunnel_sock_release, "_gpl", "");
KSYMTAB_FUNC(udp_tun_rx_dst, "_gpl", "");

MODULE_INFO(depends, "");

