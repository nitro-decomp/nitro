#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/reg.h"

static void MI_func_0001(u8 param1);
static void MI_func_0004(s32 id);
static void MI_func_0005(s32 id, u32 param2);
static void MI_func_0006(BOOL param1, void *param2, s32 param3, s32 param4);
static s32 MI_func_0010(s32 param1, void *param2, u32 param3, u32 param4, u32 param5);

void MI_func_0007(void *inSrc, void *inDst, u32 size);
void MI_func_0013(s32 dma, u32 param2, void *param3, BOOL param4, BOOL param5);
void MI_func_0014(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5);
void MI_func_0015(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5);
void MI_func_0016(s32 param1, u32 param2, void *param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7);
void MI_func_0017(s32 param1, void *param2, u32 param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7);
void MI_func_0018(s32 param1);
void MI_func_0020(void);
void MI_CpuFill16(u16 value, void *buf, u32 size);

inline u32 MI_DmaBusyFlag(u32 dma) {
    return *(vu32 *) &(&REG_DMA0SAD)[dma * 3 + 2] & 0x80000000;
}

inline void MI_WaitDma(u32 dma) {
    while (MI_DmaBusyFlag(dma)) {
    }
}

static void MI_func_0001(u8 param1) {
    REG_WRAM_CNT = param1;
}

void MI_func_0013(s32 dma, u32 param2, void *param3, BOOL param4, BOOL param5) {
    if (!param4) {
        return;
    }

    MI_WaitDma(dma);
    if (param5) {
        MI_func_0010(dma, param3, param2, param4 >> 2 | 0x85000000, 0x12);
    } else {
        MI_func_0010(dma, param3, param2, param4 >> 2 | 0x5000000, 0x16);
    }
    MI_WaitDma(dma);
}

void MI_func_0014(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5) {
    if (!param4) {
        return;
    }

    MI_func_0006(dma, param2, param4, 0);
    MI_WaitDma(dma);
    if (param5) {
        MI_func_0010(dma, param2, param3, param4 >> 2 | 0x84000000, 0x2);
    } else {
        MI_func_0010(dma, param2, param3, param4 >> 2 | 0x4000000, 0x6);
    }
    MI_WaitDma(dma);
}

void MI_func_0015(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5) {
    if (!param4) {
        return;
    }

    MI_func_0006(dma, param2, param4, 0);
    MI_WaitDma(dma);
    if (param5) {
        MI_func_0010(dma, param2, param3, param4 >> 1 | 0x80000000, 0x2);
    } else {
        MI_func_0010(dma, param2, param3, param4 >> 1, 0x6);
    }
    MI_WaitDma(dma);
}

void MI_func_0016(s32 param1, u32 param2, void *param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7) {
    if (!param4) {
        if (param5) {
            (*param5)(param6);
        }
        return;
    }

    MI_func_0018(param1);
    if (param5) {
        OS_func_0013(param1, param5, param6);
        if (param7) {
            MI_func_0010(param1, param3, param2, param4 >> 2 | 0xc5000000, 0x10);
        } else {
            MI_func_0010(param1, param3, param2, param4 >> 2 | 0x45000000, 0x14);
        }
    } else if (param7) {
        MI_func_0010(param1, param3, param2, param4 >> 2 | 0x85000000, 0x10);
    } else {
        MI_func_0010(param1, param3, param2, param4 >> 2 | 0x5000000, 0x14);
    }
}

void MI_func_0017(s32 param1, void *param2, u32 param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7) {
    MI_func_0006(param1, param2, param4, 0);
    if (!param4) {
        if (param5) {
            (*param5)(param6);
        }
        return;
    }

    MI_func_0018(param1);
    if (param5) {
        OS_func_0013(param1, param5, param6);
        if (param7 != 0) {
            MI_func_0010(param1, param2, param3, param4 >> 2 | 0xc4000000, 0);
        } else {
            MI_func_0010(param1, param2, param3, param4 >> 2 | 0x44000000, 4);
        }
        return;
    }
    if (param7) {
        MI_func_0010(param1, param2, param3, param4 >> 2 | 0x84000000, 0);
    } else {
        MI_func_0010(param1, param2, param3, param4 >> 2 | 0x4000000, 4);
    }
}

void MI_func_0018(s32 id) {
    OSIntrMode intr = OS_DisableInterrupts();
    do {
    } while (REG_DMA[id].cnt & 0x80000000);
    if (id == 0) {
        OSDma *dma = &REG_DMA[id];
        dma->src   = NULL;
        dma->dst   = NULL;
        dma->cnt   = 0x81400001;
    }
    OS_RestoreInterrupts(intr);
}

static void MI_func_0004(s32 id) {
    OSIntrMode intr = OS_DisableInterrupts();
    REG_DMA[id].cnt &= ~0x3a000000;
    REG_DMA[id].cnt &= ~0x80000000;
    REG_DMA[id].cnt;
    REG_DMA[id].cnt;
    if (id == 0) {
        OSDma *dma = &REG_DMA[id];
        dma->src   = NULL;
        dma->dst   = NULL;
        dma->cnt   = 0x81400001;
    }
    OS_RestoreInterrupts(intr);
}

void MI_func_0020(void) {
    MI_func_0004(0);
    MI_func_0004(1);
    MI_func_0004(2);
    MI_func_0004(3);
}

static void MI_func_0005(s32 id, u32 param2) {
    s32 i;
    for (i = 0; i < 3; ++i) {
        if (i == id) {
            continue;
        }
        u32 cnt = REG_DMA[i].cnt;
        if ((cnt & 0x80000000) == 0) {
            continue;
        }
        cnt &= 0x38000000;
        if (cnt != param2 && (cnt != 0x8000000 || param2 != 0x10000000) && (cnt != 0x10000000 || param2 != 0x8000000) &&
            (cnt == 0x18000000 || cnt == 0x20000000 || cnt == 0x28000000 || cnt == 0x30000000 || cnt == 0x38000000 ||
             cnt == 0x8000000 || cnt == 0x10000000)) {
            OS_Panic();
        }
    }
}

void MI_func_0006(BOOL param1, void *param2, s32 param3, s32 param4) {
    u32 before;
    u32 after;

    if (param1) {
        return;
    }
    before = (u32) param2 & 0xff000000;
    switch (param4) {
        case 0:
            param2 += param3;
            break;
        case 0x800000:
            param2 -= param3;
            break;
    }
    after = (u32) param2 & 0xff000000;
    if (before == 0x4000000 || before >= 0x8000000 || after == 0x4000000 || after >= 0x8000000) {
        OS_Panic();
    }
}

void MI_CpuFill16(u16 value, void *inBuf, u32 size) {
    u16 *buf = inBuf;
#ifdef NITRO_NO_ASM
    while (buf < inBuf + size) {
        *buf++ = value;
    }
#else
    u32 i = 0;
    asm {
    loop:
        cmp i, size
        strlth value, [buf, i]
        addlt i, i, #0x2
        blt loop
    }
#endif
}

void MI_CpuCopy16(void *inSrc, void *inDst, u32 size) {
    u16 *src = inSrc;
    u16 *dst = inDst;
#ifdef NITRO_NO_ASM
    while (dst < inDst + size) {
        *dst++ = *src++;
    }
#else
    u32 tmp;
    u32 i = 0;
    asm {
    loop:
        cmp i, size
        ldrlth tmp, [src, i]
        strlth tmp, [dst, i]
        addlt i, i, #0x2
        blt loop
    }
#endif
}

void MI_CpuFill32(u32 value, void *inBuf, u32 size) {
    u32 *buf = inBuf;
#ifdef NITRO_NO_ASM
    while (buf < inBuf + size) {
        *buf++ = value;
    }
#else
    // clang-format off
    asm {
        add ip, inBuf, size
    loop:
        cmp buf, ip
        stmltia buf!, {r0}
        blt loop
    }
    // clang-format on
#endif
}

void MI_CpuCopy32(void *inSrc, void *inDst, u32 size) {
    u32 *src = inSrc;
    u32 *dst = inDst;
#ifdef NITRO_NO_ASM
    while (dst < inDst + size) {
        *dst++ = *src++;
    }
#else
    // clang-format off
    asm {
        add ip, inDst, size
    loop:
        cmp dst, ip
        ldmltia src!, {r2}
        stmltia dst!, {r2}
        blt loop
    }
    // clang-format on
#endif
}

#ifdef NITRO_NO_ASM
void _MI_CpuFill(u32 value, void *inBuf, u32 size) {
    u32 *buf        = inBuf;
    u32 alignedSize = size / 32 * 32;
    while (buf < inBuf + alignedSize) {
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
        *buf++ = value;
    }
    while (buf < inBuf + size) {
        *buf++ = value;
    }
}
#else
// clang-format off
asm void _MI_CpuFill(u32 value, void *inBuf, u32 size) {
    stmdb sp!, {r4-r9}
    add r9, r1, r2
    mov ip, r2, lsr #0x5
    add ip, r1, ip, lsl #0x5
    mov r2, r0
    mov r3, r2
    mov r4, r2
    mov r5, r2
    mov r6, r2
    mov r7, r2
    mov r8, r2
alignedLoop:
    cmp r1, ip
    stmltia r1!, {r0, r2-r8}
    blt alignedLoop
remainderLoop:
    cmp r1, r9
    stmltia r1!, {r0}
    blt remainderLoop
end:
    ldmia sp!, {r4-r9}
    bx lr
}
// clang-format on
#endif

#ifdef NITRO_NITRO_NO_ASM
void MI_func_0007(void *inSrc, void *inDst, u32 size) {
    u32 *src        = inSrc;
    u32 *dst        = inDst;
    u32 alignedSize = size / 32 * 32;
    typedef struct {
        u32 data[4];
    } CopyStruct;
    while (dst < inDst + alignedSize) {
        *(CopyStruct *) dst       = *(CopyStruct *) src;
        *(CopyStruct *) (dst + 4) = *(CopyStruct *) (src + 4);
        dst += 8;
        src += 8;
    }
    while (dst < inDst + size) {
        *dst++ = *src++;
    }
}
#else
// clang-format off
asm void MI_func_0007(void *inSrc, void *inDst, u32 size) {
    stmdb sp!, {r4-r10}
    add r10, r1, r2
    mov ip, r2, lsr #0x5
    add ip, r1, ip, lsl #0x5
alignedLoop:
    cmp r1, ip
    ldmltia r0!, {r2-r9}
    stmltia r1!, {r2-r9}
    blt alignedLoop
remainderLoop:
    cmp r1, r10
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt remainderLoop
end:
    ldmia sp!, {r4-r10}
    bx lr
}
#endif
// clang-format on

void MI_CpuFill8(void *inBuf, u8 inValue, u32 size) {
    u32 *buf  = inBuf;
    u32 value = inValue;
    u32 r3;
    u32 ip;
    if (size == 0) {
        return;
    }
    if (((u32) buf & 1) != 0) {
        *(u16 *) ((u32) buf - 1) = ((u8) * (u16 *) ((u32) buf - 1)) | (value << 8);
        buf                      = (u32 *) ((u32) buf + 1);
        size -= 1;
        if (size == 0) {
            return;
        }
    }
    if (size >= 2) {
        value |= (value << 8);
        if (((u32) buf & 2) != 0) {
            *((u16 *) buf)++ = value;
            size -= 2;
            if (size == 0) {
                return;
            }
        }
        value |= (value << 16);
        r3 = size & ~3;
        if (r3 > 0) {
            size -= r3;
            ip = r3 + (u32) buf;
            do {
                *buf++ = value;
            } while (buf < (void *) ip);
        }
        if ((size & 2) != 0) {
            *((u16 *) buf)++ = value;
        }
    }
    if ((size & 1) != 0) {
        (*(u16 *) buf) = ((*(u16 *) buf) & 0xff00) | (u8) value;
    }
}

void MI_CpuCopy8(void *inSrc, void *inDst, u32 size) {
    u32 temp_ip;
    u32 temp_r3;
    u32 src;
    u32 dst;

    src = (u32) inSrc;
    dst = (u32) inDst;
    if (size == 0) {
        return;
    }
    if (dst & 1) {
        temp_ip = (u8) * (u16 *) (dst - 1);
        if ((src & 1) != 0) {
            temp_r3 = *(u16 *) (src - 1);
            temp_r3 >>= 8;
        } else {
            temp_r3 = *(u16 *) src;
        }
        *(u16 *) (dst - 1) = (u16) (temp_ip | (temp_r3 << 8));
        src += 1;
        dst += 1;
        size -= 1;
        if (size == 0) {
            return;
        }
    }
    if (((dst ^ src) & 1) != 0) {
        src &= ~1;
        temp_r3 = (u32) * (u16 *) src >> 8;
        src += 2;
        while ((size -= 2) >= 2) {
            src += 2;
            temp_ip      = temp_r3 | (*(u16 *) src << 8);
            *(u16 *) dst = temp_ip;
            dst += 2;
            temp_r3 = temp_ip >> 16;
        }
        if ((size & 1) != 0) {
            *(u16 *) dst = (*(u16 *) dst & 0xff00) | temp_r3;
        }
        return;
    }
    if (((dst ^ src) & 2) != 0) {
        temp_r3 = size & ~1;
        if (temp_r3 > 0) {
            size -= temp_r3;
            temp_ip = temp_r3 + dst;
            do {
                *(u16 *) dst = *(u16 *) src;
                src += 2;
                dst += 2;
            } while (dst < temp_ip);
        }
    } else if (size >= 2) {
        if (dst & 2) {
            *(u16 *) dst = *(u16 *) src;
            src += 2;
            dst += 2;
            size -= 2;
            if (size == 0) {
                return;
            }
        }
        temp_r3 = size & ~3;
        if (temp_r3 != 0) {
            size -= temp_r3;
            temp_ip = temp_r3 + dst;
            do {
                *(s32 *) dst = *(s32 *) src;
                src += 4;
                dst += 4;
            } while (dst < temp_ip);
        }
        if ((size & 2) != 0) {
            *(u16 *) dst = *(u16 *) src;
            src += 2;
            dst += 2;
        }
    }
    if ((size & 1) != 0) {
        *(u16 *) dst = (u16) ((*(u16 *) dst & 0xFF00) | (u8) * (u16 *) src);
    }
}
