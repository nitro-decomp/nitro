#include "nitro/rtc.h"
#include "nitro/os.h"

typedef struct RTC_UnkStruct2 {
    /* 00 */ s32 unk_00;
    /* 04 */ s32 unk_04;
    /* 08 */ s32 unk_08;
    /* 0c */ s32 unk_0c;
    /* 10 */
} RTC_UnkStruct2;

typedef struct RTC_UnkStruct1 {
    /* 00 */ u16 unk_00;
    /* 04 */ s32 unk_04;
    /* 08 */ void (*unk_08)(s32, s32);
    /* 0c */ union {
        void *unk_0c;
        RTCDate *date;
        RTCTime *time;
        RTC_UnkStruct2 *unk_0c_2;
    };
    /* 10 */ RTCTime *unk_10;
    /* 14 */ s32 unk_14;
    /* 18 */ s32 unk_18;
    /* 1c */ s32 unk_1c;
    /* 20 */ void (*unk_20)(void);
    /* 24 */ s32 unk_24;
    /* 28 */
} RTC_UnkStruct1;

static s32 RTC_func_0001(RTCDate *date, void (*arg1)(s32, s32), s32 arg2);
static s32 RTC_func_0002(RTCTime *time, void (*arg1)(s32, s32), s32 arg2);
static void RTC_func_0003(u32 arg0, u32 arg1, u32 arg2);
static s32 RTC_func_0004(u32 arg0);
static void RTC_func_0005(s32 arg0, s32 arg1);
static void RTC_func_0006(void);
static s32 RTC_func_0007(void);
static s32 RTC_func_0008(void);
static s32 RTC_func_0009(void);
static s32 RTC_func_0010(u32 arg0);
static s32 RTC_func_0011(const RTCDate *date);
static s32 RTC_func_0012(const RTCTime *time);
static s32 RTC_func_0013(RTCDate *date);

static u32 data_02080fb4[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static RTC_UnkStruct1 data_021388c0;
static vs32 data_021388c4;

void RTC_Init(void) {
    if (data_021388c0.unk_00 != 0) {
        return;
    }
    data_021388c0.unk_00 = 1;
    data_021388c0.unk_04 = 0;
    data_021388c0.unk_08 = 0;
    data_021388c0.unk_20 = 0;
    data_021388c0.unk_0c = NULL;
    data_021388c0.unk_10 = 0;
    OS_func_0167();
    while (OS_func_0170(5, 1) == 0) {
    }
    OS_func_0169(5, RTC_func_0003);
}

static s32 RTC_func_0001(RTCDate *date, void (*arg1)(s32, s32), s32 arg2) {
    OSIntrMode irq = OS_DisableInterrupts();
    if (data_021388c0.unk_04 != 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    data_021388c0.unk_04 = 1;
    OS_RestoreInterrupts(irq);
    data_021388c0.unk_18 = 0;
    data_021388c0.unk_1c = 0;
    data_021388c0.date   = date;
    data_021388c0.unk_08 = arg1;
    data_021388c0.unk_14 = arg2;
    if (RTC_func_0007() != 0) {
        return 0;
    }
    data_021388c0.unk_04 = 0;
    return 3;
}

s32 RTC_GetDate(RTCDate *date) {
    s32 temp_r0;

    temp_r0              = RTC_func_0001(date, RTC_func_0005, 0);
    data_021388c0.unk_24 = temp_r0;
    if (temp_r0 == 0) {
        RTC_func_0006();
    }
    return data_021388c0.unk_24;
}

s32 RTC_func_0002(RTCTime *time, void (*arg1)(s32, s32), s32 arg2) {
    OSIntrMode irq = OS_DisableInterrupts();
    if (data_021388c0.unk_04 != 0) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    data_021388c0.unk_04 = 1;
    OS_RestoreInterrupts(irq);
    data_021388c0.unk_18 = 1;
    data_021388c0.unk_1c = 0;
    data_021388c0.time   = time;
    data_021388c0.unk_08 = arg1;
    data_021388c0.unk_14 = arg2;
    if (RTC_func_0008() != 0) {
        return 0;
    }
    data_021388c0.unk_04 = 0;
    return 3;
}

s32 RTC_GetTime(RTCTime *time) {
    s32 temp_r0;

    temp_r0              = RTC_func_0002(time, RTC_func_0005, 0);
    data_021388c0.unk_24 = temp_r0;
    if (temp_r0 == 0) {
        RTC_func_0006();
    }
    return data_021388c0.unk_24;
}

void RTC_func_0003(u32 arg0, u32 arg1, u32 arg2) {
    void (*temp_r2)(s32, s32);
    void (*temp_r2_2)(s32, s32);
    s32 var_r5;
    s32 var_r0;
    u16 var_r1;
    RTCDate *temp_r8;
    RTCDate *temp_r8_2;
    RTC_UnkStruct2 *temp_r8_3;
    RTCTime *var_r8;
    u32 temp_r1;
    u32 temp_r1_2;

    if (arg2 != 0) {
        if (data_021388c0.unk_1c != 0) {
            data_021388c0.unk_1c = 0;
        }
        if (data_021388c0.unk_04 != 0) {
            data_021388c0.unk_04 = 0;
        }
        temp_r2 = data_021388c0.unk_08;
        if (temp_r2 == NULL) {
            return;
        }
        data_021388c0.unk_08 = NULL;
        temp_r2(6, data_021388c0.unk_14);
        return;
    }
    if ((u8) ((u32) (arg1 & 0x7F00) >> 8) == 0x30) {
        if (data_021388c0.unk_20 == NULL) {
            return;
        }
        data_021388c0.unk_20();
        return;
    }
    if (arg1 == 0) {
        var_r5 = 0;
        switch (data_021388c0.unk_18) {              /* switch 1 */
            default:                                    /* switch 1 */
                data_021388c0.unk_1c = 0;
                goto block_69;
            case 0:                                     /* switch 1 */
                temp_r8        = data_021388c0.date;
                temp_r8->year  = RTC_func_0004((u8) REG_027FFDE8);
                temp_r8->month = RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0x13) >> 0x1B));
                temp_r8->day   = RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0xA) >> 0x1A));
                temp_r8->unk   = RTC_func_0013(temp_r8);
                break;
            case 1:                                     /* switch 1 */
                var_r8         = data_021388c0.time;
                var_r8->hour   = (u32) RTC_func_0004((u8) ((u32) (REG_027FFDEC << 0x1A) >> 0x1A));
                var_r8->minute = RTC_func_0004((u8) ((u32) (REG_027FFDEC << 0x11) >> 0x19));
                var_r0         = REG_027FFDEC;
            block_34:
                var_r8->second = RTC_func_0004((u8) ((u32) (var_r0 << 9) >> 0x19));
                break;
            case 2:                                     /* switch 1 */
                temp_r8_2        = data_021388c0.unk_0c;
                temp_r8_2->year  = (u32) RTC_func_0004((u8) REG_027FFDE8);
                temp_r8_2->month = RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0x13) >> 0x1B));
                temp_r8_2->day   = RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0xA) >> 0x1A));
                temp_r8_2->unk   = RTC_func_0013(temp_r8_2);
                var_r8           = data_021388c0.unk_10;
                var_r8->hour     = (u32) RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0x1A) >> 0x1A));
                var_r8->minute   = RTC_func_0004((u8) ((u32) (REG_027FFDE8 << 0x11) >> 0x19));
                var_r0           = REG_027FFDE8;
                goto block_34;
            case 6:                                     /* switch 1 */
                if (((u32) (REG_027FFDEA << 0x1C) >> 0x1C) == 4) {
                    *(s32 *) data_021388c0.unk_0c = 1;
                } else {
                    *(s32 *) data_021388c0.unk_0c = 0;
                }
                break;
            case 7:                                     /* switch 1 */
                if (((u32) (REG_027FFDEA << 0x19) >> 0x1F) != 0) {
                    *(s32 *) data_021388c0.unk_0c = 1;
                } else {
                    *(s32 *) data_021388c0.unk_0c = 0;
                }
                break;
            case 8:                                     /* switch 1 */
                temp_r8_3         = data_021388c0.unk_0c_2;
                temp_r8_3->unk_00 = (u32) (REG_027FFDEC << 0x1D) >> 0x1D;
                temp_r8_3->unk_04 = RTC_func_0004((u8) ((u32) (REG_027FFDEC << 0x12) >> 0x1A));
                temp_r8_3->unk_08 = RTC_func_0004((u8) ((u32) (REG_027FFDEC << 9) >> 0x19));
                temp_r8_3->unk_0c = 0;
                if (((u32) (REG_027FFDEC << 0x18) >> 0x1F) != 0) {
                    temp_r8_3->unk_0c = (s32) (temp_r8_3->unk_0c + 1);
                }
                if (((u32) (REG_027FFDEC << 0x10) >> 0x1F) != 0) {
                    temp_r8_3->unk_0c = (s32) (temp_r8_3->unk_0c + 2);
                }
                if (((u32) (REG_027FFDEC << 8) >> 0x1F) != 0) {
                    temp_r8_3->unk_0c = (s32) (temp_r8_3->unk_0c + 4);
                }
                break;
            case 9:                                     /* switch 1 */
                if (data_021388c0.unk_1c == 0) {
                    temp_r1 = REG_027FFDEA << 0x1C;
                    if (*(s32 *) data_021388c0.unk_0c == 1) {
                        if ((temp_r1 >> 0x1C) != 4) {
                            data_021388c0.unk_1c = (s32) (data_021388c0.unk_1c + 1);
                            var_r1               = (REG_027FFDEA & ~0xF) | 4;
                            goto block_64;
                        }
                    } else if ((temp_r1 >> 0x1C) != 0) {
                        data_021388c0.unk_1c = (s32) (data_021388c0.unk_1c + 1);
                        var_r1               = REG_027FFDEA & ~0xF;
                    block_64:
                        REG_027FFDEA = var_r1;
                        if (RTC_func_0009() == 0) {
                            data_021388c0.unk_1c = 0;
                            var_r5               = 3;
                        }
                    }
                } else {
                block_57:
                    data_021388c0.unk_1c = 0;
                }
                break;
            case 10:                                    /* switch 1 */
                if (data_021388c0.unk_1c == 0) {
                    temp_r1_2 = REG_027FFDEA << 0x19;
                    if (*(s32 *) data_021388c0.unk_0c == 1) {
                        if ((temp_r1_2 >> 0x1F) == 0) {
                            data_021388c0.unk_1c = (s32) (data_021388c0.unk_1c + 1);
                            var_r1               = REG_027FFDEA | 0x40;
                            goto block_64;
                        }
                    } else if ((temp_r1_2 >> 0x1F) != 0) {
                        data_021388c0.unk_1c = (s32) (data_021388c0.unk_1c + 1);
                        var_r1               = REG_027FFDEA & ~0x40;
                        goto block_64;
                    }
                } else {
                    goto block_57;
                }
                break;
        }
    } else {
        data_021388c0.unk_1c = 0;
        switch ((u32) arg1) {                       /* switch 2; irregular */
            case 5:                                     /* switch 2 */
            block_69:
                var_r5 = 4;
                break;
            case 1:                                     /* switch 2 */
                goto block_69;
            case 2:                                     /* switch 2 */
                var_r5 = 5;
                break;
            case 3:                                     /* switch 2 */
                var_r5 = 1;
                break;
            default:                                    /* switch 2 */
                var_r5 = 6;
                break;
        }
    }
    if (data_021388c0.unk_1c != 0) {
        return;
    }
    if (data_021388c0.unk_04 != 0) {
        data_021388c0.unk_04 = 0;
    }
    temp_r2_2 = data_021388c0.unk_08;
    if (temp_r2_2 == NULL) {
        return;
    }
    data_021388c0.unk_08 = NULL;
    temp_r2_2(var_r5, data_021388c0.unk_14);
}

s32 RTC_func_0004(u32 arg0) {
    s32 var_ip;
    s32 var_lr;
    s32 var_r2;
    s32 var_r4;

    var_ip = 0;
    var_r2 = 0;
loop_1:
    if ((u32) ((arg0 >> (var_r2 * 4)) & 0xF) >= 0xA) {
        return 0;
    }
    var_r2 += 1;
    if (var_r2 >= 8) {
        var_r4 = 0;
        var_lr = 1;
        do {
            var_ip += var_lr * ((arg0 >> (var_r4 * 4)) & 0xF);
            var_r4 += 1;
            var_lr *= 0xA;
        } while (var_r4 < 8);
        return var_ip;
    }
    goto loop_1;
}

void RTC_func_0005(s32 arg0, s32 arg1) {
    data_021388c0.unk_24 = arg0;
}

void RTC_func_0006(void) {
    while (data_021388c4 == 1) {
    }
}

s32 RTC_func_0007(void) {
    return RTC_func_0010(0x11);
}

s32 RTC_func_0008(void) {
    return RTC_func_0010(0x12);
}

s32 RTC_func_0009(void) {
    return RTC_func_0010(0x27);
}

s32 RTC_func_0010(u32 arg0) {
    s32 var_r4;

    var_r4 = 0;
    if (OS_func_0171(5, (arg0 << 8) & 0x7F00, 0) >= 0) {
        var_r4 = 1;
    }
    return var_r4;
}

static s32 RTC_func_0011(const RTCDate *date) {
    s32 var_r2;
    u32 temp_r1;
    u32 temp_r2;
    u32 temp_r3;

    temp_r3 = date->year;
    if ((temp_r3 >= 0x64U) || (temp_r2 = date->month, (temp_r2 < 1U)) || (temp_r2 > 0xCU) ||
        (temp_r1 = date->day, (temp_r1 < 1U)) || (temp_r1 > 0x1FU) || ((s32) date->unk >= 7) || (temp_r2 < 1U) ||
        (temp_r2 > 0xCU)) {
        return -1;
    }
    var_r2 = (temp_r1 - 1) + data_02080fb4[temp_r2 - 1];
    if ((temp_r2 >= 3U) && !(temp_r3 & 3)) {
        var_r2 += 1;
    }
    return (temp_r3 * 0x16D) + var_r2 + ((u32) (temp_r3 + 3) >> 2);
}

static s32 RTC_func_0012(const RTCTime *time) {
    return (((time->hour * 60) + time->minute) * 60) + time->second;
}

u64 RTC_ConvertDateTimeToSecond(const RTCDate *date, const RTCTime *time) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r5;

    temp_r0 = RTC_func_0011(date);
    var_r5  = -1;
    if (temp_r0 == -1) {
        return -1;
    }
    temp_r0_2 = RTC_func_0012(time);
    if (temp_r0_2 == -1) {

    } else {
        var_r5 = temp_r0_2 + (temp_r0 * 0x15180);
    }
    return var_r5;
}

s32 RTC_func_0013(RTCDate *date) {
    s32 temp_r0;
    s32 temp_r2;
    s32 temp_r3;
    s32 var_r1;
    u32 temp_r4;
    u32 temp_r5;
    u32 var_ip;

    var_r1 = date->month - 2;
    var_ip = date->year + 0x7D0;
    if (var_r1 < 1) {
        var_ip -= 1;
        var_r1 += 0xC;
    }
    temp_r5 = var_ip >> 0x1F;
    temp_r3 = temp_r5 + (var_ip / 100);
    temp_r2 = var_ip - (0x64 * (temp_r5 + (var_ip / 100)));
    temp_r0 = var_r1 * 0x1A;
    temp_r4 = temp_r2 + (date->day + (((u32) (temp_r0 - 2) >> 0x1F) + ((temp_r0 - 2) / 10))) +
              ((s32) (temp_r2 + ((u32) (temp_r2 >> 1) >> 0x1E)) >> 2) +
              ((s32) (temp_r3 + ((u32) (temp_r3 >> 1) >> 0x1E)) >> 2) + (temp_r3 * 5);
    return temp_r4 - (7 * ((temp_r4 >> 0x1F) + ((s32) (temp_r4 + temp_r4 * 4 / 7) >> 2)));
}
