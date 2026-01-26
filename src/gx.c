#include <nitro/gx.h>
#include <nitro/mi.h>
#include <nitro/os.h>

static GX_func_02068d24(void);

typedef struct GX_UnkStruct1 {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */
} GX_UnkStruct1;

static GX_UnkStruct1 data_0216a0dc;

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