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

KSYMTAB_FUNC(acpi_video_get_levels, "", "");
KSYMTAB_FUNC(acpi_video_get_edid, "", "");
KSYMTAB_FUNC(acpi_video_register, "", "");
KSYMTAB_FUNC(acpi_video_unregister, "", "");
KSYMTAB_FUNC(acpi_video_register_backlight, "", "");
KSYMTAB_FUNC(acpi_video_handles_brightness_key_presses, "", "");
KSYMTAB_FUNC(__acpi_video_get_backlight_type, "", "");

MODULE_INFO(depends, "backlight");

MODULE_ALIAS("acpi*:LNXVIDEO:*");
