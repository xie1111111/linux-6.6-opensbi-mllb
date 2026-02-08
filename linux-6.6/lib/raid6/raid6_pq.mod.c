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

KSYMTAB_DATA(raid6_empty_zero_page, "", "");
KSYMTAB_DATA(raid6_call, "_gpl", "");
KSYMTAB_DATA(raid6_2data_recov, "_gpl", "");
KSYMTAB_DATA(raid6_datap_recov, "_gpl", "");
KSYMTAB_DATA(raid6_gfmul, "", "");
KSYMTAB_DATA(raid6_vgfmul, "", "");
KSYMTAB_DATA(raid6_gfexp, "", "");
KSYMTAB_DATA(raid6_gflog, "", "");
KSYMTAB_DATA(raid6_gfinv, "", "");
KSYMTAB_DATA(raid6_gfexi, "", "");

MODULE_INFO(depends, "");

