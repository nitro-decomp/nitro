#ifndef _NITRO_TP_H
#define _NITRO_TP_H

#include "nitro/types.h"

#define TP_VALIDITY_VALID 0
#define TP_VALIDITY_INVALID_X 1
#define TP_VALIDITY_INVALID_Y 2
#define TP_VALIDITY_INVALID_XY 3

typedef struct {
    /* 00 */ s16 unk_00;
    /* 02 */ s16 unk_02;
    /* 04 */ s16 unk_04;
    /* 06 */ s16 unk_06;
    /* 08 */
} TPCalibrateParam;

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

void TP_Init(void);
BOOL TP_GetUserInfo(TPCalibrateParam *calibrate);
void TP_SetCalibrateParam(const TPCalibrateParam *calibrate);

void func_020711c0(void);
BOOL func_02071254(TPData *data);

inline BOOL TP_RequestRawSampling(TPData *data) {
    func_020711c0();
    return func_02071254(data);
}

void TP_GetCalibratedPoint(TPData *, TPData *);

#endif
