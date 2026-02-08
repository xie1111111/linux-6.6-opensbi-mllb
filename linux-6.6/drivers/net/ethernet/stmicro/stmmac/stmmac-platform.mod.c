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

KSYMTAB_FUNC(stmmac_probe_config_dt, "_gpl", "");
KSYMTAB_FUNC(devm_stmmac_probe_config_dt, "_gpl", "");
KSYMTAB_FUNC(stmmac_remove_config_dt, "_gpl", "");
KSYMTAB_FUNC(stmmac_get_platform_resources, "_gpl", "");
KSYMTAB_FUNC(stmmac_pltfr_init, "_gpl", "");
KSYMTAB_FUNC(stmmac_pltfr_exit, "_gpl", "");
KSYMTAB_FUNC(stmmac_pltfr_probe, "_gpl", "");
KSYMTAB_FUNC(devm_stmmac_pltfr_probe, "_gpl", "");
KSYMTAB_FUNC(stmmac_pltfr_remove_no_dt, "_gpl", "");
KSYMTAB_FUNC(stmmac_pltfr_remove, "_gpl", "");
KSYMTAB_DATA(stmmac_pltfr_pm_ops, "_gpl", "");

MODULE_INFO(depends, "stmmac");

