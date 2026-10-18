#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/os/os_mutex.h"

#ifdef NITRO_DEBUG
    void _TEMP_PANIC_2(char* file, long line, char* message, ...);
    #define __LS_OSi_RemoveThreadFromList_0 0x29c
    #define __LS_OS_SetThreadPriority_0 0x6ed
    #define __LS_OS_SetThreadPriority_1 0x6ee
    #define __LS_OS_GetThreadPriority_0 0x724
    #define __LS_OS_CreateThread_0 0x33a
    #define __LS_OS_CreateThread_1 0x33c
    #define __LS_OS_CreateThread_2 0x33d
    #define __LS_OS_CreateThread_3 0x33e
    #define __LS_OS_CreateThread_4 0x346
    #define __LS_OS_CreateThread_5 0x5d
    #define __LS_OS_CreateThread_6 0x5e
    
    //#ifdef SPOOF_LINE_NUMBERS
        #define ASSERT_WITH_MESSAGE_2(line_number, condition, message) do {if (condition) _TEMP_PANIC_2(__FILE__, line_number, message);} while (0)
        #define ASSERT_WITH_MESSAGE_2_ARG(line_number, condition, message, arg) do {if (condition) _TEMP_PANIC_2(__FILE__, line_number, message, arg);} while (0) // This might actually be dedicated to align casts?
    //#else
    //    #define ASSERT_WITH_MESSAGE_2(condition, message) if (condition) _TEMP_PANIC_2(__FILE__, __LINE__, message)
    //#endif
#else
    #define ASSERT_WITH_MESSAGE_2(condition, message)
#endif

typedef struct OS_UnkStruct2 {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */
} OS_UnkStruct2;

typedef void (*OSSwitchThreadCallback)(OSThread *, OSThread *);

static void OSi_ExitThread_ArgSpecified(OSThread *thread, void *arg);
static void OSi_ExitThread(void *);
static void OSi_ExitThread_Destroy(void);
static OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback);
static void OSi_IdleThreadProc(void *);
static void OS_SetThreadDestructor(OSThread *thread, OSThreadDtor dtor);
static void OS_InitContext(OSThread *thread, void (*threadFunc)(void *arg), void *);
static u32 OS_SaveContext(OSThread *thread);
static void OS_LoadContext(OSThread *thread);
static void OS_RescheduleThread(void);
static u32 OS_DisableScheduler(void);
static u32 OS_EnableScheduler(void);
static BOOL OS_SetThreadPriority(OSThread *thread, u32 prio);
static u32 OS_GetThreadPriority(OSThread *thread);
static void OSi_SleepAlarmCallback(OSThread **arg);

static u8 sIdleThreadStack[0xc8] ATTRIBUTE_ALIGN(16);
static OSThread sMainThread;
static OSThread sIdleThread;
static OSSwitchThreadCallback sSwitchThreadCallback;

static OSThread *gHighestPriorityThread                       = NULL;
static OSThread *sCurrentThread                               = NULL;
static OS_UnkStruct2 data_0216a1a0                            = {};
static u32 sLatestThreadId                                    = 0;
static void *sThreadExitStack                                 = NULL;
static u32 data_0216a194                                      = 0;
static u32 data_0216a190                                      = 0;
static OSThread **spCurrentThread                             = NULL;
static u32 data_0216a18c                                      = 0;
static u32 sSchedulerDisableCount                             = 0;
static void (*sSwitchThreadCallback2)(OSThread *, OSThread *) = NULL;
static BOOL OSi_ThreadInitialized                             = false;

static u32 OSi_GetUnusedThreadId(void) {
    return ++sLatestThreadId;
}

static void OSi_InsertLinkToQueue(OSThreadQueue *list, OSThread *thread) {
    OSThread *it;
    for (it = list->head; it != NULL && it->prio <= thread->prio; it = it->next) {
        if (it == thread) {
            return;
        }
    }
    if (it == NULL) {
        OSThread *prev = list->tail;
        if (prev == NULL) {
            list->head = thread;
        } else {
            prev->next = thread;
        }
        thread->prev = prev;
        thread->next = NULL;
        list->tail   = thread;
    } else {
        OSThread *prev = it->prev;
        if (prev == NULL) {
            list->head = thread;
        } else {
            prev->next = thread;
        }
        thread->prev = prev;
        thread->next = it;
        it->prev     = thread;
    }
}

static OSThread *OSi_RemoveLinkFromQueue(OSLinkedList *list) {
    OSThread *removed = list->head;
    if (removed != NULL) {
        OSThread *next = removed->next;
        list->head     = next;
        if (next != NULL) {
            next->prev = 0;
        } else {
            list->tail      = NULL;
            removed->unk_78 = 0;
        }
    }
    return removed;
}

static OSThread *OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue *list, OSThread *thread) {
    OSThread *iter;
    OSThread *next;
    OSThread *head = list->head;
    iter           = head;
    if (head != NULL) {
        do {
            next = iter->next;
            if (iter == thread) {
                OSThread *prev = iter->prev;
                if (head == iter) {
                    list->head = next;
                } else {
                    prev->next = next;
                }
                thread = list->tail;
                if (thread == iter) {
                    list->tail = prev;
                } else {
                    next->prev = prev;
                }
                break;
            }
            iter = next;
        } while (next != NULL);
    }
    return iter;
}

OSMutex *OS_func_0039(OSMutexQueue *param1) {
    OSMutex *iVar1;
    OSMutex *iVar2;

    iVar2 = param1->head;
    if (iVar2 != NULL) {
        iVar1        = iVar2->queue.head;
        param1->head = iVar1;
        if (iVar1 != 0) {
            iVar1->queue.tail = NULL;
        } else {
            param1->tail = NULL;
        }
    }
    return iVar2;
}

static void OSi_InsertThreadToList(OSThread *thread) {
    OSThread *iter = gHighestPriorityThread;
    OSThread *prev = NULL;
    while (iter != NULL && iter->prio < thread->prio) {
        prev = iter;
        iter = iter->nextPrio;
    }
    if (prev == NULL) {
        thread->nextPrio       = gHighestPriorityThread;
        gHighestPriorityThread = thread;
    } else {
        thread->nextPrio = prev->nextPrio;
        prev->nextPrio   = thread;
    }
}

static void OSi_RemoveThreadFromList(OSThread *param_1) {
    OSThread *iter = gHighestPriorityThread;
    OSThread *prev = NULL;
    while (iter != NULL && iter != param_1) {
        prev = iter;
        iter = iter->nextPrio;
    }
    ASSERT_WITH_MESSAGE_2(__LS_OSi_RemoveThreadFromList_0, iter == NULL, "OS_GetThreadPriority: bad thread");
    if (prev == NULL) {
        gHighestPriorityThread = param_1->nextPrio;
    } else {
        prev->nextPrio = param_1->nextPrio;
    }
}

static void OSi_RescheduleThread(void) {
    OSThread *currThread;
    OSThread *nextThread;
    if (sSchedulerDisableCount > 0) {
        return;
    }
    if (data_0216a1a0.unk_02 != 0 || OS_GetProcMode() == 0x12) {
        data_0216a1a0.unk_00 = 0;
        return;
    }
    currThread = *spCurrentThread;
    nextThread = OS_SelectThread();
    if (currThread == nextThread || nextThread == NULL) {
        return;
    }
    if (currThread->unk_64 != 2 && OS_SaveContext(currThread) != 0) {
        return;
    }
    if (sSwitchThreadCallback2 != NULL) {
        sSwitchThreadCallback2(currThread, nextThread);
    }
    if (sSwitchThreadCallback != NULL) {
        sSwitchThreadCallback(currThread, nextThread);
    }
    gHighestPriorityThread = nextThread;
    OS_LoadContext(nextThread);
}

void OS_InitThread(void) {
    u8 *stackLo;
    if (OSi_ThreadInitialized) {
        return;
    }
    OSi_ThreadInitialized  = true;
    spCurrentThread        = &sCurrentThread;
    sMainThread.prio       = 16;
    sMainThread.unk_6c     = 0;
    sMainThread.unk_64     = 1;
    sMainThread.nextPrio   = NULL;
    sMainThread.unk_74     = 0;
    gHighestPriorityThread = &sMainThread;
    sCurrentThread         = &sMainThread;
    if (OS_unk_linker_1 <= 0) {
        stackLo = OS_unk_linker_3 - OS_unk_linker_1;
    } else {
        stackLo = DTCM_LO + 0x3f80 - OS_unk_linker_2 - OS_unk_linker_1;
    }
    sMainThread.stackHi                = DTCM_LO + 0x3f80 - OS_unk_linker_2;
    sMainThread.stackLo                = stackLo;
    sMainThread.unk_98                 = 0;
    *(u32 *) (sMainThread.stackHi - 8) = 0xfddb597d;
    *(u32 *) (sMainThread.stackLo)     = 0x7bf9dd5b;
    sMainThread.unk_9c.tail            = NULL;
    sMainThread.unk_9c.head            = NULL;
    data_0216a1a0.unk_00               = 0;
    data_0216a1a0.unk_02               = 0;
    REG_027FFFA0                       = (u32) &data_0216a1a0;
    OS_SetSwitchThreadCallback(NULL);
    OS_CreateThread(&sIdleThread, OSi_IdleThreadProc, NULL, &sIdleThreadStack[0xc8], 0xc8, 31);
    sIdleThread.prio   = 32;
    sIdleThread.unk_64 = 1;
}

void OS_CreateThread(OSThread *thread, void (*threadFunc)(void *arg), void *arg, void *stackHi, u32 stackSize, u32 prio) {
    // TODO: This seems to have has some pretty big changes between GTA CW & star wars
    s32 uVar1;
    s32 uVar2;
    u32 destination_address;
    ASSERT_WITH_MESSAGE_2(__LS_OS_CreateThread_0, OSi_ThreadInitialized == FALSE, "thread system were not initialized.");
    ASSERT_WITH_MESSAGE_2(__LS_OS_CreateThread_1, prio > 0x1f, "invalid priority");
    ASSERT_WITH_MESSAGE_2_ARG(__LS_OS_CreateThread_2, (u32)stackSize & 3 != 0, "stack size must be aligned by %d", 4);
    ASSERT_WITH_MESSAGE_2_ARG(__LS_OS_CreateThread_3, (u32)stackHi & 3 != 0, "stack must be aligned by %d", 4);

    uVar1      = OS_DisableInterrupts();
    uVar2      = OSi_GetUnusedThreadId();
    if (uVar1 < 0) {
        ASSERT_WITH_MESSAGE_2(__LS_OS_CreateThread_4, uVar2 < 0, "OS_CreateThread: thread entry not allocated");
        OS_RestoreInterrupts(uVar1);
    }
    thread->prio   = prio;
    thread->unk_6c = uVar2;
    thread->unk_64 = 0;
    thread->unk_74 = 0;
    OSi_InsertThreadToList(thread);
    thread->stackHi                = stackHi;
    thread->stackLo                = stackHi - stackSize;
    thread->unk_98                 = 0;
    *(u32 *) (thread->stackHi - 8) = 0xfddb597d;
    *(u32 *) thread->stackLo       = 0x7bf9dd5b;
    thread->unk_9c.tail            = NULL;
    thread->unk_9c.head            = NULL;
    OS_InitContext(thread, threadFunc, stackHi - 8);
    thread->context.regs[0]  = (u32) arg; // set first argument to threadFunc
    thread->context.regs[14] = (u32) OS_ExitThread; // set return address
    ASSERT_WITH_MESSAGE_2(__LS_OS_CreateThread_5, stackSize & 3 != 0, "size & 3 must be 0");
    destination_address = (u32)stackHi - stackSize + 4;
    ASSERT_WITH_MESSAGE_2(__LS_OS_CreateThread_6, destination_address & 3 != 0, "destination address must be in 4-byte alignment");
    MIi_CpuClear32(0, (void*)destination_address, stackSize - 12);
    thread->unk_84      = 0;
    thread->unk_88.head = NULL;
    thread->unk_88.tail = NULL;
    OS_SetThreadDestructor(thread, NULL);
    thread->unk_78 = 0;
    thread->next   = 0;
    thread->prev   = 0;
    MIi_CpuClear32(0, &thread->unk_a4, 0xc);
    thread->alarm = 0;
    OS_RestoreInterrupts(uVar1);
}

void OS_ExitThread(void) {
    OS_DisableInterrupts();
    OSi_ExitThread_ArgSpecified(sCurrentThread, NULL);
}

static void OSi_ExitThread_ArgSpecified(OSThread *thread, void *arg) {
    if (sThreadExitStack != 0) {
        OS_InitContext(thread, OSi_ExitThread, sThreadExitStack);
        thread->context.regs[0] = (u32) arg; // set first argument to OSi_ExitThread
        thread->context.cpsr |= 0x80;
        thread->unk_64 = 1;
        OS_LoadContext(thread);
    } else {
        OSi_ExitThread(arg);
    }
}

static void OSi_ExitThread(void *arg) {
    OSThreadDtor dtor = (*spCurrentThread)->destructor;
    if (dtor != NULL) {
        (*spCurrentThread)->destructor = NULL;
        dtor(arg);
        OS_DisableInterrupts();
    }
    OSi_ExitThread_Destroy();
}

static void OSi_ExitThread_Destroy(void) {
    OSThreadQueue *list;
    OSThread *thread;

    thread = *spCurrentThread;
    OS_DisableScheduler();
    OSi_UnlockAllMutex(thread);
    list = thread->unk_78;
    if (list != 0) {
        OSi_RemoveSpecifiedLinkFromQueue(list, thread);
    }
    OSi_RemoveThreadFromList(thread);
    thread->unk_64 = 2;
    OS_WakeupThread(&thread->unk_9c);
    OS_EnableScheduler();
    OS_RescheduleThread();
    OS_Terminate();
}

void OS_SleepThread(OSThreadQueue *list) {
    s32 temp_r4;
    OSThread *temp_r5;

    temp_r4 = OS_DisableInterrupts();
    temp_r5 = *spCurrentThread;
    if (list) {
        temp_r5->unk_78 = list;
        OSi_InsertLinkToQueue(list, temp_r5);
    }
    temp_r5->unk_64 = 0;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(temp_r4);
}

void OS_WakeupThread(OSThreadQueue *list) {
    OSIntrMode irq;
    OSThread *thread;

    irq = OS_DisableInterrupts();
    if (list->head != NULL) {
        while (list->head != NULL) {
            thread         = OSi_RemoveLinkFromQueue((OSLinkedList *) list);
            thread->unk_64 = 1;
            thread->unk_78 = NULL;
            thread->next   = NULL;
            thread->prev   = NULL;
        }
        list->tail = NULL;
        list->head = NULL;
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(irq);
}

void OS_WakeupThreadDirect(OSThread *thread) {
    OSIntrMode irq;

    irq            = OS_DisableInterrupts();
    thread->unk_64 = 1;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(irq);
}

OSThread *OS_SelectThread(void) {
    OSThread *thread;

    for (thread = gHighestPriorityThread; thread != NULL && thread->unk_64 != 1; thread = thread->nextPrio) {
    }
    return thread;
}

static void OS_RescheduleThread(void) {
    OSIntrMode irq;

    irq = OS_DisableInterrupts();
    OSi_RescheduleThread();
    OS_RestoreInterrupts(irq);
}

static BOOL OS_SetThreadPriority(OSThread *thread, u32 prio) {
    OSThread *iter;
    OSThread *prev;
    OSIntrMode irq;

    iter = gHighestPriorityThread;
    prev = NULL;
    ASSERT_WITH_MESSAGE_2(__LS_OS_SetThreadPriority_0, prio > 0x1f, "invalid priority");
    ASSERT_WITH_MESSAGE_2(__LS_OS_SetThreadPriority_1, thread == &sIdleThread, "cannot change idle thread priority.");
    irq  = OS_DisableInterrupts();
    while ((iter != NULL) && (iter != thread)) {
        prev = iter;
        iter = iter->nextPrio;
    }
    if ((iter == NULL) || (iter == &sIdleThread)) {
        OS_RestoreInterrupts(irq);
        return false;
    }
    if (iter->prio != prio) {
        if (prev == NULL) {
            gHighestPriorityThread = thread->nextPrio;
        } else {
            prev->nextPrio = thread->nextPrio;
        }
        thread->prio = prio;
        OSi_InsertThreadToList(thread);
        OSi_RescheduleThread();
    }
    OS_RestoreInterrupts(irq);
    return true;
}

static u32 OS_GetThreadPriority(OSThread *thread) {
    ASSERT_WITH_MESSAGE_2(__LS_OS_GetThreadPriority_0, thread == NULL, "OS_GetThreadPriority: bad thread");
    return thread->prio;
}

void OS_Sleep(u32 time) {
    OSAlarm timer;
    OSThread *thread;
    OSIntrMode irq;

    OS_CreateAlarm(&timer);
    thread        = *spCurrentThread;
    irq           = OS_DisableInterrupts();
    thread->alarm = &timer;
    OS_func_0094(&timer, OS_MilliSecondsToTicks(time), &OSi_SleepAlarmCallback, &thread);
    while (thread != NULL) {
        OS_SleepThread(0);
    }
    OS_RestoreInterrupts(irq);
}

static void OSi_SleepAlarmCallback(OSThread **arg) {
    OSThread *thread;

    thread        = *arg;
    *arg          = NULL;
    thread->alarm = NULL;
    OS_WakeupThreadDirect(thread);
}

static OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback) {
    OSSwitchThreadCallback old;
    OSIntrMode irq;

    irq                   = OS_DisableInterrupts();
    old                   = sSwitchThreadCallback;
    sSwitchThreadCallback = callback;
    OS_RestoreInterrupts(irq);
    return old;
}

static void OSi_IdleThreadProc(void *arg) {
    OS_EnableInterrupts();
    while (true) {
        OS_Halt();
    }
}

static u32 OS_DisableScheduler(void) {
    OSIntrMode irq;
    u32 var_r4;

    irq = OS_DisableInterrupts();
    if (sSchedulerDisableCount < -1) {
        var_r4 = sSchedulerDisableCount;
        sSchedulerDisableCount++;
    }
    OS_RestoreInterrupts(irq);
    return var_r4;
}

static u32 OS_EnableScheduler(void) {
    OSIntrMode irq;
    u32 var_r4;

    irq    = OS_DisableInterrupts();
    var_r4 = 0;
    if (sSchedulerDisableCount > 0) {
        var_r4 = sSchedulerDisableCount;
        sSchedulerDisableCount--;
    }
    OS_RestoreInterrupts(irq);
    return var_r4;
}

static void OS_SetThreadDestructor(OSThread *thread, OSThreadDtor dtor) {
    thread->destructor = dtor;
}

static void OS_InitContext(OSThread *thread, void (*threadFunc)(void *arg), void *sp) {
    s32 temp_r1;
    s32 var_r1;
    u32 var_r2;
    BOOL thumb;

    threadFunc               = threadFunc + 4;
    thread->context.regs[15] = (u32) threadFunc; // set PC to threadFunc
    thread->context.sp       = (u32) sp;
    var_r2                   = (u32) sp - 0x40;
    if ((u32) var_r2 & 4) {
        var_r2 -= 4;
    }
    thread->context.regs[14] = var_r2;
    thumb                    = (u32) threadFunc & 1;
    thread->context.cpsr     = thumb ? 0x3F : 0x1F;
    thread->context.regs[0]  = 0;
    thread->context.regs[1]  = 0;
    thread->context.regs[2]  = 0;
    thread->context.regs[3]  = 0;
    thread->context.regs[4]  = 0;
    thread->context.regs[5]  = 0;
    thread->context.regs[6]  = 0;
    thread->context.regs[7]  = 0;
    thread->context.regs[8]  = 0;
    thread->context.regs[9]  = 0;
    thread->context.regs[10] = 0;
    thread->context.regs[11] = 0;
    thread->context.regs[12] = 0;
    thread->context.regs[13] = 0;
}

// clang-format off
static asm u32 OS_SaveContext(OSThread *thread) {
    #pragma push
    #pragma thumb off
    stmdb sp!, {r0, lr}
    add r0, r0, #0x48
    lda r1, CP_SaveContext
    blx r1
    ldmia sp!, {r0, lr}
    add r1, r0, #0
    mrs r2, cpsr
    str r2, [r1], #4
    mov r0, #0xd3
    msr cpsr_c, r0
    str sp, [r1, #0x40]
    msr cpsr_c, r2
    mov r0, #1
    stmia r1, {r0-r14}
    add r0, pc, #8
    str r0, [r1, #0x3c]
    mov r0, #0
    bx lr
    #pragma pop
}
// clang-format on

// clang-format off
static asm void OS_LoadContext(OSThread *thread) {
    #pragma push
    #pragma thumb off
    stmdb sp!, {r0, lr}
    add r0, r0, #0x48
    lda r1, CPi_RestoreContext
    blx r1
    ldmia sp!, {r0, lr}
    mrs r1, cpsr
    bic r1, r1, #0x1f
    orr r1, r1, #0xd3
    msr cpsr_c, r1
    ldr r1, [r0], #4
    msr spsr_fxsc, r1
    ldr sp, [r0, #0x40]
    ldr lr, [r0, #0x3c]
    ldmia r0, {r0-r14}^
    mov r0, r0
    subs pc, lr, #4
    #pragma pop
}// clang-format on
