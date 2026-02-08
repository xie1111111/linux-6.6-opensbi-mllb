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

KSYMTAB_FUNC(drm_sched_fault, "", "");
KSYMTAB_FUNC(drm_sched_suspend_timeout, "", "");
KSYMTAB_FUNC(drm_sched_resume_timeout, "", "");
KSYMTAB_FUNC(drm_sched_stop, "", "");
KSYMTAB_FUNC(drm_sched_start, "", "");
KSYMTAB_FUNC(drm_sched_resubmit_jobs, "", "");
KSYMTAB_FUNC(drm_sched_job_init, "", "");
KSYMTAB_FUNC(drm_sched_job_arm, "", "");
KSYMTAB_FUNC(drm_sched_job_add_dependency, "", "");
KSYMTAB_FUNC(drm_sched_job_add_syncobj_dependency, "", "");
KSYMTAB_FUNC(drm_sched_job_add_resv_dependencies, "", "");
KSYMTAB_FUNC(drm_sched_job_add_implicit_dependencies, "", "");
KSYMTAB_FUNC(drm_sched_job_cleanup, "", "");
KSYMTAB_FUNC(drm_sched_pick_best, "", "");
KSYMTAB_FUNC(drm_sched_init, "", "");
KSYMTAB_FUNC(drm_sched_fini, "", "");
KSYMTAB_FUNC(drm_sched_increase_karma, "", "");
KSYMTAB_FUNC(to_drm_sched_fence, "", "");
KSYMTAB_FUNC(drm_sched_entity_init, "", "");
KSYMTAB_FUNC(drm_sched_entity_modify_sched, "", "");
KSYMTAB_FUNC(drm_sched_entity_error, "", "");
KSYMTAB_FUNC(drm_sched_entity_flush, "", "");
KSYMTAB_FUNC(drm_sched_entity_fini, "", "");
KSYMTAB_FUNC(drm_sched_entity_destroy, "", "");
KSYMTAB_FUNC(drm_sched_entity_set_priority, "", "");
KSYMTAB_FUNC(drm_sched_entity_push_job, "", "");

MODULE_INFO(depends, "drm");

