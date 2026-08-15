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

typedef struct OS_Mutex_UnkStruct2 {
    /* 00 */ PAD(0x00, 0x84);
    /* 84 */ struct OSMutex *unk_84;
    /* 88 */ OS_UnkStruct1 unk_88;
    /* 8c */
} OS_Mutex_UnkStruct2;

typedef struct OS_Mutex_UnkStruct1 {
    /* 00 */ PAD(0x00, 0x04);
    /* 04 */ OS_Mutex_UnkStruct2 *unk_04;
    /* 08 */
} OS_Mutex_UnkStruct1;

typedef struct OSMutex {
    /* 00 */ OSLinkedList unk_00;
    /* 08 */ OS_Mutex_UnkStruct2 *unk_08;
    /* 0c */ vu32 unk_0c;
    /* 10 */ struct OSMutex *unk_10;
    /* 14 */ struct OSMutex *unk_14;
    /* 18 */
} OSMutex;

void OS_InitMutex(OSMutex *mutex);
void OS_LockMutex(OSMutex *mutex);
void OS_UnlockMutex(OSMutex *mutex);

void OS_func_0066(OS_Mutex_UnkStruct2 *param1);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
