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

KSYMTAB_FUNC(xfrm_aalg_get_byid, "_gpl", "");
KSYMTAB_FUNC(xfrm_ealg_get_byid, "_gpl", "");
KSYMTAB_FUNC(xfrm_calg_get_byid, "_gpl", "");
KSYMTAB_FUNC(xfrm_aalg_get_byname, "_gpl", "");
KSYMTAB_FUNC(xfrm_ealg_get_byname, "_gpl", "");
KSYMTAB_FUNC(xfrm_calg_get_byname, "_gpl", "");
KSYMTAB_FUNC(xfrm_aead_get_byname, "_gpl", "");
KSYMTAB_FUNC(xfrm_aalg_get_byidx, "_gpl", "");
KSYMTAB_FUNC(xfrm_ealg_get_byidx, "_gpl", "");
KSYMTAB_FUNC(xfrm_probe_algs, "_gpl", "");
KSYMTAB_FUNC(xfrm_count_pfkey_auth_supported, "_gpl", "");
KSYMTAB_FUNC(xfrm_count_pfkey_enc_supported, "_gpl", "");

MODULE_INFO(depends, "");

