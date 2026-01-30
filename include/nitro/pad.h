#ifndef _NITRO_PAD_H
#define _NITRO_PAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/reg.h"
#include "nitro/types.h"

#define PAD_BUTTON_A 0x1
#define PAD_BUTTON_B 0x2
#define PAD_BUTTON_SELECT 0x4
#define PAD_BUTTON_START 0x8
#define PAD_KEY_RIGHT 0x10
#define PAD_KEY_LEFT 0x20
#define PAD_KEY_UP 0x40
#define PAD_KEY_DOWN 0x80
#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800

#define PAD_BUTTON_ALL                                                                                                 \
    (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_SELECT | PAD_BUTTON_START | PAD_BUTTON_R | PAD_BUTTON_L | PAD_BUTTON_X | \
     PAD_BUTTON_Y)

#define PAD_KEY_ALL (PAD_KEY_RIGHT | PAD_KEY_LEFT | PAD_KEY_UP | PAD_KEY_DOWN)

#define PAD_ALL (PAD_BUTTON_ALL | PAD_KEY_ALL)

inline BOOL PAD_DetectFold(void) {
    return (REG_PAD & 0x8000) >> 0xf;
}

inline u16 PAD_Read(void) {
    return ((REG_KEYINPUT | REG_PAD) ^ 0x2fff) & 0x2fff;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
