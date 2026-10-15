#include "nitro/fs.h"
#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/std.h"
#include "nitro/wm.h"

typedef struct FS_UnkStruct5 {
    /* 00 */ FSArchive *unk_00;
    /* 04 */ FSArchive *unk_04;
    /* 08 */ u16 unk_08;
    /* 0a */ u16 unk_0a;
    /* 0c */ u32 unk_0c;
    /* 10 */
} FS_UnkStruct5;

static s32 FS_func_0053(char *arg0, s32 arg1);
static s32 FS_func_0054(char *arg0);

static char FS_data_0004[FS_MAX_PATH];
static char sLongArchiveNames[0x10][0x10];
static FS_UnkStruct5 FS_data_0003;

FSArchive *FS_FindArchive(const char *name, u32 length) {
    OSIntrMode irq;
    char *archiveName;
    FSArchive *archive;

    irq = OS_DisableInterrupts();
    for (archive = FS_data_0003.unk_00; archive != NULL; archive = archive->next) {
        if (!!(archive->flags & FS_ARCHIVE_FLAG_0x2) == false) {
            continue;
        }
        archiveName = FSi_GetPackedName(archive);
        if (WM_func_0009(archiveName, name, length) == 0 && archiveName[length] == '\0') {
            break;
        }
    }
    OS_RestoreInterrupts(irq);
    return archive;
}

BOOL FS_func_0044(char *arg0) {
    char sp5C[FS_MAX_PATH];
    FSFile file;
    FSiCmd4 sp4;
    u32 sp0;
    BOOL result;
    FSArchive *archive;

    result  = false;
    sp0     = 0;
    archive = FS_func_0046(arg0, &sp0, &sp5C);
    if (archive != NULL) {
        FS_data_0003.unk_04 = archive;
        FS_data_0003.unk_08 = 0;
        FS_data_0003.unk_0a = 0;
        FS_data_0003.unk_0c = 0;
        WM_func_0007(&FS_data_0004, &sp5C, sizeof(FS_data_0004));
        if (archive->fns->unk_10 != NULL) {
            FS_InitFile(&file);
            file.archive  = archive;
            file.cmd.cmd4 = &sp4;
            sp4.unk_00    = sp0;
            sp4.path      = sp5C;
            sp4.unk_0c    = 1;
            if (FSi_SendCommand(&file, FS_CMD_4, true) != FS_RESULT_SUCCESS) {
                FS_data_0003.unk_08 = sp4.unk_08;
                WM_func_0007(&FS_data_0004, &sp5C, sizeof(FS_data_0004));
            }
        }
        result = true;
    }
    return result;
}

static s32 FS_func_0045(char *dst, s32 dstLen, const char *src, s32 srcLen, BOOL *arg4) {
    s32 i;
    s32 len;

    len = dstLen - 1;
    if (len >= srcLen) {
        len = srcLen;
    }
    for (i = 0; i < len && src[i] != '\0'; ++i) {
        dst[i] = src[i];
    }
    if (i < srcLen && src[i] != '\0') {
        *arg4 = true;
    }
    dst[i] = '\0';
    return i;
}

FSArchive *FS_func_0046(const char *path, u32 *arg1, char (*arg2)[FS_MAX_PATH]) {
    struct {
        FSArchive *unk_00;
        BOOL unk_04;
    } sp4;
    s32 temp_r0_3 = 0;
    BOOL wide;
    BOOL slash;
    s32 var_r6;
    s32 i;
    FSArchive *archive;
    const char *pathIter;
    u32 ch;
    u8 firstCh;
    u8 c;
    u8 temp_r1;

    var_r6     = 0;
    pathIter   = path;
    sp4.unk_04 = 0;
    if (FS_data_0003.unk_04 == NULL) {
        FS_data_0003.unk_04 = FS_data_0003.unk_00;
        FS_data_0003.unk_08 = 0U;
        FS_data_0003.unk_0c = 0;
        FS_data_0003.unk_0a = 0;
        FS_data_0004[0]     = '\0';
    }
    firstCh = *pathIter;
    if ((firstCh == '/') || (firstCh == '\\')) {
        pathIter += 1;
        sp4.unk_00 = FS_data_0003.unk_04;
        if (arg1 != NULL) {
            *arg1 = 0;
        }
    } else {
        i = 0;
        while (true) {
            c = pathIter[i];
            if (c == '\0' || c == '/' || c == '\\') {
                sp4.unk_00 = FS_data_0003.unk_04;
                if (arg1 != NULL) {
                    *arg1 = FS_data_0003.unk_08;
                }
                if (arg2 != NULL && FS_data_0003.unk_08 == 0 && FS_data_0004[0] != '\0') {
                    temp_r0_3 += FS_func_0045(*arg2, sizeof(*arg2), FS_data_0004, sizeof(FS_data_0004), &sp4.unk_04);
                    var_r6 =
                        temp_r0_3 + FS_func_0045(*arg2 + temp_r0_3, sizeof(*arg2) - temp_r0_3, "/", 1, &sp4.unk_04);
                }
                break;
            } else if (c == ':') {
                archive = FS_FindArchive(pathIter, i);
                pathIter += i + 1;
                temp_r1    = *pathIter;
                sp4.unk_00 = archive;
                if ((temp_r1 == '/') || (temp_r1 == '\\')) {
                    pathIter += 1;
                }
                if (arg1 != NULL) {
                    *arg1 = 0;
                }
                break;
            }

            wide = true;
            if (!STD_CHAR_IS_WIDE(c)) {
                wide = false;
            }
            i = i + 1 + wide;
        }
    }
    if (arg2 != NULL) {
        i = 0;
        while (sp4.unk_04 == 0) {
            ch = pathIter[i];
            if (ch != '\0') {
                slash = true;
                if ((u8) ch != '/' && (u8) ch != '\\') {
                    slash = false;
                }
                if (!slash) {
                    wide = false;
                    if (STD_CHAR_IS_WIDE(ch) && (pathIter[i + 1] != '\x7f') &&
                        ((u32) (u8) (pathIter[i + 1] - 0x40) <= 0xBCU)) {
                        wide = true;
                    }
                    i += wide ? 2 : 1;
                    continue;
                }
            }
            switch (i) {
                case 0:
                    break;
                case 1:
                    if (*pathIter == '.') {
                        break;
                    }
                    // fallthrough
                default:
                    if ((i == 2) && (pathIter[0] == '.') && (pathIter[1] == '.')) {
                        if (var_r6 > 0) {
                            var_r6 -= 1;
                        }
                        var_r6 = FS_func_0053(*arg2, var_r6) + 1;
                    } else {
                        var_r6 += FS_func_0045(*arg2 + var_r6, sizeof(*arg2) - var_r6, pathIter, i, &sp4.unk_04);
                        if (ch != 0) {
                            var_r6 += FS_func_0045(*arg2 + var_r6, sizeof(*arg2) - var_r6, "/", 1, &sp4.unk_04);
                        }
                    }
                    break;
            }
            if (ch == 0) {
                break;
            }
            pathIter += i + 1;
            i = 0;
        }
        (*arg2)[var_r6] = 0;
        FS_func_0054(*arg2);
    }
    if (sp4.unk_04 != 0) {
        sp4.unk_00 = NULL;
    }
    return sp4.unk_00;
}

void FS_InitArchive(FSArchive *archive) {
    MI_CpuFill8(archive, 0, sizeof(*archive));
    archive->unk_0c.tail = NULL;
    archive->unk_0c.head = NULL;
}

s32 FS_RegisterArchiveName(FSArchive *archive, const char *name, u32 length) {
    OSIntrMode irq;
    BOOL result;
    s32 var_r5_2;
    FSArchive **var_r1;
    char (*temp_r5)[0x10];
    FSArchive *var_r0;

    result = false;
    irq    = OS_DisableInterrupts();
    if (FS_FindArchive(name, length) == NULL) {
        var_r1 = &FS_data_0003.unk_00;
        var_r0 = FS_data_0003.unk_00;
        if (var_r0 != NULL) {
            do {
                var_r1 = &var_r0->next;
                var_r0 = var_r0->next;
            } while (var_r0 != NULL);
        }
        *var_r1 = archive;
        if (length <= 3) {
            archive->pName = NULL;
            WM_func_0007(archive->name, name, length + 1);
        } else if (length <= 15) {
            for (var_r5_2 = 0;; var_r5_2++) {
                if (var_r5_2 >= 16) {
                    OS_Panic();
                    continue;
                }

                if (sLongArchiveNames[var_r5_2][0] == '\0') {
                    temp_r5 = &sLongArchiveNames[var_r5_2];
                    WM_func_0007(temp_r5, name, length + 1);
                    archive->pName = *temp_r5;
                    break;
                }
            }

        } else {
            OS_Panic();
        }
        result = true;
        archive->flags |= FS_ARCHIVE_FLAG_0x1;
    }
    OS_RestoreInterrupts(irq);
    return result;
}

char *FSi_GetPackedName(FSArchive *archive) {
    char *name;

    name = archive->name;
    if (name[3] != '\0') {
        name = archive->pName;
    }
    return name;
}

BOOL FS_func_0049(FSArchive *archive, FS_UnkStruct7 *arg1, const FSArchiveFns *fns) {
    FSFile file;

    archive->unk_20 = arg1;
    archive->fns    = fns;
    FS_InitFile(&file);
    file.archive = archive;
    FSi_TranslateCommand(&file, FS_CMD_17);
    archive->flags |= FS_ARCHIVE_FLAG_0x2;
    return true;
}

void FS_NotifyArchiveAsyncEnd(FSArchive *archive, FSResult result) {
    FSFile *file;
    OSIntrMode irq;
    FSFile *cmd;

    file = archive->currentFile;
    if (file->flags & FS_FILE_FLAG_AWAIT_SYNC) {
        irq = OS_DisableInterrupts();
        file->flags |= FS_FILE_FLAG_0x8;
        file->unk_14 = result;
        OS_WakeupThread(&file->unk_18);
        OS_RestoreInterrupts(irq);
        return;
    }
    FSi_ReleaseCommand(file, result);
    cmd = FSi_NextCommand(archive, true);
    if (cmd != NULL) {
        FSi_ExecuteAsyncCommand(cmd);
    }
}

static s32 FS_func_0051(char *path, s32 arg1) {
    s32 var_r3;

    var_r3 = arg1 - 1;
    while ((var_r3 > 0) && STD_CHAR_IS_WIDE(path[var_r3 - 1])) {
        var_r3 -= 1;
    }
    arg1 -= 1;
    return arg1 - ((arg1 - var_r3) & 1);
}

s32 FS_func_0052(char *path, s32 start) {
    s32 index;
    BOOL wide;
    u32 temp_lr;

    index = start;
    while ((temp_lr = path[index]) != '\0' && (u8) temp_lr != '/' && (u8) temp_lr != '\\') {
        if (STD_CHAR_IS_WIDE(temp_lr)) {
            wide = true;
        } else {
            wide = false;
        }
        index = index + 1 + wide;
    }
    return index;
}

static s32 FS_func_0053(char *path, s32 arg1) {
    char ch;

    while (true) {
        arg1 = FS_func_0051(path, arg1);
        if (arg1 < 0) {
            break;
        }
        ch = path[arg1];
        if (ch == '/' || ch == '\\') {
            break;
        }
    }
    return arg1;
}

static s32 FS_func_0054(char *path) {
    s32 temp_r0;
    s32 var_r4;
    char ch;

    var_r4  = WM_func_0008();
    temp_r0 = FS_func_0051(path, var_r4);
    if (temp_r0 >= 0) {
        ch = path[temp_r0];
        if (ch == '/' || ch == '\\') {
            var_r4        = temp_r0;
            path[temp_r0] = '\0';
        }
    }
    return var_r4;
}
