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

KSYMTAB_FUNC(gf128mul_x8_ble, "", "");
KSYMTAB_FUNC(gf128mul_lle, "", "");
KSYMTAB_FUNC(gf128mul_bbe, "", "");
KSYMTAB_FUNC(gf128mul_init_64k_bbe, "", "");
KSYMTAB_FUNC(gf128mul_free_64k, "", "");
KSYMTAB_FUNC(gf128mul_64k_bbe, "", "");
KSYMTAB_FUNC(gf128mul_init_4k_lle, "", "");
KSYMTAB_FUNC(gf128mul_init_4k_bbe, "", "");
KSYMTAB_FUNC(gf128mul_4k_lle, "", "");
KSYMTAB_FUNC(gf128mul_4k_bbe, "", "");

MODULE_INFO(depends, "");

