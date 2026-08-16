#include "nitro/os.h"
#include "nitro/os/mutex.h"

static void OS_WakeupThread(OSMutex *mutex);
static void OS_func_0067(OSThread *param1, OSMutex *mutex);
static void OS_func_0068(OSThread *param1, OSMutex *mutex);
static BOOL OS_func_0124(OSMutex *mutex);
static void OS_func_0125(OSMutex *mutex, u32 param2);

void OS_InitMutex(OSMutex *mutex) {
    u32 temp_r1;

    mutex->unk_00.tail = NULL;
    mutex->unk_00.head = NULL;
    mutex->unk_08      = 0;
    temp_r1            = mutex->unk_0c & 0xFF000000;
    mutex->unk_0c      = temp_r1 & ~0xFF000000;
}

extern OS_Mutex_UnkStruct1 data_021384c0;

extern void OS_LockMutex(OSMutex *mutex) {
    OSIntrMode irq;
    OSThread *temp_r6;

    irq     = OS_DisableInterrupts();
    temp_r6 = data_021384c0.unk_04;
    while (true) {
        if (OS_func_0124(mutex) != 0) {
            break;
        }
        temp_r6->unk_84 = mutex;
        OS_SleepThread(mutex);
        temp_r6->unk_84 = NULL;
    }
    OS_RestoreInterrupts(irq);
}

void OS_UnlockMutex(OSMutex *mutex) {
    OS_func_0125(mutex, 0x10000000);
}

void OSi_UnlockAllMutex(OSThread *param1) {
    OSMutex *mutex;
    u32 temp_r1;

    while (param1->unk_88.unk_00 != NULL) {
        mutex         = OS_func_0039(&param1->unk_88);
        temp_r1       = mutex->unk_0c & 0xFF000000;
        mutex->unk_08 = 0;
        mutex->unk_0c = (s32) (temp_r1 & ~0xFF000000);
        OS_WakeupThread(mutex);
    }
}

static BOOL OS_func_0124(OSMutex *mutex) {
    OSThread *temp_r0;
    s32 temp_r1;
    OS_Mutex_UnkStruct1 *temp_r1_2;
    s32 temp_r3;
    OSIntrMode irq;
    BOOL result;
    OSThread *temp_r2;

    irq     = OS_DisableInterrupts();
    temp_r2 = mutex->unk_08;
    temp_r0 = data_021384c0.unk_04;
    if (temp_r2 == NULL) {
        temp_r3       = (mutex->unk_0c & ~0xFF000000) | 0x10000000;
        mutex->unk_08 = temp_r0;
        mutex->unk_0c = (s32) ((temp_r3 & 0xFF000000) | ((temp_r3 + 1) & ~0xFF000000));
        OS_func_0067(temp_r0, mutex);
        result = true;
    } else if (temp_r2 != temp_r0) {
        result = false;
    } else {
        temp_r1       = mutex->unk_0c;
        result        = true;
        mutex->unk_0c = (s32) ((temp_r1 & 0xFF000000) | ((temp_r1 + 1) & ~0xFF000000));
    }
    OS_RestoreInterrupts(irq);
    return result;
}

static void OS_func_0125(OSMutex *mutex, u32 param2) {
    u32 temp_r0;
    BOOL var_r1;
    OSThread *temp_r0_1;
    s32 temp_r3;
    OSIntrMode irq;

    irq       = OS_DisableInterrupts();
    var_r1    = false;
    temp_r0_1 = data_021384c0.unk_04;
    if ((param2 != 0) && (param2 != (mutex->unk_0c & 0xFF000000))) {
        OS_RestoreInterrupts(irq);
        return;
    }
    temp_r3 = mutex->unk_0c & 0xFF000000;
    switch (temp_r3) {
        case 0x10000000:
        case 0x30000000:
            if (mutex->unk_08 != temp_r0_1) {
                break;
            }
            temp_r3 = mutex->unk_0c;
        case 0x20000000:
            temp_r3       = temp_r3 | ((temp_r3 - 1) & ~0xFF000000);
            mutex->unk_0c = temp_r3;
            if (!(temp_r3 & ~0xFF000000)) {
                var_r1 = true;
            }
            break;
        default:
            OS_RestoreInterrupts(irq);
            return;
    }
    if (var_r1) {
        OS_func_0068(temp_r0_1, mutex);
        mutex->unk_08 = NULL;
        mutex->unk_0c = (s32) (mutex->unk_0c & ~0xFF000000);
        OS_WakeupThread(mutex);
    }
    OS_RestoreInterrupts(irq);
    return;
}

static void OS_func_0067(OSThread *param1, OSMutex *mutex) {
    OSMutex *temp_r3;

    temp_r3 = param1->unk_88.unk_04;
    if (temp_r3 == NULL) {
        param1->unk_88.unk_00 = mutex;
    } else {
        temp_r3->unk_10 = mutex;
    }
    mutex->unk_14         = temp_r3;
    mutex->unk_10         = 0;
    param1->unk_88.unk_04 = mutex;
}

static void OS_func_0068(OSThread *param1, OSMutex *mutex) {
    OSMutex *temp_r1;
    OSMutex *temp_r2;

    temp_r2 = mutex->unk_10;
    temp_r1 = mutex->unk_14;
    if (temp_r2 == NULL) {
        param1->unk_88.unk_04 = temp_r1;
    } else {
        temp_r2->unk_14 = temp_r1;
    }
    if (temp_r1 == NULL) {
        param1->unk_88.unk_00 = temp_r2;
    } else {
        temp_r1->unk_10 = temp_r2;
    }
}
