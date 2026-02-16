#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/reg.h"

static void MI_func_0001(u8 param1);
static void MI_func_0006(s32 param1, void *param2, s32 param3, s32 param4);
static s32 MI_func_0010(s32 param1, void *param2, u32 param3, u32 param4, u32 param5);

void MI_func_0013(s32 dma, u32 param2, void *param3, BOOL param4, BOOL param5);
void MI_func_0014(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5);
void MI_func_0015(s32 dma, void *param2, u32 param3, BOOL param4, BOOL param5);
void MI_func_0016(s32 param1, u32 param2, void *param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7);
void MI_func_0017(s32 param1, void *param2, u32 param3, BOOL param4, void (*param5)(u32), u32 param6, BOOL param7);
void MI_func_0018(s32 param1);

inline u32 MI_DmaBusyFlag(u32 dma) {
    vu32 *dmasad = (vu32 *) ((u32) &REG_DMA0SAD + (dma * 3 + 2) * sizeof(u32));
    return (*dmasad & 0x80000000);
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
    if (param7 != 0) {
        MI_func_0010(param1, param2, param3, param4 >> 2 | 0x84000000, 0);
    } else {
        MI_func_0010(param1, param2, param3, param4 >> 2 | 0x4000000, 4);
    }
}
