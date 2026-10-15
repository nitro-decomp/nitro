#ifndef _NITRO_STD_H
#define _NITRO_STD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include "nitro/types.h"

// `true` if this is the first byte of a wide character in the Shift JIS character set
#define STD_CHAR_IS_WIDE(ch) ((((u8) (ch) ^ 0x20) - 0xa1) < 0x3cu)

s32 STD_CompareNString(const char *src, const char *dst, s32 size);
s32 STD_CompareString(const char *src, const char *dst);
char *STD_CopyString(char *dst, const char *src);
s32 STD_CopyLString(char *dst, const char *src, s32 size);
const char *STD_SearchString(const char *src, const char *dst);
s32 STD_GetStringLength(const char *arg0);

s32 STD_TVSScanf(const char *buffer, const char *format, va_list args);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
