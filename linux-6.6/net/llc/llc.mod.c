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

KSYMTAB_DATA(llc_sap_list, "", "");
KSYMTAB_FUNC(llc_sap_find, "", "");
KSYMTAB_FUNC(llc_sap_open, "", "");
KSYMTAB_FUNC(llc_sap_close, "", "");
KSYMTAB_FUNC(llc_add_pack, "", "");
KSYMTAB_FUNC(llc_remove_pack, "", "");
KSYMTAB_FUNC(llc_set_station_handler, "", "");
KSYMTAB_FUNC(llc_mac_hdr_init, "", "");
KSYMTAB_FUNC(llc_build_and_send_ui_pkt, "", "");

MODULE_INFO(depends, "");

