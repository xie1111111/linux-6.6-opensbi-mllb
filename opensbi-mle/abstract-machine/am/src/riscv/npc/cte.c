#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 0xb:{
#ifdef __riscv_e
        int ecall_event=(int)c->gpr[15];
#else
        int ecall_event=(int)c->gpr[17];
#endif
        if(ecall_event==-1){
          ev.event = EVENT_YIELD;
          c->mepc+=4;// 系统调用,mepc指向将要运行的地址
        }
        else{
          ev.event = EVENT_SYSCALL;
          c->mepc+=4;// 系统调用,mepc指向将要运行的地址
        }
        break;
        }
      case ((1ul<<(__riscv_xlen-1)) | 0x7):ev.event = EVENT_IRQ_TIMER; break;
      case ((1ul<<(__riscv_xlen-1)) | 0x1b):ev.event = EVENT_IRQ_IODEV; break;
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  Context *kc=(Context*)((uint8_t*)kstack.end-sizeof(Context));
  for (int i = 1/* x0 始终为0 */; i < NR_REGS; i ++)
  {
      kc->gpr[i] = (uintptr_t)(0xdeadbeafdeadbeaf);//printf(" %d %p\n",i,(uintptr_t)i<<(64-8));
  }
  kc->gpr[10]=(uintptr_t)arg; 
  kc->gpr[11]=0;kc->gpr[12]=0;// a0~a1 函数参数与返回值
  kc->gpr[13]=0;kc->gpr[14]=0;
  kc->gpr[14]=0;kc->gpr[15]=0;
  #ifndef __riscv_e
  kc->gpr[16]=0;kc->gpr[17]=0;// a2~a7 函数参数
  #endif
  kc->mepc=(uintptr_t)entry;
  *((uintptr_t*)kstack.start)=(uintptr_t)kc;//FIXME t
  return kc;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
  asm volatile("csrrs zero, mstatus, %0" :: "r"(enable << 3));
}
