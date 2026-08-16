#ifndef _NITRO_OS_MUTEX_H
#define _NITRO_OS_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/os/common.h"
#include "nitro/types.h"

struct OSMutex;
typedef struct OS_UnkStruct1 {
    /* 00 */ struct OSMutex *unk_00;
    /* 04 */ struct OSMutex *unk_04;
    /* 08 */
} OS_UnkStruct1;

struct OSThread;
typedef struct OS_Mutex_UnkStruct1 {
    /* 00 */ PAD(0x00, 0x04);
    /* 04 */ struct OSThread *unk_04;
    /* 08 */
} OS_Mutex_UnkStruct1;

typedef struct OSMutex {
    /* 00 */ OSLinkedList unk_00;
    /* 08 */ struct OSThread *unk_08;
    /* 0c */ vu32 unk_0c;
    /* 10 */ struct OSMutex *unk_10;
    /* 14 */ struct OSMutex *unk_14;
    /* 18 */
} OSMutex;

void OS_InitMutex(OSMutex *mutex);
void OS_LockMutex(OSMutex *mutex);
void OS_UnlockMutex(OSMutex *mutex);

void OSi_UnlockAllMutex(struct OSThread *param1);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
