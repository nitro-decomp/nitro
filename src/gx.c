#include "nitro/gx.h"
#include "nitro/g2.h"
#include "nitro/hw.h"
#include "nitro/mi.h"
#include "nitro/os.h"

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

typedef struct GX_UnkStruct3 {
    /* 00 */ u32 unk_00;
    /* 04 */ void *unk_04;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ void *unk_10;
    /* 14 */ s32 unk_14;
    /* 18 */ u32 unk_18;
    /* 1c */
} GX_UnkStruct3;

static GX_UnkStruct1 data_0216a0dc;
static GX_UnkStruct2 data_0216a0e0;
static GX_UnkStruct3 data_0216a0fc;

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

static void GX_func_0206921c(s32 param1) {
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

static void GX_func_02069448(s32 param1) {
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

void GX_SetBankForSubOBJ(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_14);
    data_0216a0e0.unk_14 = param1;
    switch (param1) {
        case 0x0:
            break;
        case 0x8:
            REG_VRAM_CNT_D = 0x84;
            break;
        case 0x100:
            REG_VRAM_CNT_I = 0x82;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

static void GXS_func_02069704(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_16);
    data_0216a0e0.unk_16 = param1;
    switch (param1) {
        case 0x80:
            REG_DISPCNT_SUB |= 0x40000000;
            REG_VRAM_CNT_H = 0x82;
            break;
        case 0x0:
            REG_DISPCNT_SUB &= ~0x40000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

BOOL GX_TrySetBankForSubBGExtPltt(s32 param1) {
    if (!OS_func_0206d5ac(param1, data_0216a0dc.unk_02)) {
        return false;
    }
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_16);
    data_0216a0e0.unk_16 = param1;
    switch (param1) {
        case 0x80:
            REG_DISPCNT_SUB |= 0x40000000;
            REG_VRAM_CNT_H = 0x82;
            break;
        case 0x0:
            REG_DISPCNT_SUB &= ~0x40000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
    return true;
}

static void GXS_func_02069830(s32 param1) {
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_18);
    data_0216a0e0.unk_18 = param1;
    switch (param1) {
        case 0x100:
            REG_DISPCNT_SUB |= 0x80000000;
            REG_VRAM_CNT_I = 0x83;
            break;
        case 0x0:
            REG_DISPCNT_SUB &= ~0x80000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
}

BOOL GX_TrySetBankForSubOBJExtPltt(s32 param1) {
    if (!OS_func_0206d5ac(param1 & 0xffff, data_0216a0dc.unk_02)) {
        return false;
    }
    data_0216a0e0.unk_00 = ~param1 & (data_0216a0e0.unk_00 | data_0216a0e0.unk_18);
    data_0216a0e0.unk_18 = param1;
    switch (param1) {
        case 0x100:
            REG_DISPCNT_SUB |= 0x80000000;
            REG_VRAM_CNT_I = 0x83;
            break;
        case 0x0:
            REG_DISPCNT_SUB &= ~0x80000000;
            break;
    }
    GX_func_02068d84(data_0216a0e0.unk_00);
    return true;
}

static u16 GX_func_0206995c(u16 *param1) {
    u16 uVar1 = *param1;
    *param1   = 0;
    data_0216a0e0.unk_00 |= uVar1;
    GX_func_02068d84(uVar1);
    return uVar1;
}

u16 GX_ResetBankForBGExtPltt(void) {
    REG_DISPCNT &= ~0x40000000;
    return GX_func_0206995c(&data_0216a0e0.unk_0e);
}

u16 GX_ResetBankForOBJExtPltt(void) {
    REG_DISPCNT &= ~0x80000000;
    return GX_func_0206995c(&data_0216a0e0.unk_10);
}

u16 GX_ResetBankForSubBGExtPltt(void) {
    REG_DISPCNT_SUB &= ~0x40000000;
    return GX_func_0206995c(&data_0216a0e0.unk_16);
}

u16 GX_ResetBankForSubOBJExtPltt(void) {
    REG_DISPCNT_SUB &= ~0x80000000;
    return GX_func_0206995c(&data_0216a0e0.unk_18);
}

static u32 GX_func_02069a28(u16 *param1) {
    u32 uVar1 = *param1;
    *param1   = 0;
    if ((uVar1 & 0x1) != 0) {
        REG_VRAM_CNT_A = 0;
    }
    if ((uVar1 & 0x2) != 0) {
        REG_VRAM_CNT_B = 0;
    }
    if ((uVar1 & 0x4) != 0) {
        REG_VRAM_CNT_C = 0;
    }
    if ((uVar1 & 0x8) != 0) {
        REG_VRAM_CNT_D = 0;
    }
    if ((uVar1 & 0x10) != 0) {
        REG_VRAM_CNT_E = 0;
    }
    if ((uVar1 & 0x20) != 0) {
        REG_VRAM_CNT_F = 0;
    }
    if ((uVar1 & 0x40) != 0) {
        REG_VRAM_CNT_G = 0;
    }
    if ((uVar1 & 0x80) != 0) {
        REG_VRAM_CNT_H = 0;
    }
    if ((uVar1 & 0x100) != 0) {
        REG_VRAM_CNT_I = 0;
    }
    OS_func_0206d66c(uVar1, data_0216a0dc.unk_02);
    return uVar1;
}

void GX_DisableBankForLCDC(void) {
    GX_func_02069a28(&data_0216a0e0.unk_00);
}

static void *G2_func_02069b1c(void) {
    u32 cnt = (REG_BG0CNT & 0x1f00) >> 8;
    return ((REG_DISPCNT & 0x38000000) >> 27 << 16) + HW_BG_VRAM + (cnt << 11);
}

static void *G2S_func_02069b50(void) {
    return ((REG_BG0CNT_SUB & 0x1f00) >> 8 << 11) + HW_DB_BG_VRAM;
}

static void *G2_func_02069b70(void) {
    u32 cnt = (REG_BG1CNT & 0x1f00) >> 8;
    return ((REG_DISPCNT & 0x38000000) >> 27 << 16) + HW_BG_VRAM + (cnt << 11);
}

static void *G2S_func_02069ba4(void) {
    return ((REG_BG1CNT_SUB & 0x1f00) >> 8 << 11) + HW_DB_BG_VRAM;
}

void *G2_GetBG2ScrPtr(void) {
    u32 uVar1 = REG_DISPCNT & 0x7;
    u32 uVar2 = REG_BG2CNT;
    u32 uVar3 = (REG_DISPCNT & 0x38000000) >> 27 << 16;
    u32 uVar4 = (uVar2 & 0x1f00) >> 8;
    switch (uVar1) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return uVar3 + HW_BG_VRAM + (uVar4 << 11);
        case 5:
            if ((uVar2 & 0x80) != 0) {
                return (uVar4 << 14) + HW_BG_VRAM;
            } else {
                return uVar3 + HW_BG_VRAM + (uVar4 << 11);
            }
        case 6:
            return HW_BG_VRAM;
        default:
            return 0;
    }
}

static void *G2S_func_02069c48(void) {
    u32 uVar1 = REG_DISPCNT_SUB & 0x7;
    u32 uVar2 = REG_BG2CNT_SUB;
    u32 uVar3 = (uVar2 & 0x1f00) >> 8;
    switch (uVar1) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return (uVar3 << 11) + HW_DB_BG_VRAM;
        case 5:
            if ((uVar2 & 0x80) != 0) {
                return (uVar3 << 14) + HW_DB_BG_VRAM;
            } else {
                return (uVar3 << 11) + HW_DB_BG_VRAM;
            }
        case 6:
            return 0;
        default:
            return 0;
    }
}

void *G2_GetBG3ScrPtr(void) {
    u32 uVar1 = REG_DISPCNT & 0x7;
    u32 uVar2 = REG_BG3CNT;
    u32 uVar3 = (REG_DISPCNT & 0x38000000) >> 27 << 16;
    u32 uVar4 = (uVar2 & 0x1f00) >> 8;
    switch (uVar1) {
        case 0:
        case 1:
        case 2:
            return uVar3 + HW_BG_VRAM + (uVar4 << 11);
        case 3:
        case 4:
        case 5:
            if ((uVar2 & 0x80) != 0) {
                return (uVar4 << 14) + HW_BG_VRAM;
            } else {
                return uVar3 + HW_BG_VRAM + (uVar4 << 11);
            }
        case 6:
            return 0;
        default:
            return 0;
    }
}

static void *G2S_func_02069d40(void) {
    u32 uVar1 = REG_DISPCNT_SUB & 0x7;
    u32 uVar2 = REG_BG3CNT_SUB;
    u32 uVar3 = (uVar2 & 0x1f00) >> 8;
    switch (uVar1) {
        case 0:
        case 1:
        case 2:
            return (uVar3 << 11) + HW_DB_BG_VRAM;
        case 3:
        case 4:
        case 5:
            if ((uVar2 & 0x80) != 0) {
                return (uVar3 << 14) + HW_DB_BG_VRAM;
            } else {
                return (uVar3 << 11) + HW_DB_BG_VRAM;
            }
        case 6:
            return 0;
        default:
            return 0;
    }
}

static void *G2_func_02069db4(void) {
    u32 r1   = (REG_BG0CNT & 0x3c) >> 2;
    void *r0 = ((REG_DISPCNT & 0x7000000) >> 24 << 16) + HW_BG_VRAM;
    return r0 + (r1 << 14);
}

static void *G2S_func_02069de8(void) {
    return ((REG_BG0CNT_SUB & 0x3c) >> 2 << 14) + HW_DB_BG_VRAM;
}

static void *G2_func_02069e08(void) {
    u32 r1   = (REG_BG1CNT & 0x3c) >> 2;
    void *r0 = ((REG_DISPCNT & 0x7000000) >> 24 << 16) + HW_BG_VRAM;
    return r0 + (r1 << 14);
}

static void *G2S_func_02069e3c(void) {
    return ((REG_BG1CNT_SUB & 0x3c) >> 2 << 14) + HW_DB_BG_VRAM;
}

static void *G2_func_02069e5c(void) {
    s32 r0 = REG_DISPCNT & 0x7;
    u32 r2 = REG_BG2CNT;
    if (r0 < 5 || (r2 & 0x80) == 0) {
        return ((REG_DISPCNT & 0x7000000) >> 24 << 16) + HW_BG_VRAM + ((u32) (r2 & 0x3c) >> 2 << 14);
    }
    return 0;
}

static void *G2S_func_02069eac(void) {
    s32 r0 = REG_DISPCNT_SUB & 0x7;
    u32 r1 = REG_BG2CNT_SUB;
    if (r0 < 5 || (r1 & 0x80) == 0) {
        return ((r1 & 0x3c) >> 2 << 14) + HW_DB_BG_VRAM;
    }
    return 0;
}

static void *G2_func_02069eec(void) {
    s32 r0 = REG_DISPCNT & 0x7;
    u32 r2 = REG_BG3CNT;
    if (r0 < 3 || (r0 < 6 && (r2 & 0x80) == 0)) {
        return ((REG_DISPCNT & 0x7000000) >> 24 << 16) + HW_BG_VRAM + ((u32) (r2 & 0x3c) >> 2 << 14);
    }
    return 0;
}

static void *G2S_func_02069f44(void) {
    s32 r0 = REG_DISPCNT_SUB & 0x7;
    u32 r1 = REG_BG3CNT_SUB;
    if (r0 < 3 || (r0 < 6 && (r1 & 0x80) == 0)) {
        return ((r1 & 0x3c) >> 2 << 14) + HW_DB_BG_VRAM;
    }
    return 0;
}

void G2_SetBGAffine(u32 *reg, MtxFx22 *mtx, u32 param3, u32 param4, u32 param5, u32 param6) {}

void _G2_SetBlend(u32 *reg, u32 srcPlane, u32 dstPlane, u32 srcAlpha, u32 dstAlpha) {
    u32 plane = srcPlane | 0x40 | (dstPlane << 8);
    u32 alpha = srcAlpha | (dstAlpha << 8);
    *reg      = plane | (alpha << 16);
}

void GX_LoadBGPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, HW_PLTT + offset, size);
    } else {
        MI_CpuCopy16(ptr, HW_PLTT + offset, size);
    }
}

void GXS_LoadBGPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, HW_DB_PLTT + offset, size);
    } else {
        MI_CpuCopy16(ptr, HW_DB_PLTT + offset, size);
    }
}

void GX_LoadOBJPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, HW_PLTT + 0x200 + offset, size);
    } else {
        MI_CpuCopy16(ptr, HW_PLTT + 0x200 + offset, size);
    }
}

void GXS_LoadOBJPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, HW_DB_PLTT + 0x200 + offset, size);
    } else {
        MI_CpuCopy16(ptr, HW_DB_PLTT + 0x200 + offset, size);
    }
}

void GX_LoadOAM(GXOamAttr *oam, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, oam, HW_OAM + offset, size);
    } else {
        MI_CpuCopy32(oam, HW_OAM + offset, size);
    }
}

void GXS_LoadOAM(GXOamAttr *oam, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, oam, HW_DB_OAM + offset, size);
    } else {
        MI_CpuCopy32(oam, HW_DB_OAM + offset, size);
    }
}

void GX_LoadOBJ(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, HW_OBJ_VRAM + offset, size);
    } else {
        MI_CpuCopy32(ptr, HW_OBJ_VRAM + offset, size);
    }
}

void GXS_LoadOBJ(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, HW_DB_OBJ_VRAM + offset, size);
    } else {
        MI_CpuCopy32(ptr, HW_DB_OBJ_VRAM + offset, size);
    }
}

void GX_LoadBG0Scr(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069b1c();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GXS_LoadBG0Scr(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069b50();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GX_LoadBG1Scr(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069b70();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GXS_LoadBG1Scr(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069ba4();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GX_LoadBG2Bmp(void *ptr, u32 offset, u32 size) {
    void *vram = G2_GetBG2ScrPtr();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GXS_LoadBG2Bmp(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069c48();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GX_LoadBG3Bmp(void *ptr, u32 offset, u32 size) {
    void *vram = G2_GetBG3ScrPtr();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GXS_LoadBG3Bmp(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069d40();
    if (data_020a7088.unk_04 != -1 && size > 28) {
        MI_DmaCopy16(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy16(ptr, vram + offset, size);
    }
}

void GX_LoadBG0Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069db4();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GXS_LoadBG0Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069de8();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GX_LoadBG1Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069e08();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GXS_LoadBG1Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069e3c();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GX_LoadBG2Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069e5c();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GXS_LoadBG2Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069eac();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GX_LoadBG3Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2_func_02069eec();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GXS_LoadBG3Char(void *ptr, u32 offset, u32 size) {
    void *vram = G2S_func_02069f44();
    if (data_020a7088.unk_04 != -1 && size > 48) {
        MI_DmaCopy32(data_020a7088.unk_04, ptr, vram + offset, size);
    } else {
        MI_CpuCopy32(ptr, vram + offset, size);
    }
}

void GX_BeginLoadBGExtPltt(void) {
    data_0216a0fc.unk_14 = GX_ResetBankForBGExtPltt();
    switch (data_0216a0fc.unk_14) {
        case 0x0:
            break;
        case 0x10:
            data_0216a0fc.unk_10 = ((void *) 0x06880000);
            data_0216a0fc.unk_0c = 0;
            break;
        case 0x40:
            data_0216a0fc.unk_10 = ((void *) 0x06894000);
            data_0216a0fc.unk_0c = 0x4000;
            break;
        case 0x20:
        case 0x60:
            data_0216a0fc.unk_10 = ((void *) 0x06890000);
            data_0216a0fc.unk_0c = 0;
            break;
    }
}

void GX_LoadBGExtPltt(void *ptr, u32 offset, u32 size) {
    void *vram = (data_0216a0fc.unk_10 + offset) - data_0216a0fc.unk_0c;
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d87c(data_020a7088.unk_04, ptr, vram, size, 0, 0);
    } else {
        MI_CpuCopy32(ptr, vram, size);
    }
}

void GX_EndLoadBGExtPltt(void) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d934(data_020a7088.unk_04);
    }
    GX_func_0206921c(data_0216a0fc.unk_14);
    data_0216a0fc.unk_14 = 0;
    data_0216a0fc.unk_10 = 0;
    data_0216a0fc.unk_0c = 0;
}

void GX_BeginLoadOBJExtPltt(void) {
    data_0216a0fc.unk_08 = GX_ResetBankForOBJExtPltt();
    switch (data_0216a0fc.unk_08) {
        case 0x0:
            break;
        case 0x40:
            data_0216a0fc.unk_04 = ((void *) 0x06894000);
            break;
        case 0x20:
            data_0216a0fc.unk_04 = ((void *) 0x06890000);
            break;
    }
}

void GX_LoadOBJExtPltt(void *ptr, u32 offset, u32 size) {
    void *vram = data_0216a0fc.unk_04 + offset;
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d87c(data_020a7088.unk_04, ptr, vram, size, 0, 0);
    } else {
        MI_CpuCopy32(ptr, vram, size);
    }
}

void GX_EndLoadOBJExtPltt(void) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d934(data_020a7088.unk_04);
    }
    GX_func_02069448(data_0216a0fc.unk_08);
    data_0216a0fc.unk_08 = 0;
    data_0216a0fc.unk_04 = 0;
}

void GXS_BeginLoadBGExtPltt(void) {
    data_0216a0fc.unk_00 = GX_ResetBankForSubBGExtPltt();
}

void GXS_LoadBGExtPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d87c(data_020a7088.unk_04, ptr, ((void *) 0x06898000) + offset, size, 0, 0);
    } else {
        MI_CpuCopy32(ptr, ((void *) 0x06898000) + offset, size);
    }
}

void GXS_EndLoadBGExtPltt(void) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d934(data_020a7088.unk_04);
    }
    GXS_func_02069704(data_0216a0fc.unk_00);
    data_0216a0fc.unk_00 = 0;
}

void GXS_BeginLoadOBJExtPltt(void) {
    data_0216a0fc.unk_18 = GX_ResetBankForSubOBJExtPltt();
}

void GXS_LoadOBJExtPltt(void *ptr, u32 offset, u32 size) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d87c(data_020a7088.unk_04, ptr, ((void *) 0x068a0000) + offset, size, 0, 0);
    } else {
        MI_CpuCopy32(ptr, ((void *) 0x068a0000) + offset, size);
    }
}

void GXS_EndLoadOBJExtPltt(void) {
    if (data_020a7088.unk_04 != -1) {
        MI_func_0206d934(data_020a7088.unk_04);
    }
    GXS_func_02069830(data_0216a0fc.unk_18);
    data_0216a0fc.unk_18 = 0;
}
