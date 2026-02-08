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

KSYMTAB_FUNC(ip_vs_conn_in_get_proto, "_gpl", "");
KSYMTAB_FUNC(ip_vs_conn_out_get_proto, "_gpl", "");
KSYMTAB_FUNC(register_ip_vs_scheduler, "", "");
KSYMTAB_FUNC(unregister_ip_vs_scheduler, "", "");
KSYMTAB_FUNC(ip_vs_proto_name, "", "");
KSYMTAB_FUNC(ip_vs_conn_new, "", "");
KSYMTAB_FUNC(ip_vs_conn_in_get, "", "");
KSYMTAB_FUNC(ip_vs_conn_out_get, "", "");
KSYMTAB_FUNC(ip_vs_tcp_conn_listen, "", "");
KSYMTAB_FUNC(ip_vs_conn_put, "", "");
KSYMTAB_FUNC(ip_vs_new_conn_out, "", "");
KSYMTAB_FUNC(ip_vs_scheduler_err, "", "");
KSYMTAB_FUNC(register_ip_vs_app, "", "");
KSYMTAB_FUNC(unregister_ip_vs_app, "", "");
KSYMTAB_FUNC(register_ip_vs_app_inc, "", "");
KSYMTAB_FUNC(ip_vs_proto_get, "", "");
KSYMTAB_FUNC(ip_vs_proto_data_get, "", "");
KSYMTAB_FUNC(register_ip_vs_pe, "_gpl", "");
KSYMTAB_FUNC(unregister_ip_vs_pe, "_gpl", "");
KSYMTAB_FUNC(ip_vs_nfct_expect_related, "", "");

MODULE_INFO(depends, "nf_conntrack");

