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

KSYMTAB_FUNC(nf_ct_nat_ext_add, "_gpl", "");
KSYMTAB_FUNC(nf_nat_setup_info, "", "");
KSYMTAB_FUNC(nf_nat_alloc_null_binding, "_gpl", "");
KSYMTAB_FUNC(nf_nat_packet, "_gpl", "");
KSYMTAB_FUNC(nf_nat_inet_fn, "_gpl", "");
KSYMTAB_FUNC(nf_nat_icmp_reply_translation, "_gpl", "");
KSYMTAB_FUNC(nf_nat_ipv4_register_fn, "_gpl", "");
KSYMTAB_FUNC(nf_nat_ipv4_unregister_fn, "_gpl", "");
KSYMTAB_FUNC(nf_nat_icmpv6_reply_translation, "_gpl", "");
KSYMTAB_FUNC(nf_nat_ipv6_register_fn, "_gpl", "");
KSYMTAB_FUNC(nf_nat_ipv6_unregister_fn, "_gpl", "");
KSYMTAB_FUNC(__nf_nat_mangle_tcp_packet, "", "");
KSYMTAB_FUNC(nf_nat_mangle_udp_packet, "", "");
KSYMTAB_FUNC(nf_nat_follow_master, "", "");
KSYMTAB_FUNC(nf_nat_exp_find_port, "_gpl", "");
KSYMTAB_FUNC(nf_nat_redirect_ipv4, "_gpl", "");
KSYMTAB_FUNC(nf_nat_redirect_ipv6, "_gpl", "");
KSYMTAB_FUNC(nf_nat_masquerade_ipv4, "_gpl", "");
KSYMTAB_FUNC(nf_nat_masquerade_ipv6, "_gpl", "");
KSYMTAB_FUNC(nf_nat_masquerade_inet_register_notifiers, "_gpl", "");
KSYMTAB_FUNC(nf_nat_masquerade_inet_unregister_notifiers, "_gpl", "");

MODULE_INFO(depends, "nf_conntrack,libcrc32c");

