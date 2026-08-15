#include "nitro/os/cache.h"

#define DC_DRAIN_WRITE_BUFFER(zero) mcr p15, 0, zero, c7, c10, 4

#define DC_CLEAN_INVALIDATE_VA(addr) mcr p15, 0, addr, c7, c14, 1
#define DC_CLEAN_INVALIDATE_SI(si) mcr p15, 0, si, c7, c14, 2

#define DC_FLUSH_VA(zero, si)    \
    DC_DRAIN_WRITE_BUFFER(zero); \
    DC_CLEAN_INVALIDATE_VA(si);

#define DC_FLUSH_SI(zero, si)    \
    DC_DRAIN_WRITE_BUFFER(zero); \
    DC_CLEAN_INVALIDATE_SI(si);

#define DC_INVALIDATE(line) mcr p15, 0, line, c7, c6, 1

#define DC_CLEAN(line) mcr p15, 0, ptr, c7, c10, 1

#define IC_INVALIDATE_ALL(zero) mcr p15, 0, zero, c7, c5, 0
#define IC_INVALIDATE(line) mcr p15, 0, line, c7, c5, 1

#define OS_CACHE_INS(ins) asm(ins);

void DC_FlushAll(void) {
#ifdef NITRO_NO_ASM
    s32 bank;
    s32 si;
    s32 line;
    s32 zero;

    zero = 0;
    bank = 0;
    do {
        line = 0;
        do {
            si = bank | line;
            OS_CACHE_INS(DC_FLUSH(zero, si));
            line += OS_CACHE_LINE_SIZE;
        } while (line < 0x400);
        bank += 0x40000000;
    } while (bank != 0);
#else
    s32 line;
    s32 bank;
    s32 si;

    asm {
        mov ip, 0
        mov bank, 0
    loop_bank:
        mov line, 0
    loop_line:
        orr si, bank, line
        DC_FLUSH_SI(ip, si)
        add line, line, OS_CACHE_LINE_SIZE
        cmp line, 0x400
        blt loop_line
    end_loop_line:
        add bank, bank, 0x40000000
        cmp bank, 0
        bne loop_bank
    end:
    }
#endif
}

void DC_InvalidateRange(void *ptr, u32 size) {
    s32 end;

    end = size + (s32) ptr;
    ptr = (void *) ((s32) ptr & ~(OS_CACHE_LINE_SIZE - 1));
    do {
        OS_CACHE_INS(DC_INVALIDATE(ptr));
        ptr += OS_CACHE_LINE_SIZE;
    } while ((s32) ptr < end);
}

void DC_StoreRange(void *ptr, u32 size) {
    s32 end;

    end = size + (s32) ptr;
    ptr = (void *) ((s32) ptr & ~(OS_CACHE_LINE_SIZE - 1));
    do {
        OS_CACHE_INS(DC_CLEAN(ptr));
        ptr += OS_CACHE_LINE_SIZE;
    } while ((s32) ptr < end);
}

void DC_FlushRange(void *ptr, u32 size) {
#ifdef NITRO_NO_ASM
    s32 end;
    s32 zero;

    zero = 0;

    end = size + (s32) ptr;
    ptr = (void *) ((s32) ptr & ~(OS_CACHE_LINE_SIZE - 1));
    do {
        OS_CACHE_INS(DC_FLUSH_VA(zero, ptr));
        ptr += OS_CACHE_LINE_SIZE;
    } while ((s32) ptr < end);
#else
    asm("mov ip, 0");
    s32 end;

    end = size + (s32) ptr;
    ptr = (void *) ((s32) ptr & ~(OS_CACHE_LINE_SIZE - 1));
    do {
        OS_CACHE_INS(DC_FLUSH_VA(ip, ptr));
        ptr += OS_CACHE_LINE_SIZE;
    } while ((s32) ptr < end);
#endif
}

void DC_DrainWriteBuffer(void) {
#ifdef NITRO_NO_ASM
    s32 zero = 0;
    OS_CACHE_INS(DC_DRAIN_WRITE_BUFFER(zero));
#else
    asm("mov r0, 0");
    OS_CACHE_INS(DC_DRAIN_WRITE_BUFFER(r0));
#endif
}

void IC_InvalidateAll(void) {
#ifdef NITRO_NO_ASM
    s32 zero = 0;
    OS_CACHE_INS(IC_INVALIDATE_ALL(zero));
#else
    asm("mov r0, 0");
    OS_CACHE_INS(IC_INVALIDATE_ALL(r0));
#endif
}

void IC_InvalidateRange(void *ptr, u32 size) {
    s32 end;

    end = size + (s32) ptr;
    ptr = (void *) ((s32) ptr & ~(OS_CACHE_LINE_SIZE - 1));
    do {
        OS_CACHE_INS(IC_INVALIDATE(ptr));
        ptr += OS_CACHE_LINE_SIZE;
    } while ((s32) ptr < end);
}
