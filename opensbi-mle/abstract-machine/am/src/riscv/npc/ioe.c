#include <am.h>
#include <klib-macros.h>

void __am_timer_init();

void __am_timer_rtc(AM_TIMER_RTC_T *);
void __am_timer_uptime(AM_TIMER_UPTIME_T *);
void __am_input_keybrd(AM_INPUT_KEYBRD_T *);

static void __am_timer_config(AM_TIMER_CONFIG_T *cfg) { cfg->present = true; cfg->has_rtc = true; }
static void __am_input_config(AM_INPUT_CONFIG_T *cfg) { cfg->present = true;  }
static void __am_uart_config(AM_INPUT_CONFIG_T *cfg) { cfg->present = false;  }

#ifndef NO_NPC_GPU
#include <am.h>
#include "npc.h"

#define SYNC_ADDR (VGACTL_ADDR + 4)
static uint32_t screen_w=0;
static uint32_t screen_h=0;
static uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;

static void __am_gpu_init() {
  screen_w = inw(VGACTL_ADDR+2);
  screen_h = inw(VGACTL_ADDR);
}

static void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = screen_w, .height = screen_h,
    .vmemsz = screen_w*screen_h
  };
}

static void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  // if (w == 0 || h == 0) return;
  if((ctl->sync|w|h)==0){
    return;
  }else {
    // 使用指针进行内存操作以减少数组索引计算
    uint32_t *pixels = (uint32_t *)ctl->pixels;

    // 遍历每一行
    for (int i = 0; i < h; i++) {
      uint32_t *fb_row = (uint32_t *)fb + screen_w * (y + i) + x;
      uint32_t *pixel_row = (uint32_t *)pixels + w * i;

      // 使用 memcpy 批量复制一行像素数据
      for (int j = 0; j < w; j++) {
        fb_row[j] = pixel_row[j];
      }
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
#endif
typedef void (*handler_t)(void *buf);
static void *lut[128] = {
  [AM_TIMER_CONFIG] = __am_timer_config,
  [AM_TIMER_RTC   ] = __am_timer_rtc,
  [AM_TIMER_UPTIME] = __am_timer_uptime,
  [AM_INPUT_CONFIG] = __am_input_config,
  [AM_INPUT_KEYBRD] = __am_input_keybrd,
  [AM_UART_CONFIG]  = __am_uart_config,
  #ifdef NPC_GPU
  [AM_GPU_CONFIG  ] = __am_gpu_config,
  [AM_GPU_FBDRAW  ] = __am_gpu_fbdraw,
  [AM_GPU_STATUS  ] = __am_gpu_status,
  #endif
};

static void fail(void *buf) { panic("access nonexist register"); }

bool ioe_init() {
    for (int i = 0; i < LENGTH(lut); i++)
    if (!lut[i]) lut[i] = fail;
  #ifdef NPC_GPU
  __am_gpu_init();
  #endif
  __am_timer_init();
  return true;
}

void ioe_read (int reg, void *buf) { ((handler_t)lut[reg])(buf); }
void ioe_write(int reg, void *buf) { ((handler_t)lut[reg])(buf); }
