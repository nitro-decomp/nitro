#include "nitro/mi.h"
#include "nitro/os.h"

typedef struct OS_UnkStruct2 {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */
} OS_UnkStruct2;

static void OS_func_0045(OSThread *thread, void *arg);
static void OS_func_0046(void *);
static void OS_func_0047(void);
static OSThread *OS_func_0206bbbc(OSThread **param1);
static void OS_func_0206bd78(void);
static void OS_func_0206bda0(void *);
static void OS_func_0206bdb0(void);
static void OS_func_0206be18(OSThread *thread, u32 param2);
static void OS_func_0206be20(OSThread *thread, void (*threadFunc)(void *arg), void *);
static u32 OS_func_0206bea4(OSThread *thread);
static void OS_func_0206bef0(OSThread *thread);

static u8 data_0216a330[0xc8] ATTRIBUTE_ALIGN(16);
static OSThread data_0216a270;
static OSThread data_0216a1b0;
static void (*data_0216a1ac)(OSThread *, OSThread *);

static OSThread *data_0216a1a4                       = NULL;
static OS_UnkStruct2 data_0216a1a0                   = {};
static u32 sThreadCount                              = 0; // 0216a19c
static void *data_0216a198                           = NULL;
static u32 data_0216a194                             = 0;
static u32 data_0216a190                             = 0;
static u32 data_0216a18c                             = 0;
static u32 data_0216a188                             = 0;
static OSThread **data_0216a184                      = NULL;
static u32 data_0216a180                             = 0;
static void (*data_0216a17c)(OSThread *, OSThread *) = NULL;
static OSThread *data_0216a1a8                       = NULL;

static u32 OS_func_0035(void) {
    return ++sThreadCount;
}

static void OS_func_0036(OSLinkedList *list, OSThread *thread) {
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

static OSThread *OS_func_0037(OSLinkedList *list) {
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

static OSThread *OS_func_0038(OSLinkedList *list, OSThread *thread) {
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

s32 OS_func_0039(OS_UnkStruct1 *param1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = param1->unk_00;
    if (iVar2 != 0) {
        iVar1          = *(s32 *) (iVar2 + 0x10);
        param1->unk_00 = iVar1;
        if (iVar1 != 0) {
            *(u32 *) (iVar1 + 0x14) = 0;
        } else {
            param1->unk_04 = 0;
        }
    }
    return iVar2;
}

static void OS_func_0040(OSThread *thread) {
    OSThread *iter = data_0216a1a8;
    OSThread *prev = NULL;
    while (iter != NULL && iter->prio < thread->prio) {
        prev = iter;
        iter = iter->nextPrio;
    }
    if (prev == NULL) {
        thread->nextPrio = data_0216a1a8;
        data_0216a1a8    = thread;
    } else {
        thread->nextPrio = prev->nextPrio;
        prev->nextPrio   = thread;
    }
}

static void OS_func_0041(OSThread *param_1) {
    OSThread *iter = data_0216a1a8;
    OSThread *prev = NULL;
    while (iter != NULL && iter != param_1) {
        prev = iter;
        iter = iter->nextPrio;
    }
    if (prev == NULL) {
        data_0216a1a8 = param_1->nextPrio;
    } else {
        prev->nextPrio = param_1->nextPrio;
    }
}

static void OS_func_0042(void) {
    OSThread *pOVar1;
    OSThread *pOVar2;
    void (*r2)(OSThread *, OSThread *);
    if (data_0216a180 != 0) {
        return;
    }
    if (data_0216a1a0.unk_02 != 0 || OS_func_0206d3cc() == 0x12) {
        data_0216a1a0.unk_00 = 0;
        return;
    }
    pOVar1 = *data_0216a184;
    pOVar2 = OS_func_0206bbbc(data_0216a184);
    if (pOVar1 == pOVar2 || pOVar2 == NULL) {
        return;
    }
    if (pOVar1->unk_64 != 2 && OS_func_0206bea4(pOVar1) != 0) {
        return;
    }
    if (data_0216a17c != NULL) {
        data_0216a17c(pOVar1, pOVar2);
    }
    if (data_0216a1ac != NULL) {
        data_0216a1ac(pOVar1, pOVar2);
    }
    data_0216a1a8 = pOVar2;
    OS_func_0206bef0(pOVar2);
}

extern u32 _OS_unk_linker_1; // 0xffffd9b8
extern u32 _OS_unk_linker_2; // 0x800
extern u32 _OS_unk_linker_3; // 0x027e0080
#define OS_unk_linker_1 ((s32) (&_OS_unk_linker_1))
#define OS_unk_linker_2 ((u32) (&_OS_unk_linker_2))
#define OS_unk_linker_3 ((u8 *) (&_OS_unk_linker_3))

void OS_InitThread(void) {
    u8 *stackLo;
    if (data_0216a188 != 0) {
        return;
    }
    data_0216a188          = 1;
    data_0216a184          = &data_0216a1a4;
    data_0216a270.prio     = 16;
    data_0216a270.unk_6c   = 0;
    data_0216a270.unk_64   = 1;
    data_0216a270.nextPrio = NULL;
    data_0216a270.unk_74   = 0;
    data_0216a1a8          = &data_0216a270;
    data_0216a1a4          = &data_0216a270;
    if (OS_unk_linker_1 <= 0) {
        stackLo = OS_unk_linker_3 - OS_unk_linker_1;
    } else {
        stackLo = DTCM_LO + 0x3f80 - OS_unk_linker_2 - OS_unk_linker_1;
    }
    data_0216a270.stackHi                = DTCM_LO + 0x3f80 - OS_unk_linker_2;
    data_0216a270.stackLo                = stackLo;
    data_0216a270.unk_98                 = 0;
    *(u32 *) (data_0216a270.stackHi - 4) = 0xfddb597d;
    *(u32 *) (data_0216a270.stackLo)     = 0x7bf9dd5b;
    data_0216a270.unk_a0                 = 0;
    data_0216a270.unk_9c                 = 0;
    data_0216a1a0.unk_00                 = 0;
    data_0216a1a0.unk_02                 = 0;
    REG_027FFFA0                         = (u32) &data_0216a1a0;
    OS_func_0206bd78();
    OS_CreateThread(&data_0216a1b0, OS_func_0206bda0, NULL, &data_0216a330[0xc8], 0xc8, 31);
    data_0216a1b0.prio   = 32;
    data_0216a1b0.unk_64 = 1;
}

void OS_CreateThread(OSThread *thread, void (*threadFunc)(void *arg), void *arg, void *stackHi, u32 stackSize,
                     u32 prio) {
    u32 uVar1      = OS_DisableInterrupts_Irq();
    u32 uVar2      = OS_func_0035();
    thread->prio   = prio;
    thread->unk_6c = uVar2;
    thread->unk_64 = 0;
    thread->unk_74 = 0;
    OS_func_0040(thread);
    thread->stackHi                = stackHi;
    thread->stackLo                = stackHi - stackSize;
    thread->unk_98                 = 0;
    *(u32 *) (thread->stackHi - 4) = 0xfddb597d;
    *(u32 *) thread->stackLo       = 0x7bf9dd5b;
    thread->unk_a0                 = 0;
    thread->unk_9c                 = 0;
    OS_func_0206be20(thread, threadFunc, stackHi - 4);
    thread->arg    = arg;
    thread->unk_3c = OS_func_0044;
    MI_CpuFill32(0, stackHi - stackSize + 4, stackSize - 8);
    thread->unk_84        = 0;
    thread->unk_88.unk_00 = 0;
    thread->unk_88.unk_04 = 0;
    OS_func_0206be18(thread, 0);
    thread->unk_78 = 0;
    thread->next   = 0;
    thread->prev   = 0;
    MI_CpuFill32(0, &thread->unk_a4, 0xc);
    thread->unk_b0 = 0;
    OS_RestoreInterrupts(uVar1);
}

void OS_func_0044(void) {
    OS_DisableInterrupts_Irq();
    OS_func_0045(data_0216a1a4, NULL);
}

static void OS_func_0045(OSThread *thread, void *arg) {
    if (data_0216a198 != 0) {
        OS_func_0206be20(thread, OS_func_0046, data_0216a198);
        thread->arg = arg;
        thread->unk_00 |= 0x80;
        thread->unk_64 = 1;
        OS_func_0206bef0(thread);
    } else {
        OS_func_0046(arg);
    }
}

static void OS_func_0046(void *arg) {
    void (*pcVar1)(void *) = (*data_0216a184)->unk_b4;
    if (pcVar1 != NULL) {
        (*data_0216a184)->unk_b4 = 0;
        pcVar1(arg);
        OS_DisableInterrupts_Irq();
    }
    OS_func_0047();
}
