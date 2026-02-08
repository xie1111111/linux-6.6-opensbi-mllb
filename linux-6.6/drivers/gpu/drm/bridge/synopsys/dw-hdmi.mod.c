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

KSYMTAB_FUNC(dw_hdmi_set_plugged_cb, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_channel_status, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_sample_width, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_sample_non_pcm, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_sample_rate, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_channel_count, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_channel_allocation, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_audio_enable, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_audio_disable, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_i2c_write, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_set_high_tmds_clock_ratio, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_gen2_pddq, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_gen2_txpwron, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_gen1_reset, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_gen2_reset, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_i2c_set_addr, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_read_hpd, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_update_hpd, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_phy_setup_hpd, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_setup_rx_sense, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_bus_fmt_is_420, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_probe, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_remove, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_bind, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_unbind, "_gpl", "");
KSYMTAB_FUNC(dw_hdmi_resume, "_gpl", "");

MODULE_INFO(depends, "drm,i2c-core,drm_kms_helper,drm_display_helper");

