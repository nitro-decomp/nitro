#include "nitro/fs.h"
#include "nitro/mi.h"
#include "nitro/os.h"

typedef struct FSUnkStruct1 {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 unk_04;
    /* 08 */
} FSUnkStruct1;

typedef struct FSUnkStruct4 {
    /* 00 */ s32 unk_00;
    /* 04 */ s32 unk_04;
    /* 08 */ s32 unk_08;
    /* 0c */ s32 unk_0c;
    /* 10 */ s32 unk_10;
    /* 14 */ s32 unk_14;
    /* 18 */
} FSUnkStruct4;

typedef struct FSUnkStruct6 {
    /* 00 */
} FSUnkStruct6;

BOOL FS_func_0005(FSFile *file);
BOOL FS_func_0006(FSFile *file);
BOOL FS_func_0007(FSFile *file);
BOOL FS_func_0008(FSFile *file);
BOOL FS_func_0009(FSFile *file);
BOOL FS_func_0010(FSFile *file);
BOOL FS_func_0011(FSFile *file);
BOOL FS_func_0012(FSFile *file);
BOOL FS_func_0013(FSFile *file);

static BOOL sFSInitialized;
static FSVolume *gFSVolumeHead;
static FSVolume *data_0216c10c;
static u16 data_0216c110;
static u16 data_0216c112;
static u32 data_0216c114;
static FSUnkStruct4 data_0216c11c;
static FSVolume gRomVolume;

static BOOL (*data_02091014[])(FSFile *file) = {
    FS_func_0005, FS_func_0006, FS_func_0007, FS_func_0008, FS_func_0009,
    FS_func_0010, FS_func_0011, FS_func_0012, FS_func_0013,
};

static void FS_AddRomVolume(u32);
static BOOL FS_func_0027(FSFile *file);

extern void func_0206bb2c(OSLinkedList *);
void FS_func_0001(FSFile *file, u32 param2) {
    u32 irq;
    s32 unk1;
    s32 *unk2;

    irq  = OS_DisableInterrupts_Irq();
    unk1 = file->unk_00;
    unk2 = file->unk_04;
    if (unk1 != 0) {
        *(s32 **) (unk1 + 4) = unk2;
    }
    if (unk2) {
        *unk2 = unk1;
    }
    file->unk_00 = 0;
    file->unk_04 = NULL;
    file->flags &= ~0x4f;
    file->unk_14 = param2;
    func_0206bb2c(&file->unk_18);
    OS_RestoreInterrupts(irq);
}

extern void func_0206badc(void *);
u32 FS_func_0002(FSFile *file, u8 param2) {
    s32 result;
    FSVolume *volume = file->volume;
    u32 mask         = 1 << param2;
    if (!!(file->flags & 4) != 0) {
        volume->flags |= 0x200;
    } else {
        volume->flags |= 0x100;
    }
    if ((volume->unk_58 & mask) != 0) {
        result = volume->unk_54(file, param2);
        switch (result) {
            case 0:
            case 1:
            case 4:
                file->unk_14 = result;
                break;
            case 8:
                volume->unk_58 &= ~mask;
                result = 7;
                break;
        }
    } else {
        result = 7;
    }
    if (result == 7) {
        result = data_02091014[param2](file);
    }
    if (result == 6) {
        if (!!(file->flags & 4) != 0) {
            u32 irq = OS_DisableInterrupts_Irq();
            while (!!(volume->flags & 0x200) != 0) {
                func_0206badc(&volume->unk_0c);
            }
            result = file->unk_14;
            OS_RestoreInterrupts(irq);
        }
    } else if (!!(file->flags & 4) == 0) {
        volume->flags &= ~0x100;
        FS_func_0001(file, result);
    } else {
        volume->flags &= ~0x200;
        file->unk_14 = result;
    }
    return result;
}

s32 FS_PathCompare(const char *lhs, const char *rhs, u32 length) {
    u32 i = 0;
    for (i = 0; i < length; i++) {
        u32 left  = (u8) lhs[i] - 'A';
        u32 right = (u8) rhs[i] - 'A';
        if (left <= 'Z' - 'A') {
            left += 'a' - 'A';
        }
        if (right <= 'Z' - 'A') {
            right += 'a' - 'A';
        }
        if (left != right) {
            return left - right;
        }
    }
    return 0;
}

s32 FS_func_0003(FSUnkStruct2 *param1, FSUnkStruct2 *param2, s32 param3) {
    u32 result;
    FSVolume *volume = param1->unk_00;
    volume->flags |= 0x200;
    result = volume->unk_50(volume, param2, param1->unk_04, param3);
    switch (result) {
        case 0:
        case 1:
            volume->flags &= ~0x200;
            break;
        case 6: {
            u32 irq = OS_DisableInterrupts_Irq();
            while (!!(volume->flags & 0x200) != 0) {
                func_0206badc(&volume->unk_0c);
            }
            OS_RestoreInterrupts(irq);
            result = *(u32 *) (volume->unk_24 + 0x14);
            break;
        }
    }
    param1->unk_04 += param3;
    return result;
}

u32 FS_func_0004(FSFile *file, u32 param2) {
    file->flags |= 4;
    file->buf      = file->volume;
    file->unk_38   = 0;
    file->unk_36_s = 0;
    file->unk_34_s = param2;
    return FS_func_0002(file, 2);
}

BOOL FS_func_0005(FSFile *file) {
    file->cursor += file->unk_38;
    return file->volume->unk_48(file->volume, file->buf, 0, 0);
}

BOOL FS_func_0006(FSFile *file) {
    file->cursor += file->unk_38;
    return file->volume->unk_4c(file->volume, file->buf, 0, 0);
}

BOOL FS_func_0007(FSFile *file) {
    s32 iVar1;
    FSVolume *puVar3;
    FSUnkStruct2 local_20;
    FSUnkStruct2 local_18;

    puVar3          = file->volume;
    local_20.unk_04 = puVar3->fnt + file->unk_38 * sizeof(FSFntDirectory);
    local_20.unk_00 = puVar3;
    iVar1           = FS_func_0003(&local_20, &local_18, 8);
    if (iVar1 == 0) {
        file->unk_20 = file->buf;
        if ((u32) * (u16 *) ((s32) &file->unk_34 + 2) == 0 && file->unk_38 == 0) {
            *(u16 *) ((s32) &file->unk_20 + 2) = local_18.unk_04;
            file->endRomOffset                 = (u8 *) (puVar3->fnt + (u32) local_18.unk_00);
        }
        file->cursor = (u8 *) (local_18.unk_06 & 0xfff);
    }
    return iVar1;
}

BOOL FS_func_0008(FSFile *file) {
    BOOL iVar1;
    FSUnkStruct3 *pFVar2;
    FSUnkStruct2 abStack_18;
    FSUnkStruct2 local_14;

    pFVar2          = file->buf;
    local_14.unk_00 = file->volume;
    local_14.unk_04 = file->unk_38;
    iVar1           = FS_func_0003(&local_14, &abStack_18, 1);
    if (iVar1 != 0) {
        return iVar1;
    }
    pFVar2->unk_10 = (u32) abStack_18.unk_00 & 0x7f;
    pFVar2->unk_0c = (s32) (u32) abStack_18.unk_00 >> 7;
    if (pFVar2->unk_10 != 0) {
        if (file->unk_34 == 0) {
            iVar1 = FS_func_0003(&local_14, (void *) &pFVar2->unk_14, 0);
            if (iVar1) {
                return iVar1;
            }
            ((s32 *) &pFVar2->unk_14)[pFVar2->unk_10] = 0;
        } else {
            local_14.unk_04 += pFVar2->unk_10;
        }
        if (pFVar2->unk_0c == 0) {
            pFVar2->volumeName                 = (u32) file->volume;
            pFVar2->unk_04                     = (u32) * (u16 *) ((s32) &file->unk_34 + 2);
            *(s16 *) ((s32) &file->unk_34 + 2) = *(s16 *) ((s32) &file->unk_34 + 2) + 1;
        } else {
            iVar1 = FS_func_0003(&local_14, &abStack_18, 2);
            if (iVar1) {
                return iVar1;
            }
            pFVar2->volumeName                   = (u32) file->volume;
            *(u16 *) &pFVar2->unk_04             = (u32) abStack_18.unk_00 & 0xfff;
            *(u16 *) ((s32) &pFVar2->unk_04 + 2) = 0;
            pFVar2->unk_08                       = 0;
        }
        file->unk_38 = local_14.unk_04;
        return false;
    }
    return true;
}

BOOL FS_func_0009(FSFile *file) {}

BOOL FS_func_0010(FSFile *file) {}

BOOL FS_func_0011(FSFile *file) {
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    FSUnkStruct2 iStack_18;
    FSUnkStruct2 iStack_20;

    iVar4 = file->volume;
    iVar2 = file->unk_34;
    iVar3 = iVar2 * 8;
    if (*(u32 *) (iVar4 + 0x30) <= (u32) (iVar3)) {
        return true;
    }
    iStack_20.unk_00 = file->volume;
    iStack_20.unk_04 = *(s32 *) (iStack_20.unk_00 + 0x2c) + iVar3;
    iVar1            = FS_func_0003(&iStack_20, &iStack_18, 8);
    if (!iVar1) {
        file->buf    = iStack_18.unk_00;
        file->unk_34 = iStack_18.unk_04;
        file->unk_38 = iVar2;
        return FS_func_0002(file, 7);
    }
    return iVar1;
}

BOOL FS_func_0012(FSFile *file) {
    file->startRomOffset = (u8 *) file->buf;
    file->cursor         = (u8 *) file->buf;
    file->endRomOffset   = file->buf;
    file->unk_20         = file->buf;
    return false;
}

BOOL FS_func_0013(FSFile *file) {
    return false;
}

u32 FS_GetPathVolumeName(const char *path, s32 length) {
    u32 volume = 0;
    if (length <= 3) {
        s32 i;
        for (i = 0; i < length; ++i) {
            u32 diff;
            u32 ch = path[i];
            if (ch == 0) {
                break;
            }
            diff = ch - 'A';
            if (diff <= 'Z' - 'A') {
                ch = diff + 'a';
            } else {
                ch = diff + 'A';
            }
            volume |= ch << (i * 8);
        }
    }
    return volume;
}

u32 FS_func_0014(FSFile *file, u8 *buf, u32 offset, u32 size) {
    MI_CpuCopy8(file->cursor + offset, buf, size);
    return 0;
}

u32 FS_func_0015(FSFile *file, u8 *buf, u32 offset, u32 size) {
    MI_CpuCopy8(buf, file->cursor + offset, size);
    return 0;
}

BOOL FS_func_0016(u32) {}
void FS_func_0017(FSFile *) {}

BOOL FS_func_0018(FSFile *file) {
    u32 uVar1 = FS_func_0002(file, file->unk_10);
    FS_func_0001(file, uVar1);
    if (FS_func_0016(file->volume)) {
        FS_func_0017(file);
    }
    return file->unk_14 == 0;
}

BOOL FS_func_0019(FSFile *file, u8 param2) {
    FSVolume *puVar1;
    FSVolume *it;
    FSVolume *volume;
    u32 irq;
    s32 iVar5;
    s32 *piVar6;
    u32 mask;

    volume       = file->volume;
    file->unk_10 = param2;
    file->unk_14 = 2;
    mask         = 1 << param2;
    file->flags |= 1;
    irq = OS_DisableInterrupts_Irq();
    if ((volume->flags & 0x80) != 0) {
        FS_func_0001(file, 3);
        OS_RestoreInterrupts(irq);
        return false;
    }
    if ((mask & 0x1fc) != 0) {
        file->flags |= 4;
    }
    iVar5  = file->unk_00;
    piVar6 = file->unk_04;
    if (iVar5 != 0) {
        *(s32 **) (iVar5 + 4) = piVar6;
    }
    if (piVar6 != (s32 *) 0x0) {
        *piVar6 = iVar5;
    }
    puVar1 = volume->prev;
    for (it = volume->unk_24; it != NULL; it = it->next) {
        puVar1 = it;
    }
    puVar1->next = (u32) file;
    file->unk_00 = (s32) puVar1;
    file->unk_04 = (s32 *) 0x0;
    if (!!(volume->flags & 8) == 0 && !!(volume->flags & 0x10) == 0) {
        volume->flags |= 0x10;
        OS_RestoreInterrupts(irq);
        if ((volume->unk_58 & 0x200) != 0) {
            volume->unk_54(file, 9);
        }
        irq         = OS_DisableInterrupts_Irq();
        file->flags = file->flags | 0x40;
        if (!!(file->flags & 4) == 0) {
            OS_RestoreInterrupts(irq);
            FS_func_0017(file);
            return true;
        }
        OS_RestoreInterrupts(irq);
    } else {
        if (!!(file->flags & 4) == 0) {
            OS_RestoreInterrupts(irq);
            return true;
        }
        do {
            func_0206badc((u8 *) &file->unk_18);
        } while ((file->flags & 0x40) == 0);
        OS_RestoreInterrupts(irq);
    }
    return FS_func_0018(file);
}

void FS_func_0020(FSVolume *unk) {
    MI_CpuFill8(unk, 0, sizeof(*unk));
    unk->unk_10 = 0;
    unk->unk_0c = 0;
    unk->unk_18 = 0;
    unk->unk_14 = 0;
}

FSVolume *FS_FindVolumeForPath(const char *path, u32 length) {
    u32 volumeName;
    FSVolume *volume;
    u32 irq;

    volumeName = FS_GetPathVolumeName(path, length);
    irq        = OS_DisableInterrupts_Irq();
    volume     = gFSVolumeHead;
    while (volume && volume->volumeName != volumeName) {
        volume = volume->next;
    }
    OS_RestoreInterrupts(irq);
    return volume;
}

BOOL FS_AddVolume(FSVolume *volume, const char *path, u32 length) {
    BOOL ret  = false;
    u32 uVar3 = OS_DisableInterrupts_Irq();
    if (!FS_FindVolumeForPath(path, length)) {
        if (gFSVolumeHead == NULL) {
            gFSVolumeHead = volume;
            data_0216c10c = volume;
            data_0216c114 = 0;
            data_0216c110 = 0;
            data_0216c112 = 0;
        } else {
            FSVolume *tail = gFSVolumeHead;
            FSVolume *it   = tail;
            while (it = it->next) {
                tail = it;
            }
            tail->next   = volume;
            volume->prev = tail;
        }
        volume->volumeName = FS_GetPathVolumeName(path, length);
        ret                = true;
        volume->flags |= 1;
    }
    OS_RestoreInterrupts(uVar3);
    return ret;
}

BOOL FS_InitVolume(FSVolume *volume, u32 param2, u32 fatRomOffset, u32 fatSize, u32 fntRomOffset, u32 fntSize,
                   u32 (*param7)(FSFile *file, u8 *buf, u32 offset, u32 size),
                   u32 (*param8)(FSFile *file, u8 *buf, u32 offset, u32 size)) {
    volume->unk_28       = param2;
    volume->fatSize      = fatSize;
    volume->fatRomOffset = fatRomOffset;
    volume->fat          = fatRomOffset;
    volume->fntSize      = fntSize;
    volume->fntRomOffset = fntRomOffset;
    volume->fnt          = fntRomOffset;
    volume->unk_48       = param7 ? param7 : (void *) FS_func_0014;
    volume->unk_4c       = param8 ? param8 : (void *) FS_func_0015;
    volume->unk_50       = volume->unk_48;
    volume->unk_44       = 0;
    volume->flags |= 2;
    return true;
}

void FS_func_0021(FSVolume *unk, u32 (*param2)(FSFile *, u32), u32 param3) {
    if (!param3) {
        param2 = NULL;
    } else if (!param2) {
        param3 = 0;
    }
    unk->unk_54 = param2;
    unk->unk_58 = param3;
}

void FS_func_0022(u32, u32) {}

void FS_Init(u32 dmaCount) {
    if (sFSInitialized) {
        return;
    }
    sFSInitialized = true;
    FS_AddRomVolume(dmaCount);
}

void FS_InitFile(FSFile *file) {
    file->unk_00      = 0;
    file->unk_04      = NULL;
    file->unk_18.tail = NULL;
    file->unk_18.head = NULL;
    file->volume      = 0;
    file->unk_10      = 0xe;
    file->flags       = 0;
}

BOOL FS_func_0023(FSFile *file, const char *path, FSUnkStruct1 *unk, u32 param4) {
    bool bVar2;
    s32 i;
    FSUnkStruct5 local_28;

    if (*path == '/' || *path == '\\') {
        local_28.volume = (void *) data_0216c10c;
        local_28.next   = NULL;
        local_28.prev   = NULL;
        path++;
    } else {
        local_28.volume = data_0216c10c;
        local_28.next   = data_0216c10c->next;
        local_28.prev   = data_0216c10c->prev;
        for (i = 0; i <= 3; ++i) {
            if (path[i] == '\0' || path[i] == '/' || path[i] == '\\') {
                break;
            }
            if (path[i] == ':') {
                local_28.volume = FS_FindVolumeForPath(path, i);
                if (local_28.volume == NULL) {
                    return false;
                }
                if (!!(local_28.volume->flags & 2) == 0) {
                    return false;
                }
                local_28.next = NULL;
                local_28.prev = NULL;
                path += i + 1;
                if (*path == '/' || *path == '\\') {
                    path++;
                }
                break;
            }
        }
    }
    file->volume = local_28.volume;
    file->unk_3c = path;
    file->buf    = &local_28;
    if (param4 != 0) {
        file->unk_40 = 1;
        file->unk_44 = param4;
    } else {
        file->unk_40 = 0;
        file->unk_44 = unk;
    }
    return FS_func_0019(file, 4);
}

u32 FS_func_0024(FSFile *file, void *buf, s32 size, u32 param4) {
    s32 iVar3   = size;
    u32 prevPos = file->cursor;
    s32 iVar1   = file->endRomOffset - prevPos;
    if (iVar3 > iVar1) {
        iVar3 = iVar1;
    }
    if (iVar3 < 0) {
        iVar3 = 0;
    }
    file->buf    = buf;
    file->unk_34 = size;
    file->unk_38 = iVar3;
    if (param4 == 0) {
        file->flags |= 4;
    }
    FS_func_0019(file, 0);
    if (param4 == 0) {
        if (FS_func_0027(file)) {
            iVar3 = file->cursor - prevPos;
        } else {
            iVar3 = -1;
        }
    }
    return iVar3;
}

BOOL FS_func_0025(FSUnkStruct1 *unk, const char *path) {
    FSFile file;
    FS_InitFile(&file);
    if (FS_func_0023(&file, path, unk, 0)) {
        return true;
    }
    return false;
}

BOOL FS_func_0026(FSFile *file, FSUnkStruct1 unk) {
    if (unk.unk_00 == 0) {
        return false;
    }
    file->volume = unk.unk_00;
    file->buf    = unk.unk_00;
    file->unk_34 = unk.unk_04;
    if (FS_func_0019(file, 6)) {
        file->flags = (file->flags | 0x10) & ~0x20;
        return true;
    }
    return false;
}

BOOL FS_OpenFile(FSFile *file, const char *path) {
    FSUnkStruct1 local_10;
    return FS_func_0025(&local_10, path) && FS_func_0026(file, local_10);
}

BOOL FS_CloseFile(FSFile *file) {
    if (!FS_func_0019(file, 8)) {
        return false;
    }
    file->volume = 0;
    file->unk_10 = 0xe;
    file->flags &= ~0x30;
    return true;
}

static BOOL FS_func_0027(FSFile *file) {
    BOOL unk1 = false;
    u32 irq;

    irq = OS_DisableInterrupts_Irq();
    if (!!(file->flags & 1) != 0) {
        unk1 = (file->flags & 0x44) == 0;
        if (unk1) {
            file->flags |= 4;
            do {
                func_0206badc(&file->unk_18);
            } while ((file->flags & 0x40) == 0);
        } else {
            do {
                func_0206badc(&file->unk_18);
            } while (!!(file->flags & 1) != 0);
        }
    }
    OS_RestoreInterrupts(irq);
    if (unk1) {
        return FS_func_0018(file);
    }
    return file->unk_14 == 0;
}

u32 FS_func_0028(FSFile *file, void *buf, u32 size) {
    return FS_func_0024(file, buf, size, 1);
}

u32 FS_ReadFile(FSFile *file, void *buf, u32 size) {
    return FS_func_0024(file, buf, size, 0);
}

BOOL FS_SeekFile(FSFile *file, s32 pos, u32 mode) {
    u8 *newPos;
    switch (mode) {
        case FS_SEEK_SET:
            newPos = file->startRomOffset + pos;
            break;
        case FS_SEEK_RELATIVE:
            newPos = file->cursor + pos;
            break;
        case FS_SEEK_END:
            newPos = file->endRomOffset + pos;
            break;
        default:
            return false;
    }
    if ((s32) newPos < (s32) file->startRomOffset) {
        newPos = file->startRomOffset;
    }
    if ((s32) newPos > (s32) file->endRomOffset) {
        newPos = file->endRomOffset;
    }
    file->cursor = newPos;
    return true;
}

extern s32 func_02073f88(void);
void FS_func_0029(u32 param1) {
    FS_func_0022(param1, func_02073f88() ? 5 : 0);
}

extern void func_02073bbc(FSUnkStruct4 *, u32, u32, u32, void (*)(u32), void *, u32);
u32 FS_func_0030(FSFile *file, u8 *buf, u32 offset, u32 size) {
    func_02073bbc(&data_0216c11c, offset, buf, size, FS_func_0029, file, 1);
    return 6;
}

u32 FS_func_0031(FSFile *file, u8 *buf, u32 offset, u32 size) {
    return 1;
}

extern void func_02072e50(u16);
extern void func_02072e34(u16);
u32 FS_func_0032(FSFile *param1, u32 param2) {
    switch (param2) {
        case 9:
            func_02072e34(data_0216c11c.unk_00);
            return 0;
        case 10:
            func_02072e50(data_0216c11c.unk_00);
            return 0;
        case 1:
            return 4;
        default:
            return 8;
    }
}

u32 FS_func_0033(FSFile *file, u8 *buf, u32 offset, u32 size) {
    return 1;
}

u32 FS_func_0034(FSFile *, u32) {
    return 4;
}

static void func_02073cb4(void);
static void FS_AddRomVolume(u32 dmaCount) {
    data_0216c11c.unk_04 = dmaCount;
    data_0216c11c.unk_00 = OS_GetLockID();
    data_0216c11c.unk_08 = 0;
    data_0216c11c.unk_0c = 0;
    data_0216c11c.unk_10 = 0;
    data_0216c11c.unk_14 = 0;
    func_02073cb4();
    FS_func_0020(&gRomVolume);
    FS_AddVolume(&gRomVolume, "rom", 3);
    if (REG_027FFC40 == 2) {
        data_0216c11c.unk_08 = -1;
        data_0216c11c.unk_0c = 0;
        data_0216c11c.unk_10 = -1;
        data_0216c11c.unk_14 = 0;
        FS_func_0021(&gRomVolume, FS_func_0034, -1);
        FS_InitVolume(&gRomVolume, 0, 0, 0, 0, 0, FS_func_0033, FS_func_0031);
    } else {
        FS_func_0021(&gRomVolume, FS_func_0032, 0x602);
        if (REG_FNT_ROM_OFFSET != -1 && REG_FNT_ROM_OFFSET != 0 && REG_FAT_ROM_OFFSET != -1 &&
            REG_FAT_ROM_OFFSET != 0) {
            FS_InitVolume(&gRomVolume, 0, REG_FAT_ROM_OFFSET, REG_FAT_SIZE, REG_FNT_ROM_OFFSET, REG_FNT_SIZE,
                          FS_func_0030, FS_func_0031);
        }
    }
}
