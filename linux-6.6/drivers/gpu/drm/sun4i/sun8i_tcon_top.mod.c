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

KSYMTAB_FUNC(sun8i_tcon_top_set_hdmi_src, "", "");
KSYMTAB_FUNC(sun8i_tcon_top_de_config, "", "");
KSYMTAB_DATA(sun8i_tcon_top_of_table, "", "");

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-tcon-top");
MODULE_ALIAS("of:N*T*Callwinner,sun8i-r40-tcon-topC*");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-tcon-top");
MODULE_ALIAS("of:N*T*Callwinner,sun20i-d1-tcon-topC*");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-tcon-top");
MODULE_ALIAS("of:N*T*Callwinner,sun50i-h6-tcon-topC*");
