#ifndef _NITRO_OS_COMMON_H
#define _NITRO_OS_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/types.h"

typedef struct OSLinkedList {
    /* 00 */ void *head;
    /* 04 */ void *tail;
    /* 08 */
} OSLinkedList;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
