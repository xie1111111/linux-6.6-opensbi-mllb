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

KSYMTAB_FUNC(musb_get_mode, "_gpl", "");
KSYMTAB_DATA(musb_readb, "_gpl", "");
KSYMTAB_DATA(musb_writeb, "_gpl", "");
KSYMTAB_DATA(musb_clearb, "_gpl", "");
KSYMTAB_DATA(musb_readw, "_gpl", "");
KSYMTAB_DATA(musb_writew, "_gpl", "");
KSYMTAB_DATA(musb_clearw, "_gpl", "");
KSYMTAB_FUNC(musb_readl, "_gpl", "");
KSYMTAB_FUNC(musb_writel, "_gpl", "");
KSYMTAB_DATA(musb_dma_controller_create, "", "");
KSYMTAB_DATA(musb_dma_controller_destroy, "", "");
KSYMTAB_FUNC(musb_set_host, "_gpl", "");
KSYMTAB_FUNC(musb_set_peripheral, "_gpl", "");
KSYMTAB_FUNC(musb_interrupt, "_gpl", "");
KSYMTAB_FUNC(musb_dma_completion, "_gpl", "");
KSYMTAB_FUNC(musb_mailbox, "_gpl", "");
KSYMTAB_FUNC(musb_queue_resume_work, "_gpl", "");
KSYMTAB_FUNC(musb_root_disconnect, "_gpl", "");

MODULE_INFO(depends, "");

