#include "nitro/os.h"

#define OS_WAIT_FOR_INTERRUPT(zero) mcr p15, 0, zero, c7, c0, 4

#define OS_CACHE_INS(ins) asm(ins);

void OS_Halt(void) {
#ifdef NITRO_NO_ASM
    u32 zero = 0;
    OS_CACHE_INS(OS_WAIT_FOR_INTERRUPT(zero));
#else
    asm("mov r0, 0");
    OS_CACHE_INS(OS_WAIT_FOR_INTERRUPT(r0));
#endif
}
