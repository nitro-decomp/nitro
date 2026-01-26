#include <nitro/gx.h>
#include <nitro/mi.h>
#include <nitro/os.h>

static void GX_func_02068d24(void);

typedef struct GX_UnkStruct1 {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */
} GX_UnkStruct1;

typedef struct GX_UnkStruct2 {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ u16 unk_04;
    /* 06 */ u16 unk_06;
    /* 08 */ u16 unk_08;
    /* 0a */ u16 unk_0a;
    /* 0c */ u16 unk_0c;
    /* 0e */ u16 unk_0e;
    /* 10 */ u16 unk_10;
    /* 12 */ u16 unk_12;
    /* 14 */ u16 unk_14;
    /* 16 */ u16 unk_16;
    /* 18 */ u16 unk_18;
    /* 1a */
} GX_UnkStruct2;

static GX_UnkStruct1 data_0216a0dc;
static GX_UnkStruct2 data_0216a0e0;

void GX_Init(void) {
    REG_POWER_CNT |= 0x8000;
    REG_POWER_CNT = (REG_POWER_CNT & ~0x20e) | 0x20e;
    REG_POWER_CNT |= 0x1;

    GX_func_02068d24();

    while (data_0216a0dc.unk_02 == 0) {
        s32 lock = OS_GetLockID();
        if (lock == OS_LOCK_ID_ERROR) {
            OS_Panic();
        }
        data_0216a0dc.unk_02 = lock;
    }

    REG_DISPSTAT = 0;
    REG_DISPCNT  = 0;

    if (data_020a7088.unk_04 != -1) {
        MI_DmaFill32(data_020a7088.unk_04, &REG_BG0CNT, 0, 0x60);
        REG_MASTER_BRIGHT = 0;
        MI_DmaFill32(data_020a7088.unk_04, &REG_DISPCNT_SUB, 0, 0x70);
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
    u32 cnt              = REG_DISPCNT;
    data_020a7088.unk_00 = 0;
    data_0216a0dc.unk_00 = (cnt & 0x30000) >> 16;
    REG_DISPCNT          = cnt & ~0x30000;
}

void GX_DispOn(void) {
    data_020a7088.unk_00 = 1;
    if (data_0216a0dc.unk_00 != 0) {
        REG_DISPCNT = (REG_DISPCNT & ~0x30000) | data_0216a0dc.unk_00 << 16;
        return;
    }
    REG_DISPCNT |= 0x10000;
}

void GX_SetGraphicsMode(u32 param1, u32 param2, u32 param3) {
    u32 cnt              = REG_DISPCNT;
    data_0216a0dc.unk_00 = param1;
    if (data_020a7088.unk_00 == 0) {
        param1 = 0;
    }
    cnt         = (cnt & ~0xf000f) | (param1 << 16);
    REG_DISPCNT = param2 | cnt | (param3 << 3);
    if (data_0216a0dc.unk_00 == 0) {
        data_020a7088.unk_00 = 0;
    }
}

void GXS_SetGraphicsMode(u32 mode) {
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x7) | mode;
}

static void GX_func_02068d24(void) {
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

static void GX_func_02068d84(u32 cnt) {
    if ((cnt & 0x1) != 0) {
        REG_VRAM_CNT_A = 0x80;
    }
    if ((cnt & 0x2) != 0) {
        REG_VRAM_CNT_B = 0x80;
    }
    if ((cnt & 0x4) != 0) {
        REG_VRAM_CNT_C = 0x80;
    }
    if ((cnt & 0x8) != 0) {
        REG_VRAM_CNT_D = 0x80;
    }
    if ((cnt & 0x10) != 0) {
        REG_VRAM_CNT_E = 0x80;
    }
    if ((cnt & 0x20) != 0) {
        REG_VRAM_CNT_F = 0x80;
    }
    if ((cnt & 0x40) != 0) {
        REG_VRAM_CNT_G = 0x80;
    }
    if ((cnt & 0x80) != 0) {
        REG_VRAM_CNT_H = 0x80;
    }
    if ((cnt & 0x100) != 0) {
        REG_VRAM_CNT_I = 0x80;
    }
}

void GX_SetBankForBG(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_02);
    data_0216a0e0.unk_02 = param1;
    switch (param1) {
        case 0x0:
            break;
        case 0x8:
            REG_VRAM_CNT_D = 0x81;
            break;
        case 0xc:
            REG_VRAM_CNT_D = 0x89;
        case 0x4:
            REG_VRAM_CNT_C = 0x81;
            break;
        case 0xe:
            REG_VRAM_CNT_D = 0x91;
        case 0x6:
            REG_VRAM_CNT_C = 0x89;
        case 0x2:
            REG_VRAM_CNT_B = 0x81;
            break;
        case 0xf:
            REG_VRAM_CNT_D = 0x99;
        case 0x7:
            REG_VRAM_CNT_C = 0x91;
        case 0x3:
            REG_VRAM_CNT_B = 0x89;
        case 0x1:
            REG_VRAM_CNT_A = 0x81;
            break;
        case 0xb:
            REG_VRAM_CNT_A = 0x81;
            REG_VRAM_CNT_B = 0x89;
            REG_VRAM_CNT_D = 0x91;
            break;
        case 0xd:
            REG_VRAM_CNT_D = 0x91;
        case 0x5:
            REG_VRAM_CNT_A = 0x81;
            REG_VRAM_CNT_C = 0x89;
            break;
        case 0x9:
            REG_VRAM_CNT_A = 0x81;
            REG_VRAM_CNT_D = 0x89;
            break;
        case 0xa:
            REG_VRAM_CNT_B = 0x81;
            REG_VRAM_CNT_D = 0x89;
            break;
        case 0x70:
            REG_VRAM_CNT_G = 0x99;
        case 0x30:
            REG_VRAM_CNT_F = 0x91;
        case 0x10:
            REG_VRAM_CNT_E = 0x81;
            break;
        case 0x50:
            REG_VRAM_CNT_G = 0x91;
            REG_VRAM_CNT_E = 0x81;
            break;
        case 0x60:
            REG_VRAM_CNT_G = 0x89;
        case 0x20:
            REG_VRAM_CNT_F = 0x81;
            break;
        case 0x40:
            REG_VRAM_CNT_G = 0x81;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

void GX_SetBankForOBJ(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_04);
    data_0216a0e0.unk_04 = param1;
    switch (param1) {
        case 0x0:
            break;
        case 0x3:
            REG_VRAM_CNT_B = 0x8a;
        case 0x1:
            REG_VRAM_CNT_A = 0x82;
            break;
        case 0x2:
            REG_VRAM_CNT_B = 0x82;
            break;
        case 0x70:
            REG_VRAM_CNT_G = 0x9a;
        case 0x30:
            REG_VRAM_CNT_F = 0x92;
        case 0x10:
            REG_VRAM_CNT_E = 0x82;
            break;
        case 0x50:
            REG_VRAM_CNT_G = 0x92;
            REG_VRAM_CNT_E = 0x82;
            break;
        case 0x60:
            REG_VRAM_CNT_G = 0x8a;
        case 0x20:
            REG_VRAM_CNT_F = 0x82;
            break;
        case 0x40:
            REG_VRAM_CNT_G = 0x82;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

void GX_func_0206921c(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_0e);
    data_0216a0e0.unk_0e = param1;
    switch (param1) {
        case 0x10:
            REG_DISPCNT |= 0x40000000;
            REG_VRAM_CNT_E = 0x84;
            break;
        case 0x40:
            REG_DISPCNT |= 0x40000000;
            REG_VRAM_CNT_G = 0x8c;
            break;
        case 0x60:
            REG_VRAM_CNT_G = 0x8c;
        case 0x20:
            REG_VRAM_CNT_F = 0x84;
            REG_DISPCNT |= 0x40000000;
            break;
        case 0x0:
            REG_DISPCNT &= ~0x40000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

BOOL GX_TrySetBankForBGExtPltt(s32 param1) {
    if (!OS_func_0206d5ac(param1, data_0216a0dc.unk_02)) {
        return false;
    }
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_0e);
    data_0216a0e0.unk_0e = param1;
    switch (param1) {
        case 0x10:
            REG_DISPCNT |= 0x40000000;
            REG_VRAM_CNT_E = 0x84;
            break;
        case 0x40:
            REG_DISPCNT |= 0x40000000;
            REG_VRAM_CNT_G = 0x8c;
            break;
        case 0x60:
            REG_VRAM_CNT_G = 0x8c;
        case 0x20:
            REG_VRAM_CNT_F = 0x84;
            REG_DISPCNT |= 0x40000000;
            break;
        case 0x0:
            REG_DISPCNT &= ~0x40000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
    return true;
}

void GX_func_02069448(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_10);
    data_0216a0e0.unk_10 = param1;
    switch (param1) {
        case 0x20:
            REG_DISPCNT |= 0x80000000;
            REG_VRAM_CNT_F = 0x85;
            break;
        case 0x40:
            REG_DISPCNT |= 0x80000000;
            REG_VRAM_CNT_G = 0x85;
            break;
        case 0x0:
            REG_DISPCNT &= ~0x80000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

BOOL GX_TrySetBankForOBJExtPltt(s32 param1) {
    if (!OS_func_0206d5ac(param1, data_0216a0dc.unk_02)) {
        return false;
    }
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_0e);
    data_0216a0e0.unk_0e = param1;
    switch (param1) {
        case 0x20:
            REG_DISPCNT |= 0x80000000;
            REG_VRAM_CNT_F = 0x85;
            break;
        case 0x40:
            REG_DISPCNT |= 0x80000000;
            REG_VRAM_CNT_G = 0x85;
            break;
        case 0x0:
            REG_DISPCNT &= ~0x80000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
    return true;
}

void GX_SetBankForLCDC(s32 param1) {
    data_0216a0e0.unk_00 |= param1;
    GX_func_02068d84(param1);
}

void GX_SetBankForSubBG(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_12);
    data_0216a0e0.unk_12 = param1;
    switch (param1) {
        case 0x1:
            break;
        case 0x4:
            REG_VRAM_CNT_C = 0x84;
            break;
        case 0x180:
            REG_VRAM_CNT_I = 0x81;
        case 0x80:
            REG_VRAM_CNT_H = 0x81;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}
