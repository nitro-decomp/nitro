#include "nitro/snd.h"
#include "nitro/dc.h"
#include "nitro/os.h"

typedef struct SND_UnkStruct1 {
    /* 00 */ SNDCommand *unk_00;
    /* 04 */ s32 unk_04;
    /* 08 */ SNDCommand *unk_08;
    /* 0c */ SNDCommand *unk_0c;
    /* 10 */ SNDCommand *unk_10;
    /* 14 */ s32 unk_14;
    /* 18 */ s32 unk_18;
    /* 1c */ s32 unk_1c;
    /* 20 */ s32 unk_20;
    /* 24 */
} SND_UnkStruct1;

typedef struct SNDAlarm {
    /* 00 */ SNDAlarmCallback callback;
    /* 04 */ void *arg; // user data
    /* 08 */ s8 unk_08;
    /* 0c */
} SNDAlarm;

typedef struct SND_UnkStruct2 {
    /* 00 */ s16 unk_00[0x10];
    /* 20 */ s32 unk_20;
    /* 24 */
} SND_UnkStruct2;

typedef struct SND_UnkStruct3 {
    /* 000 */ s32 unk_00; // number of commands executed?
    /* 004 */ s32 unk_04;
    /* 008 */ s16 unk_08;
    /* 00a */ s16 unk_0a;
    /* 00c */ s8 unk_0c[0x20 - 0x0c];
    /* 020 */ SND_UnkStruct2 unk_20[0x10];
    /* 260 */ s16 unk_260[0x10];
    /* 280 */
} ATTRIBUTE_ALIGN(32) SND_UnkStruct3;

static void SND_func_0015(SNDCommandType type, u32 target, u32 param0, u32 param1, u32 param2);
static void SND_func_0018(void);
static SNDCommand *SND_func_0019(s32 arg0);
static void SND_func_0020(SNDCommand *command);
static s32 SND_func_0024(void);
static s32 SND_func_0025(void);
static s32 SND_func_0026(void);
static void SND_func_0027(u32 arg0, u32 arg1, u32 arg2);
static void SND_func_0028(void);
static void SND_func_0029(void);
static SNDCommand *SND_func_0030(void);
static BOOL SND_func_0031(void);
static s32 SND_func_0034(u32 num, SNDAlarmCallback callback, void *arg);
static void SND_func_0035(u32 num);
static void SND_func_0038(SND_UnkStruct3 *arg0);
static void SND_func_0054(void);
static s32 SND_func_0055(void);

static SND_UnkStruct3 *data_0213a440; // pointer to data_02138960
static SNDAlarm sSndAlarms[8];
static SNDCommand sSndCommands[0x100];
static SND_UnkStruct3 data_02138960;
static SNDCommand *data_02138928[9];
static SND_UnkStruct1 data_02138904;
static OSMutex sSndMutex;
static BOOL sSndInitialized;

void SND_StartTimer(u32 channel, u32 arg1, u32 num, u32 arg3) {
    SND_func_0015(SNDCommandType_StartTimer, channel, arg1, num, arg3);
}

void SND_SetupAlarm(u32 num, u32 arg1, u32 arg2, SNDAlarmCallback callback, void *arg) {
    SND_func_0015(SNDCommandType_SetupAlarm, num, arg1, arg2, SND_func_0034(num, callback, arg));
}

void SND_LockChannel(u32 channel, u32 arg1) {
    SND_func_0015(SNDCommandType_LockChannel, channel, arg1, 0, 0);
}

void SND_SetChannelVolume(u32 channel, u32 volume, u32 datashift) {
    SND_func_0015(SNDCommandType_SetChannelVolume, channel, volume, datashift, 0);
}

void SND_SetChannelPan(u32 channel, u32 pan) {
    SND_func_0015(SNDCommandType_SetChannelPan, channel, pan, 0, 0);
}

void SND_SetupChannelPcm(u32 channel, u32 format, void *buf, u32 loop, u32 arg4, u32 numSamples, u32 volume,
                         u32 datashift, u32 arg8, u32 arg9) {
    SND_func_0015(SNDCommandType_SetupChannelPcm, channel | (arg8 << 0x10), (u32) buf,
                  numSamples | ((volume << 0x18) | (datashift << 0x16)),
                  arg4 | ((loop << 0x1A) | (format << 0x18) | (arg9 << 0x10)));
}

static void SND_func_0015(SNDCommandType type, u32 target, u32 param0, u32 param1, u32 param2) {
    SNDCommand *command;

    command = SND_func_0019(1);
    if (command == NULL) {
        return;
    }
    command->type   = type;
    command->target = target;
    command->param0 = param0;
    command->param1 = param1;
    command->param2 = param2;
    SND_func_0020(command);
}

void SND_Init(void) {
    if (sSndInitialized) {
        return;
    }
    sSndInitialized = true;
    OS_InitMutex(&sSndMutex);
    SND_func_0018();
    SND_func_0054();
}

static void SND_func_0018(void) {
    SNDCommand *command;
    s32 i;

    SND_func_0028();
    data_02138904.unk_00 = &sSndCommands[0];
    i                    = 0;
    while (i < ARRAY_LEN(sSndCommands) - 1) {
        i++;
        sSndCommands[i].next = &sSndCommands[i];
    }
    sSndCommands[ARRAY_LEN(sSndCommands) - 1].next = NULL;

    data_02138904.unk_10 = &sSndCommands[ARRAY_LEN(sSndCommands) - 1];
    data_02138904.unk_08 = 0;
    data_02138904.unk_0c = 0;
    data_02138904.unk_1c = 0;
    data_02138904.unk_14 = 0;
    data_02138904.unk_18 = 0;
    data_02138904.unk_20 = 1;
    data_02138904.unk_04 = 0;

    data_0213a440 = &data_02138960;
    SND_func_0038(data_0213a440);
    command = SND_func_0019(1);
    if (command == NULL) {
        return;
    }
    command->type   = 0x1D;
    command->target = (u32) data_0213a440;
    SND_func_0020(command);
    SND_FlushCommand(1);
}

SNDCommand *SND_RecvCommandReply(u32 arg0) {
    OSIntrMode irq;
    s32 temp_r0;
    SNDCommand *temp_r5;
    SNDCommand *var_r1;

    irq = OS_DisableInterrupts();
    if (arg0 & 1) {
        while (data_02138904.unk_04 == SND_func_0055()) {
            OS_RestoreInterrupts(irq);
            _OS_SpinWait(0x32);
            irq = OS_DisableInterrupts();
        }
    } else if (data_02138904.unk_04 == SND_func_0055()) {
        OS_RestoreInterrupts(irq);
        return NULL;
    }
    temp_r5 = data_02138928[data_02138904.unk_14];
    if (++data_02138904.unk_14 > 8) {
        data_02138904.unk_14 = 0;
    }
    var_r1 = temp_r5;
    while (var_r1->next != NULL) {
        var_r1 = var_r1->next;
    }
    if (data_02138904.unk_10 != NULL) {
        data_02138904.unk_10->next = temp_r5;
    } else {
        data_02138904.unk_00 = temp_r5;
    }
    data_02138904.unk_10 = var_r1;
    data_02138904.unk_1c--;
    data_02138904.unk_04++;
    OS_RestoreInterrupts(irq);
    return temp_r5;
}

static SNDCommand *SND_func_0019(s32 arg0) {
    SNDCommand *temp_r0;
    SNDCommand *temp_r0_2;
    SNDCommand *temp_r0_3;

    if (SND_func_0031() == 0) {
        return NULL;
    }
    temp_r0_3 = SND_func_0030();
    if (temp_r0_3 != NULL) {
        return temp_r0_3;
    }
    if (!(arg0 & 1)) {
        return NULL;
    }
    if (SND_func_0026() > 0) {
        while (SND_RecvCommandReply(0) != NULL) {
        }
        temp_r0_2 = SND_func_0030();
        if (temp_r0_2 != NULL) {
            return temp_r0_2;
        }
    } else {
        SND_FlushCommand(1);
    }
    SND_func_0029();
    do {
        SND_RecvCommandReply(1);
        temp_r0 = SND_func_0030();
    } while (temp_r0 == NULL);
    return temp_r0;
}

static void SND_func_0020(SNDCommand *command) {
    OSIntrMode irq = OS_DisableInterrupts();
    SND_UnkStruct1 *var_r1;
    SNDCommand *var_r2;

    var_r1 = &data_02138904;
    var_r2 = var_r1->unk_0c;
    if (var_r2 == NULL) {
        var_r1->unk_08 = command;
    } else {
        var_r2->next = command;
    }
    var_r1->unk_0c = command;
    command->next  = NULL;
    OS_RestoreInterrupts(irq);
}

BOOL SND_FlushCommand(u32 arg0) {
    s32 temp_r0;
    OSIntrMode irq;

    irq = OS_DisableInterrupts();
    if (data_02138904.unk_08 == NULL) {
        OS_RestoreInterrupts(irq);
        return true;
    }
    if (data_02138904.unk_1c >= 8) {
        if (!(arg0 & 1)) {
            OS_RestoreInterrupts(irq);
            return false;
        }
        do {
            SND_RecvCommandReply(1);
        } while (data_02138904.unk_1c >= 8);
        if (data_02138904.unk_08 == NULL) {
            OS_RestoreInterrupts(irq);
            return true;
        }
    }
    DC_FlushRange(&sSndCommands, 0x1800);
    if (OS_func_0171(7, data_02138904.unk_08, 0) < 0) {
        if (!(arg0 & 1)) {
            OS_RestoreInterrupts(irq);
            return false;
        }
        while (data_02138904.unk_1c >= 8 || OS_func_0171(7, data_02138904.unk_08, 0) < 0) {
            OS_RestoreInterrupts(irq);
            SND_RecvCommandReply(0);
            irq = OS_DisableInterrupts();
            DC_FlushRange(&sSndCommands, 0x1800);
            if (data_02138904.unk_08 == NULL) {
                OS_RestoreInterrupts(irq);
                return true;
            }
        }
    }
    data_02138928[data_02138904.unk_18] = data_02138904.unk_08;
    if (++data_02138904.unk_18 > 8) {
        data_02138904.unk_18 = 0;
    }
    data_02138904.unk_08 = 0;
    data_02138904.unk_0c = 0;
    data_02138904.unk_1c++;
    data_02138904.unk_20++;
    OS_RestoreInterrupts(irq);
    if (arg0 & 2) {
        SND_func_0029();
    }
    return true;
}

static s32 SND_func_0024(void) {
    OSIntrMode irq      = OS_DisableInterrupts();
    s32 count           = 0;
    SNDCommand *command = data_02138904.unk_00;
    while (command != NULL) {
        command = command->next;
        count += 1;
    }
    OS_RestoreInterrupts(irq);
    return count;
}

static s32 SND_func_0025(void) {
    OSIntrMode irq      = OS_DisableInterrupts();
    s32 count           = 0;
    SNDCommand *command = data_02138904.unk_08;
    while (command != NULL) {
        command = command->next;
        count += 1;
    }
    OS_RestoreInterrupts(irq);
    return count;
}

static s32 SND_func_0026(void) {
    s32 temp_r4;

    temp_r4 = SND_func_0024();
    return (0x100 - temp_r4) - SND_func_0025();
}

static void SND_func_0027(u32 arg0, u32 arg1, u32 arg2) {
    OSIntrMode irq;

    irq = OS_DisableInterrupts();
    SND_func_0035(arg1);
    OS_RestoreInterrupts(irq);
}

static void SND_func_0028(void) {
    OS_func_0169(7, SND_func_0027);
    if (SND_func_0031() == 0) {
        return;
    }
    if (OS_func_0170(7, 1) != 0) {
        return;
    }
    do {
        _OS_SpinWait(0x32);
    } while (OS_func_0170(7, 1) == 0);
}

static void SND_func_0029(void) {
    do {

    } while (OS_func_0171(7, 0, 0) < 0);
}

static SNDCommand *SND_func_0030(void) {
    SNDCommand *temp_r2;

    OSIntrMode irq      = OS_DisableInterrupts();
    SNDCommand *temp_r4 = data_02138904.unk_00;
    if (temp_r4 == NULL) {
        OS_RestoreInterrupts(irq);
        return NULL;
    }
    temp_r2              = temp_r4->next;
    data_02138904.unk_00 = temp_r2;
    if (temp_r2 == NULL) {
        data_02138904.unk_10 = NULL;
    }
    OS_RestoreInterrupts(irq);
    return temp_r4;
}

static BOOL SND_func_0031(void) {
    s32 temp_r4;
    BOOL var_r0;
    OSIntrMode irq;

    if (OS_func_0174() == 0) {
        return true;
    }
    irq          = OS_DisableInterrupts();
    REG_04FFF200 = 0x10;
    temp_r4      = REG_04FFF200;
    OS_RestoreInterrupts(irq);
    var_r0 = true;
    if (temp_r4 == 0) {
        var_r0 = false;
    }
    return var_r0;
}

static void SND_func_0054(void) {
    s32 i;
    for (i = 0; i < ARRAY_LEN(sSndAlarms); ++i) {
        sSndAlarms[i].callback = NULL;
        sSndAlarms[i].arg      = NULL;
        sSndAlarms[i].unk_08   = 0;
    }
}

static s32 SND_func_0034(u32 num, SNDAlarmCallback callback, void *arg) {
    SNDAlarm *alarm = &sSndAlarms[num];
    alarm->callback = callback;
    alarm->arg      = arg;
    alarm->unk_08++;
    return alarm->unk_08;
}

static void SND_func_0035(u32 num) {
    SNDAlarmCallback callback;
    SNDAlarm *alarm;

    alarm = &sSndAlarms[(u8) num];
    if ((u8) ((s32) num >> 8) != alarm->unk_08) {
        return;
    }
    callback = alarm->callback;
    if (callback == NULL) {
        return;
    }
    callback(alarm->arg);
}

static s32 SND_func_0055(void) {
    DC_InvalidateRange(data_0213a440, 4);
    return data_0213a440->unk_00;
}

static void SND_func_0038(SND_UnkStruct3 *arg0) {
    SND_UnkStruct2 *temp_r5;
    s32 i;
    s32 j;

    arg0->unk_04 = 0;
    arg0->unk_08 = 0;
    arg0->unk_0a = 0;
    arg0->unk_00 = 0;
    for (i = 0; i < ARRAY_LEN(arg0->unk_20); ++i) {
        arg0->unk_20[i].unk_20 = 0;
        for (j = 0; j < ARRAY_LEN(arg0->unk_20[i].unk_00); ++j) {
            arg0->unk_20[i].unk_00[j] = -1;
        }
    }
    for (i = 0; i < ARRAY_LEN(arg0->unk_260); ++i) {
        arg0->unk_260[i] = -1;
    }
    DC_FlushRange(arg0, sizeof(*arg0));
}
