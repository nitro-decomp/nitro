#ifndef _NITRO_TYPES_H
#define _NITRO_TYPES_H

#include <stdbool.h>
#include <stddef.h>

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef long long s64;
typedef int s32;
typedef short s16;
typedef char s8;

typedef volatile u64 vu64;
typedef volatile u32 vu32;
typedef volatile u16 vu16;
typedef volatile u8 vu8;

typedef volatile s64 vs64;
typedef volatile s32 vs32;
typedef volatile s16 vs16;
typedef volatile s8 vs8;

typedef u32 bool32;
typedef volatile bool32 vbool32;

#define ATTRIBUTE_ALIGN(x) __attribute__((aligned(x)))

#endif
