#include "nitro/gx.h"
#include "nitro/mi.h"
#include "nitro/os.h"

static void GX_InitGXState(void);

static u16 data_020a7088 = 1;
static u32 data_020a708c = 3;

static u16 data_0216a0dc = 0;
static u16 data_0216a0de = 0;
static GX_UnkStruct2 data_0216a0e0;

void GX_Init(void) {
    REG_POWER_CNT |= 0x8000;
    REG_POWER_CNT = (REG_POWER_CNT & ~0x20e) | 0x20e;
    REG_POWER_CNT |= 0x1;

    GX_InitGXState();

    while (data_0216a0de == 0) {
        s32 lock = OS_GetLockID();
        if (lock == OS_LOCK_ID_ERROR) {
            OS_Panic();
        }
        data_0216a0de = lock;
    }

    REG_DISPSTAT = 0;
    REG_DISPCNT  = 0;

    if (data_020a708c != -1) {
        MI_DmaFill32(data_020a708c, &REG_BG0CNT, 0, 0x60);
        REG_MASTER_BRIGHT = 0;
        MI_DmaFill32(data_020a708c, &REG_DISPCNT_SUB, 0, 0x70);
    } else {
        MI_CpuFill32(0, &REG_BG0CNT, 0x60);
        REG_MASTER_BRIGHT = 0;
        MI_CpuFill32(0, &REG_DISPCNT_SUB, 0x70);
    }

    REG_BG2PA     = 0x100;
    REG_BG2PD     = 0x100;
    REG_BG3PA     = 0x100;
    REG_BG3PD     = 0x100;
    REG_BG2PA_SUB = 0x100;
    REG_BG2PD_SUB = 0x100;
    REG_BG3PA_SUB = 0x100;
    REG_BG3PD_SUB = 0x100;
}

u16 GX_HBlankIntr(BOOL param1) {
    u16 prevStat = REG_DISPSTAT & 0x10;
    if (param1) {
        REG_DISPSTAT |= 0x10;
        return prevStat;
    } else {
        REG_DISPSTAT &= ~0x10;
        return prevStat;
    }
}

u16 GX_VBlankIntr(BOOL param1) {
    u16 prevStat = REG_DISPSTAT & 0x8;
    if (param1) {
        REG_DISPSTAT |= 0x8;
        return prevStat;
    } else {
        REG_DISPSTAT &= ~0x8;
        return prevStat;
    }
}

void GX_DispOff(void) {
    u32 cnt       = REG_DISPCNT;
    data_020a7088 = 0;
    data_0216a0dc = (cnt & 0x30000) >> 16;
    REG_DISPCNT   = cnt & ~0x30000;
}

void GX_DispOn(void) {
    data_020a7088 = 1;
    if (data_0216a0dc != 0) {
        REG_DISPCNT = (REG_DISPCNT & ~0x30000) | data_0216a0dc << 16;
        return;
    }
    REG_DISPCNT |= 0x10000;
}

void GX_SetGraphicsMode(u32 param1, u32 param2, u32 param3) {
    u32 cnt       = REG_DISPCNT;
    data_0216a0dc = param1;
    if (data_020a7088 == 0) {
        param1 = 0;
    }
    cnt         = (cnt & ~0xf000f) | (param1 << 16);
    REG_DISPCNT = param2 | cnt | (param3 << 3);
    if (data_0216a0dc == 0) {
        data_020a7088 = 0;
    }
}

void GXS_SetGraphicsMode(u32 mode) {
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x7) | mode;
}

static void GX_InitGXState(void) {
    data_0216a0e0.unk_00 = 0;
    data_0216a0e0.unk_02 = 0;
    data_0216a0e0.unk_04 = 0;
    data_0216a0e0.unk_06 = 0;
    data_0216a0e0.unk_08 = 0;
    data_0216a0e0.unk_0a = 0;
    data_0216a0e0.unk_0c = 0;
    data_0216a0e0.unk_0e = 0;
    data_0216a0e0.unk_10 = 0;
    data_0216a0e0.unk_12 = 0;
    data_0216a0e0.unk_14 = 0;
    data_0216a0e0.unk_16 = 0;
    data_0216a0e0.unk_18 = 0;
    REG_VRAM_CNT_ABCD    = 0;
    REG_VRAM_CNT_E       = 0;
    REG_VRAM_CNT_F       = 0;
    REG_VRAM_CNT_G       = 0;
    REG_VRAM_CNT_HI      = 0;
}
