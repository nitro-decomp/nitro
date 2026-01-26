#ifndef _NITRO_FX_H
#define _NITRO_FX_H

#define FX32_ONE (fx32)(1 << 12)

typedef u32 fx32;

typedef struct {
    /* 00 */ fx32 _00;
    /* 04 */ fx32 _01;
    /* 08 */ fx32 _10;
    /* 0c */ fx32 _11;
    /* 10 */
} MtxFx22;

void FX_Init(void);

#endif
