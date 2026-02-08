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

KSYMTAB_FUNC(drm_dp_dual_mode_read, "", "");
KSYMTAB_FUNC(drm_dp_dual_mode_write, "", "");
KSYMTAB_FUNC(drm_dp_dual_mode_detect, "", "");
KSYMTAB_FUNC(drm_dp_dual_mode_max_tmds_clock, "", "");
KSYMTAB_FUNC(drm_dp_dual_mode_get_tmds_output, "", "");
KSYMTAB_FUNC(drm_dp_dual_mode_set_tmds_output, "", "");
KSYMTAB_FUNC(drm_dp_get_dual_mode_type_name, "", "");
KSYMTAB_FUNC(drm_lspcon_get_mode, "", "");
KSYMTAB_FUNC(drm_lspcon_set_mode, "", "");
KSYMTAB_FUNC(drm_dp_channel_eq_ok, "", "");
KSYMTAB_FUNC(drm_dp_clock_recovery_ok, "", "");
KSYMTAB_FUNC(drm_dp_get_adjust_request_voltage, "", "");
KSYMTAB_FUNC(drm_dp_get_adjust_request_pre_emphasis, "", "");
KSYMTAB_FUNC(drm_dp_get_adjust_tx_ffe_preset, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_lane_channel_eq_done, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_lane_symbol_locked, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_eq_interlane_align_done, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_cds_interlane_align_done, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_link_training_failed, "", "");
KSYMTAB_FUNC(drm_dp_read_clock_recovery_delay, "", "");
KSYMTAB_FUNC(drm_dp_read_channel_eq_delay, "", "");
KSYMTAB_FUNC(drm_dp_128b132b_read_aux_rd_interval, "", "");
KSYMTAB_FUNC(drm_dp_link_train_clock_recovery_delay, "", "");
KSYMTAB_FUNC(drm_dp_link_train_channel_eq_delay, "", "");
KSYMTAB_FUNC(drm_dp_phy_name, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_link_train_clock_recovery_delay, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_link_train_channel_eq_delay, "", "");
KSYMTAB_FUNC(drm_dp_link_rate_to_bw_code, "", "");
KSYMTAB_FUNC(drm_dp_bw_code_to_link_rate, "", "");
KSYMTAB_FUNC(drm_dp_dpcd_probe, "", "");
KSYMTAB_FUNC(drm_dp_dpcd_read, "", "");
KSYMTAB_FUNC(drm_dp_dpcd_write, "", "");
KSYMTAB_FUNC(drm_dp_dpcd_read_link_status, "", "");
KSYMTAB_FUNC(drm_dp_dpcd_read_phy_link_status, "", "");
KSYMTAB_FUNC(drm_dp_downstream_is_type, "", "");
KSYMTAB_FUNC(drm_dp_downstream_is_tmds, "", "");
KSYMTAB_FUNC(drm_dp_send_real_edid_checksum, "", "");
KSYMTAB_FUNC(drm_dp_read_dpcd_caps, "", "");
KSYMTAB_FUNC(drm_dp_read_downstream_info, "", "");
KSYMTAB_FUNC(drm_dp_downstream_max_dotclock, "", "");
KSYMTAB_FUNC(drm_dp_downstream_max_tmds_clock, "", "");
KSYMTAB_FUNC(drm_dp_downstream_min_tmds_clock, "", "");
KSYMTAB_FUNC(drm_dp_downstream_max_bpc, "", "");
KSYMTAB_FUNC(drm_dp_downstream_420_passthrough, "", "");
KSYMTAB_FUNC(drm_dp_downstream_444_to_420_conversion, "", "");
KSYMTAB_FUNC(drm_dp_downstream_rgb_to_ycbcr_conversion, "", "");
KSYMTAB_FUNC(drm_dp_downstream_mode, "", "");
KSYMTAB_FUNC(drm_dp_downstream_id, "", "");
KSYMTAB_FUNC(drm_dp_downstream_debug, "", "");
KSYMTAB_FUNC(drm_dp_subconnector_type, "", "");
KSYMTAB_FUNC(drm_dp_set_subconnector_property, "", "");
KSYMTAB_FUNC(drm_dp_read_sink_count_cap, "", "");
KSYMTAB_FUNC(drm_dp_read_sink_count, "", "");
KSYMTAB_FUNC(drm_dp_remote_aux_init, "", "");
KSYMTAB_FUNC(drm_dp_aux_init, "", "");
KSYMTAB_FUNC(drm_dp_aux_register, "", "");
KSYMTAB_FUNC(drm_dp_aux_unregister, "", "");
KSYMTAB_FUNC(drm_dp_psr_setup_time, "", "");
KSYMTAB_FUNC(drm_dp_start_crc, "", "");
KSYMTAB_FUNC(drm_dp_stop_crc, "", "");
KSYMTAB_FUNC(drm_dp_read_desc, "", "");
KSYMTAB_FUNC(drm_dp_dsc_sink_max_slice_count, "", "");
KSYMTAB_FUNC(drm_dp_dsc_sink_line_buf_depth, "", "");
KSYMTAB_FUNC(drm_dp_dsc_sink_supported_input_bpcs, "", "");
KSYMTAB_FUNC(drm_dp_read_lttpr_common_caps, "", "");
KSYMTAB_FUNC(drm_dp_read_lttpr_phy_caps, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_count, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_max_link_rate, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_max_lane_count, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_voltage_swing_level_3_supported, "", "");
KSYMTAB_FUNC(drm_dp_lttpr_pre_emphasis_level_3_supported, "", "");
KSYMTAB_FUNC(drm_dp_get_phy_test_pattern, "", "");
KSYMTAB_FUNC(drm_dp_set_phy_test_pattern, "", "");
KSYMTAB_FUNC(drm_dp_vsc_sdp_log, "", "");
KSYMTAB_FUNC(drm_dp_get_pcon_max_frl_bw, "", "");
KSYMTAB_FUNC(drm_dp_pcon_frl_prepare, "", "");
KSYMTAB_FUNC(drm_dp_pcon_is_frl_ready, "", "");
KSYMTAB_FUNC(drm_dp_pcon_frl_configure_1, "", "");
KSYMTAB_FUNC(drm_dp_pcon_frl_configure_2, "", "");
KSYMTAB_FUNC(drm_dp_pcon_reset_frl_config, "", "");
KSYMTAB_FUNC(drm_dp_pcon_frl_enable, "", "");
KSYMTAB_FUNC(drm_dp_pcon_hdmi_link_active, "", "");
KSYMTAB_FUNC(drm_dp_pcon_hdmi_link_mode, "", "");
KSYMTAB_FUNC(drm_dp_pcon_hdmi_frl_link_error_count, "", "");
KSYMTAB_FUNC(drm_dp_pcon_enc_is_dsc_1_2, "", "");
KSYMTAB_FUNC(drm_dp_pcon_dsc_max_slices, "", "");
KSYMTAB_FUNC(drm_dp_pcon_dsc_max_slice_width, "", "");
KSYMTAB_FUNC(drm_dp_pcon_dsc_bpp_incr, "", "");
KSYMTAB_FUNC(drm_dp_pcon_pps_default, "", "");
KSYMTAB_FUNC(drm_dp_pcon_pps_override_buf, "", "");
KSYMTAB_FUNC(drm_dp_pcon_pps_override_param, "", "");
KSYMTAB_FUNC(drm_dp_pcon_convert_rgb_to_ycbcr, "", "");
KSYMTAB_FUNC(drm_edp_backlight_set_level, "", "");
KSYMTAB_FUNC(drm_edp_backlight_enable, "", "");
KSYMTAB_FUNC(drm_edp_backlight_disable, "", "");
KSYMTAB_FUNC(drm_edp_backlight_init, "", "");
KSYMTAB_FUNC(drm_panel_dp_aux_backlight, "", "");
KSYMTAB_FUNC(drm_dp_mst_get_port_malloc, "", "");
KSYMTAB_FUNC(drm_dp_mst_put_port_malloc, "", "");
KSYMTAB_FUNC(drm_atomic_get_mst_payload_state, "", "");
KSYMTAB_FUNC(drm_dp_mst_connector_late_register, "", "");
KSYMTAB_FUNC(drm_dp_mst_connector_early_unregister, "", "");
KSYMTAB_FUNC(drm_dp_send_power_updown_phy, "", "");
KSYMTAB_FUNC(drm_dp_send_query_stream_enc_status, "", "");
KSYMTAB_FUNC(drm_dp_add_payload_part1, "", "");
KSYMTAB_FUNC(drm_dp_remove_payload, "", "");
KSYMTAB_FUNC(drm_dp_add_payload_part2, "", "");
KSYMTAB_FUNC(drm_dp_get_vc_payload_bw, "", "");
KSYMTAB_FUNC(drm_dp_read_mst_cap, "", "");
KSYMTAB_FUNC(drm_dp_mst_topology_mgr_set_mst, "", "");
KSYMTAB_FUNC(drm_dp_mst_topology_mgr_suspend, "", "");
KSYMTAB_FUNC(drm_dp_mst_topology_mgr_resume, "", "");
KSYMTAB_FUNC(drm_dp_mst_hpd_irq_handle_event, "", "");
KSYMTAB_FUNC(drm_dp_mst_hpd_irq_send_new_request, "", "");
KSYMTAB_FUNC(drm_dp_mst_detect_port, "", "");
KSYMTAB_FUNC(drm_dp_mst_edid_read, "", "");
KSYMTAB_FUNC(drm_dp_mst_get_edid, "", "");
KSYMTAB_FUNC(drm_dp_atomic_find_time_slots, "", "");
KSYMTAB_FUNC(drm_dp_atomic_release_time_slots, "", "");
KSYMTAB_FUNC(drm_dp_mst_atomic_setup_commit, "", "");
KSYMTAB_FUNC(drm_dp_mst_atomic_wait_for_dependencies, "", "");
KSYMTAB_FUNC(drm_dp_mst_root_conn_atomic_check, "", "");
KSYMTAB_FUNC(drm_dp_mst_update_slots, "", "");
KSYMTAB_FUNC(drm_dp_check_act_status, "", "");
KSYMTAB_FUNC(drm_dp_calc_pbn_mode, "", "");
KSYMTAB_FUNC(drm_dp_mst_dump_topology, "", "");
KSYMTAB_FUNC(drm_dp_mst_add_affected_dsc_crtcs, "", "");
KSYMTAB_FUNC(drm_dp_mst_atomic_enable_dsc, "", "");
KSYMTAB_FUNC(drm_dp_mst_atomic_check, "", "");
KSYMTAB_DATA(drm_dp_mst_topology_state_funcs, "", "");
KSYMTAB_FUNC(drm_atomic_get_mst_topology_state, "", "");
KSYMTAB_FUNC(drm_atomic_get_old_mst_topology_state, "", "");
KSYMTAB_FUNC(drm_atomic_get_new_mst_topology_state, "", "");
KSYMTAB_FUNC(drm_dp_mst_topology_mgr_init, "", "");
KSYMTAB_FUNC(drm_dp_mst_topology_mgr_destroy, "", "");
KSYMTAB_FUNC(drm_dp_mst_dsc_aux_for_port, "", "");
KSYMTAB_FUNC(drm_dsc_dp_pps_header_init, "", "");
KSYMTAB_FUNC(drm_dsc_dp_rc_buffer_size, "", "");
KSYMTAB_FUNC(drm_dsc_pps_payload_pack, "", "");
KSYMTAB_FUNC(drm_dsc_set_const_params, "", "");
KSYMTAB_FUNC(drm_dsc_set_rc_buf_thresh, "", "");
KSYMTAB_FUNC(drm_dsc_setup_rc_params, "", "");
KSYMTAB_FUNC(drm_dsc_compute_rc_parameters, "", "");
KSYMTAB_FUNC(drm_dsc_get_bpp_int, "", "");
KSYMTAB_FUNC(drm_dsc_initial_scale_value, "", "");
KSYMTAB_FUNC(drm_dsc_flatness_det_thresh, "", "");
KSYMTAB_FUNC(drm_hdmi_infoframe_set_hdr_metadata, "", "");
KSYMTAB_FUNC(drm_hdmi_avi_infoframe_colorimetry, "", "");
KSYMTAB_FUNC(drm_hdmi_avi_infoframe_bars, "", "");
KSYMTAB_FUNC(drm_hdmi_avi_infoframe_content_type, "", "");
KSYMTAB_FUNC(drm_scdc_read, "", "");
KSYMTAB_FUNC(drm_scdc_write, "", "");
KSYMTAB_FUNC(drm_scdc_get_scrambling_status, "", "");
KSYMTAB_FUNC(drm_scdc_set_scrambling, "", "");
KSYMTAB_FUNC(drm_scdc_set_high_tmds_clock_ratio, "", "");

MODULE_INFO(depends, "drm,drm_kms_helper,i2c-core,backlight");

