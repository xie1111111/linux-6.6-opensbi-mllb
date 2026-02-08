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

KSYMTAB_FUNC(backlight_device_set_brightness, "", "");
KSYMTAB_FUNC(backlight_force_update, "", "");
KSYMTAB_FUNC(backlight_device_register, "", "");
KSYMTAB_FUNC(backlight_device_get_by_type, "", "");
KSYMTAB_FUNC(backlight_device_get_by_name, "", "");
KSYMTAB_FUNC(backlight_device_unregister, "", "");
KSYMTAB_FUNC(backlight_register_notifier, "", "");
KSYMTAB_FUNC(backlight_unregister_notifier, "", "");
KSYMTAB_FUNC(devm_backlight_device_register, "", "");
KSYMTAB_FUNC(devm_backlight_device_unregister, "", "");
KSYMTAB_FUNC(of_find_backlight_by_node, "", "");
KSYMTAB_FUNC(devm_of_find_backlight, "", "");

MODULE_INFO(depends, "");

