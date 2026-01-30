#ifndef _NITRO_MI_H
#define _NITRO_MI_H

#ifdef __cplusplus
extern "C" {
#endif

#define MI_DMA_MAX_NUM 3

typedef struct MI_UnkStruct2 {
    /* 00 */ u16 unk_00;
    /* 04 */ u32 unk_04;
    /* 08 */
} MI_UnkStruct2;

void MI_DmaFill32(u32, void *ptr, u8 value, u32 size);
void MI_DmaCopy16(u32, void *src, void *dst, u32 size);
void MI_DmaCopy32(u32, void *src, void *dst, u32 size);
BOOL MI_IsDmaBusy(u32);

void _MI_CpuFill(u8 value, void *ptr, u32 size);
void MI_CpuFill8(void *ptr, u8 value, u32 size);
void MI_CpuCopy8(void *src, void *dst, u32 size);
void MI_CpuFill32(u32 value, void *ptr, u32 size);

extern MI_UnkStruct2 data_020a7088;

inline void MI_CpuClearFast(void *ptr, u32 size) {
    _MI_CpuFill(0, ptr, size);
}

inline void MI_CpuFillFast(void *ptr, u8 value, u32 size) {
    _MI_CpuFill(value, ptr, size);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
