#ifndef _NITRO_FS_H
#define _NITRO_FS_H

#include "nitro/os.h"
#include "nitro/types.h"

#define FS_SEEK_SET 0
#define FS_SEEK_RELATIVE 1
#define FS_SEEK_END 2

#define FS_FILE_FLAG_FILE 0x10

struct FSVolume;
typedef struct FSUnkStruct2 {
    /* 00 */ struct FSVolume *unk_00;
    /* 04 */ s16 unk_04;
    /* 06 */ u16 unk_06;
    /* 08 */
} FSUnkStruct2;

typedef struct FSUnkStruct5 {
    /* 00 */ struct FSVolume *volume;
    /* 04 */ struct FSVolume *next;
    /* 08 */ struct FSVolume *prev;
    /* 0c */
} FSUnkStruct5;

struct FSFile;
typedef struct FSVolume {
    /* 00 */ u32 volumeName;
    /* 04 */ struct FSVolume *next;
    /* 08 */ struct FSVolume *prev;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
    /* 18 */ u32 unk_18;
    /* 1c */ vu32 flags;
    /* 20 */ u32 unk_20;
    /* 24 */ struct FSVolume *unk_24;
    /* 28 */ u32 unk_28;
    /* 2c */ u32 *fat;
    /* 30 */ u32 fatSize;
    /* 34 */ u8 *fnt;
    /* 38 */ u32 fntSize;
    /* 3c */ u32 fatRomOffset;
    /* 40 */ u32 fntRomOffset;
    /* 44 */ u32 *unk_44;
    /* 48 */ BOOL (*unk_48)(struct FSVolume *, u32, u32, u32);
    /* 4c */ BOOL (*unk_4c)(struct FSVolume *, u32, u32, u32);
    /* 50 */ BOOL (*unk_50)(struct FSVolume *, u32, u32, u32);
    /* 54 */ u32 (*unk_54)(struct FSFile *, u32);
    /* 58 */ u32 unk_58;
    /* 5c */
} FSVolume;

typedef struct FSUnkStruct3 {
    /* 00 */ u32 volumeName;
    /* 04 */ u32 unk_04;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u8 unk_14[0x94 - 0x14];
    /* 94 */
} FSUnkStruct3;

typedef struct FSUnkStruct7 {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 unk_04;
    /* 08 */ u32 unk_08;
    /* 0c */
} FSUnkStruct7;

typedef struct FSFile {
    /* 00 */ u32 unk_00;
    /* 04 */ s32 *unk_04;
    /* 08 */ FSVolume *volume;
    /* 0c */ vu32 flags;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
    /* 18 */ OS_UnkStruct1 unk_18;
    /* 20 */ u32 unk_20;
    /* 24 */ u32 startRomOffset;
    /* 28 */ u32 endRomOffset;
    /* 2c */ u32 cursor;
    /* 30 */ u32 buf;
    union {
        /* 34 */ u32 unk_34;
        struct {
            /* 34 */ u16 unk_34_s;
            /* 36 */ u16 unk_36_s;
        };
    };
    /* 38 */ u16 unk_38;
    /* 3c */ u32 unk_3c;
    /* 40 */ u32 unk_40;
    /* 44 */ u32 unk_44;
    /* 48 */
} FSFile;

typedef struct FSFntDirectory {
    /* 00 */ u32 subtableOffset;
    /* 04 */ u16 firstFileId;
    /* 06 */ u16 parentId;
    /* 08 */
} FSFntDirectory;

void FS_Init(u32 dmaCount);
void FS_InitFile(FSFile *file);
BOOL FS_OpenFile(FSFile *file, const char *path);
BOOL FS_SeekFile(FSFile *file, s32 pos, u32 mode);
u32 FS_ReadFile(FSFile *file, void *buf, u32 size);
inline BOOL FS_IsFile(FSFile *file) {
    return !!(file->flags & FS_FILE_FLAG_FILE);
}
BOOL FS_CloseFile(FSFile *file);

#endif
