#ifndef _NITRO_OS_H
#define _NITRO_OS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/reg.h"

#define OS_IE_V_BLANK 1
#define OS_IE_H_BLANK 2

#define OS_ARENA_MAIN 0
#define OS_ARENA_ITCM 3
#define OS_ARENA_DTCM 4
#define OS_CURRENT_HEAP_HANDLE -1

#define OS_MESSAGE_NOBLOCK 0
#define OS_MESSAGE_BLOCK 1

#define OS_CONSOLE_ISDEBUGGER 0x40000000
#define OS_CONSOLE_NITRO 0x80000000

#define OS_LOCK_ID_ERROR -3

typedef struct OSLinkedList {
    /* 00 */ void *head;
    /* 04 */ void *tail;
    /* 08 */
} OSLinkedList;

typedef struct OS_UnkStruct1 {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 unk_04;
    /* 08 */
} OS_UnkStruct1;

typedef struct OSThread {
    /* 00 */ u32 unk_00;
    /* 04 */ void *arg;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
    /* 18 */ u32 unk_18;
    /* 1c */ u32 unk_1c;
    /* 20 */ u32 unk_20;
    /* 24 */ u32 unk_24;
    /* 28 */ u32 unk_28;
    /* 2c */ u32 unk_2c;
    /* 30 */ u32 unk_30;
    /* 34 */ u32 unk_34;
    /* 38 */ u32 unk_38;
    /* 3c */ void *unk_3c;
    /* 40 */ u32 unk_40;
    /* 44 */ u32 unk_44;
    /* 48 */ u8 unk_48[0x64 - 0x48];
    /* 64 */ u32 unk_64;
    /* 68 */ struct OSThread *nextPrio; // next thread with lower priority
    /* 6c */ u32 unk_6c;
    /* 70 */ u32 prio;
    /* 74 */ u32 unk_74;
    /* 78 */ u32 unk_78;
    /* 7c */ struct OSThread *prev;
    /* 80 */ struct OSThread *next;
    /* 84 */ u32 unk_84;
    /* 88 */ OS_UnkStruct1 unk_88;
    /* 90 */ void *stackLo;
    /* 94 */ void *stackHi;
    /* 98 */ u32 *unk_98;
    /* 9c */ u32 *unk_9c;
    /* a0 */ u32 *unk_a0;
    /* a4 */ u8 unk_a4[0xb0 - 0xa4];
    /* b0 */ u32 *unk_b0;
    /* b4 */ void (*unk_b4)(void *);
    /* b8 */
} ATTRIBUTE_ALIGN(16) OSThread;

typedef struct OSMessageQueue {
    /* 00 */ OSLinkedList unk_00;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
    /* 18 */ u32 unk_18;
    /* 1c */ u32 unk_1c;
    /* 20 */
} OSMessageQueue;

// TODO: Maybe align is wrong? g_msgBuf in PM4 is aligned by 8 with 4 bytes of padding before it
typedef void *OSMessage ATTRIBUTE_ALIGN(8);

typedef struct OSAlarm {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 unk_04;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ void *unk_14;
    /* 18 */ void *unk_18;
    /* 1c */ u32 unk_1c;
    /* 20 */ u32 unk_20;
    /* 24 */ u32 unk_24;
    /* 28 */ u32 unk_28;
    /* 2c */
} OSAlarm;

typedef struct OSMutex {
    /* 00 */ OSLinkedList unk_00;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
    /* 18 */
} OSMutex;

typedef u32 OSHeapHandle;
typedef u64 OSTime;

void OS_Init(void);
void OS_InitTick(void);
void OS_InitAlarm(void);
void OS_SetIrqFunction(u32 type, void (*function)());

void OS_EnableIrqMask(u32 mask);

void OS_WaitVBlankIntr(void);

void OS_InitMutex(OSMutex *mutex);
void OS_LockMutex(OSMutex *mutex);
void OS_UnlockMutex(OSMutex *mutex);

void _OS_Panic();

#ifdef DEBUG
void OS_TPrintf(const char *format, ...) {}
void OS_Printf(const char *format, ...) {}
void OS_Panic(const char *message) {}
#else
    #define OS_TPrintf(...)
    #define OS_Printf(...)
    #define OS_Panic(...) _OS_Panic()
#endif

void OS_ResetSystem(u32);

void *OS_InitAlloc(u32 arena, u32 addrLo, u32 addrHi, u32);
u32 OS_GetArenaLo(u32 arena);
u32 OS_GetArenaHi(u32 arena);

void OS_SetArenaLo(u32 arena, void *addr);
void *OS_AllocFromArenaLo(u32 arena, u32 size, u32 num);

OSHeapHandle OS_CreateHeap(u32 arena, void *addrLo, void *addrHi);
void OS_SetCurrentHeap(u32 arena, OSHeapHandle heap);
void OS_DumpHeap(u32 arena, OSHeapHandle heap);
void *OS_AllocFromHeap(u32 arena, OSHeapHandle heap, u32 size);
void OS_FreeFromHeap(u32 arena, OSHeapHandle heap, void *ptr);

void OS_Sleep(u32 time);

void OS_func_0043(void);
void OS_CreateThread(OSThread *thread, void (*threadFunc)(void *arg), void *arg, void *stackHi, u32 stackSize,
                     u32 prio);
void OS_WakeupThreadDirect(OSThread *thread);
BOOL OS_IsThreadTerminated(const OSThread *thread);
void OS_KillThread(OSThread *thread, void *);
OSThread *OS_GetCurrentThread(void);
#ifdef DEBUG
void OS_CheckStack(OSThread *thread);
#else
    #define OS_CheckStack(thread)
#endif
void OS_func_0044(void);
s32 OS_func_0039(OS_UnkStruct1 *param1);

void OS_InitMessageQueue(OSMessageQueue *queue, OSMessage *buf, u32 bufLength);
void OS_ReceiveMessage(OSMessageQueue *queue, OSMessage *message, u32 block);
void OS_SendMessage(OSMessageQueue *queue, OSMessage message, u32 block);

void OS_CreateAlarm(OSAlarm *alarm);
void OS_SetPeriodicAlarm(OSAlarm *alarm, OSTime, OSTime, void (*callback)(void *arg), void *arg);
void OS_CancelAlarm(OSAlarm *alarm);

OSTime OS_GetTick(void);

u32 OS_GetConsoleType(void);

u32 OS_GetLockID(void);

u32 OS_DisableInterrupts_Irq(void);
void OS_RestoreInterrupts(u32);

BOOL OS_func_0206d5ac(u16, u32);
void OS_func_0206d66c(u16, u32);
u32 OS_func_0206d3cc(void);

inline void OS_SetIrqCheckFlag(void) {
    REG_IRQ |= 1;
}

inline u16 OS_EnableIrq(void) {
    u16 oldVal = REG_IME;
    REG_IME    = 1;
    return oldVal;
}

inline u32 OS_GetMainArenaLo() {
    return OS_GetArenaLo(OS_ARENA_MAIN);
}
inline u32 OS_GetMainArenaHi(void) {
    return OS_GetArenaHi(OS_ARENA_MAIN);
}
inline u32 OS_GetITCMArenaLo() {
    return OS_GetArenaLo(OS_ARENA_ITCM);
}
inline u32 OS_GetITCMArenaHi() {
    return OS_GetArenaHi(OS_ARENA_ITCM);
}
inline u32 OS_GetDTCMArenaLo() {
    return OS_GetArenaLo(OS_ARENA_DTCM);
}
inline u32 OS_GetDTCMArenaHi() {
    return OS_GetArenaHi(OS_ARENA_DTCM);
}

inline void OS_SetMainArenaLo(void *addr) {
    OS_SetArenaLo(OS_ARENA_MAIN, addr);
}

inline void *OS_AllocFromMainArenaLo(u32 size, u32 num) {
    return OS_AllocFromArenaLo(OS_ARENA_MAIN, size, num);
}

inline void *OS_Alloc(u32 size) {
    return OS_AllocFromHeap(OS_ARENA_MAIN, OS_CURRENT_HEAP_HANDLE, size);
}

inline void OS_Free(void *ptr) {
    OS_FreeFromHeap(OS_ARENA_MAIN, OS_CURRENT_HEAP_HANDLE, ptr);
}

inline OSTime OS_MilliSecondsToTicks(OSTime ms) {
    return (ms * 33514) / 64;
}

inline OSTime OS_MicroSecondsToTicks(OSTime us) {
    return OS_MilliSecondsToTicks(us) / 1000;
}

inline OSTime OS_TicksToMilliSeconds(OSTime ticks) {
    return (ticks * 64) / 33514;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
