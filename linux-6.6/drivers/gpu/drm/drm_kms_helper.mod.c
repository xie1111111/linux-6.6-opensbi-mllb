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

KSYMTAB_FUNC(drm_atomic_helper_check_modeset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check_wb_encoder_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check_plane_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check_crtc_primary_plane, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check_planes, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check, "", "");
KSYMTAB_FUNC(drm_atomic_helper_update_legacy_modeset_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_calc_timestamping_constants, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_modeset_disables, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_modeset_enables, "", "");
KSYMTAB_FUNC(drm_atomic_helper_wait_for_fences, "", "");
KSYMTAB_FUNC(drm_atomic_helper_wait_for_vblanks, "", "");
KSYMTAB_FUNC(drm_atomic_helper_wait_for_flip_done, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_tail, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_tail_rpm, "", "");
KSYMTAB_FUNC(drm_atomic_helper_async_check, "", "");
KSYMTAB_FUNC(drm_atomic_helper_async_commit, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit, "", "");
KSYMTAB_FUNC(drm_atomic_helper_setup_commit, "", "");
KSYMTAB_FUNC(drm_atomic_helper_wait_for_dependencies, "", "");
KSYMTAB_FUNC(drm_atomic_helper_fake_vblank, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_hw_done, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_cleanup_done, "", "");
KSYMTAB_FUNC(drm_atomic_helper_prepare_planes, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_planes, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_planes_on_crtc, "", "");
KSYMTAB_FUNC(drm_atomic_helper_disable_planes_on_crtc, "", "");
KSYMTAB_FUNC(drm_atomic_helper_cleanup_planes, "", "");
KSYMTAB_FUNC(drm_atomic_helper_swap_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_update_plane, "", "");
KSYMTAB_FUNC(drm_atomic_helper_disable_plane, "", "");
KSYMTAB_FUNC(drm_atomic_helper_set_config, "", "");
KSYMTAB_FUNC(drm_atomic_helper_disable_all, "", "");
KSYMTAB_FUNC(drm_atomic_helper_shutdown, "", "");
KSYMTAB_FUNC(drm_atomic_helper_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_suspend, "", "");
KSYMTAB_FUNC(drm_atomic_helper_commit_duplicated_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_resume, "", "");
KSYMTAB_FUNC(drm_atomic_helper_page_flip, "", "");
KSYMTAB_FUNC(drm_atomic_helper_page_flip_target, "", "");
KSYMTAB_FUNC(drm_atomic_helper_bridge_propagate_bus_fmt, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_crtc_state_reset, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_crtc_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_crtc_reset, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_crtc_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_crtc_duplicate_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_crtc_destroy_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_crtc_destroy_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_plane_state_reset, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_plane_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_plane_reset, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_plane_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_plane_duplicate_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_plane_destroy_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_plane_destroy_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_connector_state_reset, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_connector_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_tv_margins_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_tv_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_tv_check, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_connector_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_duplicate_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_connector_destroy_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_connector_destroy_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_private_obj_duplicate_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_bridge_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_bridge_duplicate_state, "", "");
KSYMTAB_FUNC(drm_atomic_helper_bridge_destroy_state, "", "");
KSYMTAB_FUNC(__drm_atomic_helper_bridge_reset, "", "");
KSYMTAB_FUNC(drm_atomic_helper_bridge_reset, "", "");
KSYMTAB_FUNC(drm_bridge_connector_init, "_gpl", "");
KSYMTAB_FUNC(drm_helper_encoder_in_use, "", "");
KSYMTAB_FUNC(drm_helper_crtc_in_use, "", "");
KSYMTAB_FUNC(drm_helper_disable_unused_functions, "", "");
KSYMTAB_FUNC(drm_crtc_helper_set_mode, "", "");
KSYMTAB_FUNC(drm_crtc_helper_atomic_check, "", "");
KSYMTAB_FUNC(drm_crtc_helper_set_config, "", "");
KSYMTAB_FUNC(drm_helper_connector_dpms, "", "");
KSYMTAB_FUNC(drm_helper_resume_force_mode, "", "");
KSYMTAB_FUNC(drm_helper_force_disable_all, "", "");
KSYMTAB_FUNC(drm_atomic_helper_check_plane_damage, "", "");
KSYMTAB_FUNC(drm_atomic_helper_dirtyfb, "", "");
KSYMTAB_FUNC(drm_atomic_helper_damage_iter_init, "", "");
KSYMTAB_FUNC(drm_atomic_helper_damage_iter_next, "", "");
KSYMTAB_FUNC(drm_atomic_helper_damage_merged, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_init, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_destroy, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_dpms, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_mode_fixup, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_prepare, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_commit, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_mode_set, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_detect, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_save, "", "");
KSYMTAB_FUNC(drm_i2c_encoder_restore, "", "");
KSYMTAB_FUNC(drm_flip_work_allocate_task, "", "");
KSYMTAB_FUNC(drm_flip_work_queue_task, "", "");
KSYMTAB_FUNC(drm_flip_work_queue, "", "");
KSYMTAB_FUNC(drm_flip_work_commit, "", "");
KSYMTAB_FUNC(drm_flip_work_init, "", "");
KSYMTAB_FUNC(drm_flip_work_cleanup, "", "");
KSYMTAB_FUNC(drm_fb_clip_offset, "", "");
KSYMTAB_FUNC(drm_fb_memcpy, "", "");
KSYMTAB_FUNC(drm_fb_swab, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_rgb332, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_rgb565, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_xrgb1555, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_argb1555, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_rgba5551, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_rgb888, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_argb8888, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_xrgb2101010, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_argb2101010, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_gray8, "", "");
KSYMTAB_FUNC(drm_fb_blit, "", "");
KSYMTAB_FUNC(drm_fb_xrgb8888_to_mono, "", "");
KSYMTAB_FUNC(drm_fb_build_fourcc_list, "", "");
KSYMTAB_FUNC(drm_gem_plane_helper_prepare_fb, "_gpl", "");
KSYMTAB_FUNC(__drm_gem_duplicate_shadow_plane_state, "", "");
KSYMTAB_FUNC(drm_gem_duplicate_shadow_plane_state, "", "");
KSYMTAB_FUNC(__drm_gem_destroy_shadow_plane_state, "", "");
KSYMTAB_FUNC(drm_gem_destroy_shadow_plane_state, "", "");
KSYMTAB_FUNC(__drm_gem_reset_shadow_plane, "", "");
KSYMTAB_FUNC(drm_gem_reset_shadow_plane, "", "");
KSYMTAB_FUNC(drm_gem_begin_shadow_fb_access, "", "");
KSYMTAB_FUNC(drm_gem_end_shadow_fb_access, "", "");
KSYMTAB_FUNC(drm_gem_simple_kms_begin_shadow_fb_access, "", "");
KSYMTAB_FUNC(drm_gem_simple_kms_end_shadow_fb_access, "", "");
KSYMTAB_FUNC(drm_gem_simple_kms_reset_shadow_plane, "", "");
KSYMTAB_FUNC(drm_gem_simple_kms_duplicate_shadow_plane_state, "", "");
KSYMTAB_FUNC(drm_gem_simple_kms_destroy_shadow_plane_state, "", "");
KSYMTAB_FUNC(drm_gem_fb_get_obj, "_gpl", "");
KSYMTAB_FUNC(drm_gem_fb_destroy, "", "");
KSYMTAB_FUNC(drm_gem_fb_create_handle, "", "");
KSYMTAB_FUNC(drm_gem_fb_init_with_funcs, "_gpl", "");
KSYMTAB_FUNC(drm_gem_fb_create_with_funcs, "_gpl", "");
KSYMTAB_FUNC(drm_gem_fb_create, "_gpl", "");
KSYMTAB_FUNC(drm_gem_fb_create_with_dirty, "_gpl", "");
KSYMTAB_FUNC(drm_gem_fb_vmap, "", "");
KSYMTAB_FUNC(drm_gem_fb_vunmap, "", "");
KSYMTAB_FUNC(drm_gem_fb_begin_cpu_access, "", "");
KSYMTAB_FUNC(drm_gem_fb_end_cpu_access, "", "");
KSYMTAB_FUNC(drm_gem_fb_afbc_init, "_gpl", "");
KSYMTAB_FUNC(drm_helper_move_panel_connectors_to_head, "", "");
KSYMTAB_FUNC(drm_helper_mode_fill_fb_struct, "", "");
KSYMTAB_FUNC(drm_crtc_init, "", "");
KSYMTAB_FUNC(drm_mode_config_helper_suspend, "", "");
KSYMTAB_FUNC(drm_mode_config_helper_resume, "", "");
KSYMTAB_FUNC(drm_plane_helper_update_primary, "", "");
KSYMTAB_FUNC(drm_plane_helper_disable_primary, "", "");
KSYMTAB_FUNC(drm_plane_helper_destroy, "", "");
KSYMTAB_FUNC(drm_plane_helper_atomic_check, "", "");
KSYMTAB_FUNC(drm_kms_helper_poll_enable, "", "");
KSYMTAB_FUNC(drm_kms_helper_poll_reschedule, "", "");
KSYMTAB_FUNC(drm_helper_probe_detect, "", "");
KSYMTAB_FUNC(drm_helper_probe_single_connector_modes, "", "");
KSYMTAB_FUNC(drm_kms_helper_hotplug_event, "", "");
KSYMTAB_FUNC(drm_kms_helper_connector_hotplug_event, "", "");
KSYMTAB_FUNC(drm_kms_helper_is_poll_worker, "", "");
KSYMTAB_FUNC(drm_kms_helper_poll_disable, "", "");
KSYMTAB_FUNC(drm_kms_helper_poll_init, "", "");
KSYMTAB_FUNC(drm_kms_helper_poll_fini, "", "");
KSYMTAB_FUNC(drm_connector_helper_hpd_irq_event, "", "");
KSYMTAB_FUNC(drm_helper_hpd_irq_event, "", "");
KSYMTAB_FUNC(drm_crtc_helper_mode_valid_fixed, "", "");
KSYMTAB_FUNC(drm_connector_helper_get_modes_from_ddc, "", "");
KSYMTAB_FUNC(drm_connector_helper_get_modes_fixed, "", "");
KSYMTAB_FUNC(drm_connector_helper_get_modes, "", "");
KSYMTAB_FUNC(drm_connector_helper_tv_get_modes, "", "");
KSYMTAB_FUNC(drm_rect_intersect, "", "");
KSYMTAB_FUNC(drm_rect_clip_scaled, "", "");
KSYMTAB_FUNC(drm_rect_calc_hscale, "", "");
KSYMTAB_FUNC(drm_rect_calc_vscale, "", "");
KSYMTAB_FUNC(drm_rect_debug_print, "", "");
KSYMTAB_FUNC(drm_rect_rotate, "", "");
KSYMTAB_FUNC(drm_rect_rotate_inv, "", "");
KSYMTAB_FUNC(drm_self_refresh_helper_update_avg_times, "", "");
KSYMTAB_FUNC(drm_self_refresh_helper_alter_state, "", "");
KSYMTAB_FUNC(drm_self_refresh_helper_init, "", "");
KSYMTAB_FUNC(drm_self_refresh_helper_cleanup, "", "");
KSYMTAB_FUNC(drm_simple_encoder_init, "", "");
KSYMTAB_FUNC(__drmm_simple_encoder_alloc, "", "");
KSYMTAB_FUNC(drm_simple_display_pipe_attach_bridge, "", "");
KSYMTAB_FUNC(drm_simple_display_pipe_init, "", "");
KSYMTAB_FUNC(drm_bridge_is_panel, "", "");
KSYMTAB_FUNC(drm_panel_bridge_add, "", "");
KSYMTAB_FUNC(drm_panel_bridge_add_typed, "", "");
KSYMTAB_FUNC(drm_panel_bridge_remove, "", "");
KSYMTAB_FUNC(drm_panel_bridge_set_orientation, "", "");
KSYMTAB_FUNC(devm_drm_panel_bridge_add, "", "");
KSYMTAB_FUNC(devm_drm_panel_bridge_add_typed, "", "");
KSYMTAB_FUNC(drmm_panel_bridge_add, "", "");
KSYMTAB_FUNC(drm_panel_bridge_connector, "", "");
KSYMTAB_FUNC(devm_drm_of_get_bridge, "", "");
KSYMTAB_FUNC(drmm_of_get_bridge, "", "");
KSYMTAB_FUNC(drm_fbdev_generic_setup, "", "");
KSYMTAB_FUNC(drm_fb_helper_debug_enter, "", "");
KSYMTAB_FUNC(drm_fb_helper_debug_leave, "", "");
KSYMTAB_FUNC(drm_fb_helper_restore_fbdev_mode_unlocked, "", "");
KSYMTAB_FUNC(drm_fb_helper_blank, "", "");
KSYMTAB_FUNC(drm_fb_helper_prepare, "", "");
KSYMTAB_FUNC(drm_fb_helper_unprepare, "", "");
KSYMTAB_FUNC(drm_fb_helper_init, "", "");
KSYMTAB_FUNC(drm_fb_helper_alloc_info, "", "");
KSYMTAB_FUNC(drm_fb_helper_release_info, "", "");
KSYMTAB_FUNC(drm_fb_helper_unregister_info, "", "");
KSYMTAB_FUNC(drm_fb_helper_fini, "", "");
KSYMTAB_FUNC(drm_fb_helper_damage_range, "", "");
KSYMTAB_FUNC(drm_fb_helper_damage_area, "", "");
KSYMTAB_FUNC(drm_fb_helper_deferred_io, "", "");
KSYMTAB_FUNC(drm_fb_helper_set_suspend, "", "");
KSYMTAB_FUNC(drm_fb_helper_set_suspend_unlocked, "", "");
KSYMTAB_FUNC(drm_fb_helper_setcmap, "", "");
KSYMTAB_FUNC(drm_fb_helper_ioctl, "", "");
KSYMTAB_FUNC(drm_fb_helper_check_var, "", "");
KSYMTAB_FUNC(drm_fb_helper_set_par, "", "");
KSYMTAB_FUNC(drm_fb_helper_pan_display, "", "");
KSYMTAB_FUNC(drm_fb_helper_fill_info, "", "");
KSYMTAB_FUNC(drm_fb_helper_initial_config, "", "");
KSYMTAB_FUNC(drm_fb_helper_hotplug_event, "", "");
KSYMTAB_FUNC(drm_fb_helper_lastclose, "", "");
KSYMTAB_FUNC(drm_fb_helper_output_poll_changed, "", "");

MODULE_INFO(depends, "drm,i2c-core");

