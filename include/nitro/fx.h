#ifndef _NITRO_FX_H
#define _NITRO_FX_H

#ifdef __cplusplus
extern "C" {
#endif

#define FX32_SHIFT 12
#define FX16_SHIFT 12

#define FX32_ONE (fx32)(1 << FX32_SHIFT)
#define FX16_ONE (fx16)(1 << FX16_SHIFT)

typedef s32 fx32;
typedef s16 fx16;

typedef struct VecFx32 {
    /* 00 */ fx32 x;
    /* 04 */ fx32 y;
    /* 08 */ fx32 z;
    /* 0c */
} VecFx32;

typedef struct MtxFx22 {
    /* 00 */ fx32 _00;
    /* 04 */ fx32 _01;
    /* 08 */ fx32 _10;
    /* 0c */ fx32 _11;
    /* 10 */
} MtxFx22;

void FX_Init(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
