# Name sources
This table outlines the source of every symbol/macro name used in this decompilation. Some are found inside other games and libraries, others are made up (blank in the Source column).

| Symbol | Type | Source | Note |
|--------|------|--------|------|
| CARD_BACKUP_TYPE_NOT_USE         | Macro | GameSpy
| CARD_BACKUP_TYPE_EEPROM          | Macro | pm4 | Deduced from CARD_BACKUP_TYPE_EEPROM_4KBITS
| CARD_BACKUP_TYPE_FLASH           | Macro | pm4 | Deduced from CARD_BACKUP_TYPE_FLASH_2MBITS
| CARD_BACKUP_TYPE_FRAM            | Macro | pm4 | Deduced from CARD_BACKUP_TYPE_FRAM_256KBITS
| CARD_BACKUP_TYPE_EEPROM_4KBITS   | Macro | pm4, GameSpy
| CARD_BACKUP_TYPE_EEPROM_64KBITS  | Macro | pm4, GameSpy
| CARD_BACKUP_TYPE_EEPROM_512KBITS | Macro | pm4, GameSpy
| CARD_BACKUP_TYPE_FLASH_2MBITS    | Macro | pm4, GameSpy
| CARD_BACKUP_TYPE_FLASH_4MBITS    | Macro | pm4
| CARD_BACKUP_TYPE_FLASH_8MBITS    | Macro | pm4
| CARD_BACKUP_TYPE_FRAM_256KBITS   | Macro | pm4, GameSpy
||
| CARD_RESULT_SUCCESS       | Macro | pm4
| CARD_RESULT_FAILURE       | Macro | pm4, gtpd
| CARD_RESULT_INVALID_PARAM | Macro | pm4
| CARD_RESULT_UNSUPPORTED   | Macro | pm4
| CARD_RESULT_TIMEOUT       | Macro | pm4
| CARD_RESULT_CANCELED      | Macro | pm4
| CARD_RESULT_NO_RESPONSE   | Macro | pm4
| CARD_RESULT_ERROR         | Macro | pm4
||
| CARDBackupType | Typedef | pm4, GameSpy
| CARDResult     | Typedef | pm4
||
| CARD_LockBackup                | Function | pm4, GameSpy
| CARD_UnlockBackup              | Function | pm4, GameSpy
| CARD_IdentifyBackup            | Function | pm4, GameSpy
| CARD_GetBackupType             | Function | pm4
| CARD_IsBackupEeprom            | Macro | pm4, GameSpy
| CARD_IsBackupFlash             | Macro | pm4, GameSpy
| CARD_IsBackupFram              | Macro | pm4, GameSpy
| CARD_GetBackupTotalSize        | Function | GameSpy
| CARD_ReadWriteBackupAsync      | Function
| CARD_WaitBackupAsync           | Function | pm4
| CARD_GetResultCode             | Function | pm4, GameSpy
| CARD_ReadEeprom                | Function | GameSpy
| CARD_ReadFlash                 | Function | GameSpy
| CARD_ReadFram                  | Function | GameSpy
| CARD_WriteAndVerifyEeprom      | Function | GameSpy
| CARD_WriteAndVerifyFlash       | Function | GameSpy
| CARD_WriteAndVerifyFram        | Function | GameSpy
| CARD_ReadEepromAsync           | Function | pm4
| CARD_ReadFlashAsync            | Function | pm4
| CARD_ReadFramAsync             | Function | pm4
| CARD_WriteAndVerifyEepromAsync | Function | pm4
| CARD_WriteAndVerifyFlashAsync  | Function | pm4
| CARD_WriteAndVerifyFramAsync   | Function | pm4
||
| CP_SaveContext     | Function | gtact
| CPi_RestoreContext | Function | gtact
||
| DC_StoreAll         | Function | pm4
| DC_StoreRange       | Function | pm4
| DC_FlushAll         | Function | pm4
| DC_FlushRange       | Function | pm4
| DC_InvalidateAll    | Function
| DC_InvalidateRange  | Function | diamondtrust
| DC_DrainWriteBuffer | Function
||
| FS_SEEK_SET | Macro | pm4, diamondtrust
| FS_SEEK_CUR | Macro | pm4
| FS_SEEK_END | Macro | gtpd
||
| FS_FILE_FLAG_FILE | Macro
||
| FS_FILEMODE_R | Macro | diamondtrust
||
| FSVolume       | Struct
| FSFile         | Struct | pm4, diamondtrust
| FSFntDirectory | Struct
| FSDirEntry     | Struct | diamondtrust
||
| FS_Init       | Function | pm4, diamondtrust
| FS_InitFile   | Function | pm4, diamondtrust
| FS_OpenFile   | Function | pm4
| FS_OpenFileEx | Function | diamondtrust
| FS_SeekFile   | Function | pm4, diamondtrust
| FS_GetLength  | Function | diamondtrust, gtpd
| FS_ReadFile   | Function | pm4, diamondtrust
| FS_CloseFile  | Function | pm4, diamondtrust
| FS_IsFile     | Function | pm4
||
| FS_FindDir | Function | diamondtrust
| FS_ReadDir | Function | diamondtrust
| FS_CloseDirectory | Function | diamondtrust
||
| FX32_SHIFT | Macro | diamondtrust, gtpd, gs456
| FX16_SHIFT | Macro | diamondtrust, gtpd
||
| FX32_ONE | Macro | pm4, diamondtrust, gtpd, gs456
| FX16_ONE | Macro | diamondtrust, gtpd
||
| fx32 | Typedef | gtpd
| fx16 | Typedef | gtpd
||
| VecFx32 | Struct | diamondtrust, gtpd
| MtxFx22 | Struct | pm4, gtpd
||
| FX_Init | Function | pm4, diamondtrust
||
| G2_SetBGAffine | Function | pm4 | Deduced from G2_SetBG2Affine and G2_SetBG3Affine
||
| _G2_SetBlend | Function
||
| G2_GetBG2ScrPtr | Function | pm4
| G2_GetBG3ScrPtr | Function | pm4
||
| G2_SetBG0Priority  | Function | pm4, diamondtrust
| G2_SetBG1Priority  | Function | pm4
| G2_SetBG2Priority  | Function | pm4
| G2_SetBG3Priority  | Function | pm4
| G2S_SetBG0Priority | Function | pm4
| G2S_SetBG1Priority | Function | pm4
| G2S_SetBG2Priority | Function | pm4, diamondtrust
| G2S_SetBG3Priority | Function | pm4
||
| G2_SetBG0Offset  | Function | pm4
| G2_SetBG1Offset  | Function | pm4
| G2_SetBG2Offset  | Function | pm4
| G2_SetBG3Offset  | Function | pm4
| G2S_SetBG0Offset | Function | pm4
| G2S_SetBG1Offset | Function | pm4
| G2S_SetBG2Offset | Function | pm4
| G2S_SetBG3Offset | Function | pm4
||
| G2_SetBG0Control        | Function | pm4
| G2_SetBG1Control        | Function | pm4
| G2_SetBG2Control        | Function | pm4 | Deduced from G2_SetBG2ControlText and similarly named functions
| G2_SetBG3Control        | Function | pm4 | Deduced from G2_SetBG3ControlText and similarly named functions
| G2S_SetBG0Control       | Function | pm4
| G2S_SetBG1Control       | Function | pm4
| G2S_SetBG2Control       | Function | pm4 | Deduced from G2S_SetBG2ControlText and similarly named functions
| G2S_SetBG3Control       | Function | pm4 | Deduced from G2S_SetBG3ControlText and similarly named functions
| G2_SetBG2Control256Bmp  | Function | pm4
| G2_SetBG3Control256Bmp  | Function | pm4
| G2S_SetBG2Control256Bmp | Function | pm4
| G2S_SetBG3Control256Bmp | Function | pm4
| G2_SetBG2ControlDCBmp   | Function | pm4
| G2_SetBG3ControlDCBmp   | Function | pm4
| G2S_SetBG2ControlDCBmp  | Function | pm4, diamondtrust
| G2S_SetBG3ControlDCBmp  | Function | pm4
| G2_SetBG2ControlText    | Function | pm4
| G2_SetBG3ControlText    | Function | pm4
| G2S_SetBG2ControlText   | Function | pm4
| G2S_SetBG3ControlText   | Function | pm4
||
| G2_SetBG2Affine | Function | pm4
| G2_SetBG3Affine | Function | pm4
||
| G2_ChangeBlendAlpha  | Function | pm4
| G2S_ChangeBlendAlpha | Function | pm4
||
| G2_BG0Mosaic         | Function | pm4
| G2_BG1Mosaic         | Function | pm4
| G2_BG2Mosaic         | Function | pm4
| G2_BG3Mosaic         | Function | pm4
| G2S_BG0Mosaic        | Function | pm4
| G2S_BG1Mosaic        | Function | pm4
| G2S_BG2Mosaic        | Function | pm4, diamondtrust
| G2S_BG3Mosaic        | Function | pm4
| G2_SetBGMosaicSize   | Function | pm4
| G2S_SetBGMosaicSize  | Function | pm4
| G2S_SetOBJMosaicSize | Function | pm4
||
| G2_BlendNone      | Function | pm4
| G2S_BlendNone     | Function | pm4
| G2_SetBlendAlpha  | Function | pm4
| G2S_SetBlendAlpha | Function | pm4, diamondtrust
||
| G2_GetOBJPosition   | Function | pm4
| G2_SetOBJPosition   | Function | pm4
| G2_GetOBJCharName   | Function | pm4
| G2_SetOBJCharName   | Function | pm4
| G2_GetOBJColorParam | Function | pm4
| G2_GetOBJMode       | Function | pm4
| G2_SetOBJMode       | Function | pm4
| G2_SetOBJPriority   | Function | pm4, gtpd
| G2_SetOBJAttr       | Function | diamondtrust, gtpd
||
| G3OP_TEXCOORD | Macro | diamondtrust
||
| G3X_Init          | Function | diamondtrust
| G3X_InitTable     | Function | diamondtrust
| G3X_InitMtxStack  | Function | diamondtrust
| G3X_Reset         | Function | diamondtrust
| G3X_SetClearColor | Function | diamondtrust
||
| G3_TexImageParam | Function | diamondtrust
| G3_TexPlttBase   | Function | diamondtrust
| G3_PolygonAttr   | Function | diamondtrust
||
| G3_PushMtx   | Function | diamondtrust
| G3_Translate | Function | diamondtrust
| G3_ViewPort  | Function | diamondtrust
| _G3_Ortho    | Function | diamondtrust | Deduced from G3_Ortho
| G3_Ortho     | Function | diamondtrust
| G3_StoreMtx  | Function | diamondtrust
| _G3_LookAt   | Function | diamondtrust | Deduced from G3_LookAt
| G3_LookAt    | Function | diamondtrust
| G3_MtxMode   | Function | diamondtrust
| G3_Identity  | Function | diamondtrust
| G3_PopMtx    | Function | diamondtrust
||
| G3_Begin   | Function | diamondtrust
| G3_Color   | Function | diamondtrust
| G3_Direct1 | Function | diamondtrust
| G3_Vtx     | Function | diamondtrust
| G3_End     | Function | diamondtrust
||
| G3_SwapBuffers     | Function | diamondtrust
| G3X_IsGeometryBusy | Function | diamondtrust
||
| G3X_AntiAlias | Function | diamondtrust
| G3X_AlphaBlend | Function | diamondtrust
||
| GX_POWER_ALL | Macro | pm4
||
| GX_DISP_SELECT_MAIN_SUB | Macro | pm4
| GX_DISP_SELECT_SUB_MAIN | Macro | pm4
| GX_DISPMODE_GRAPHICS    | Macro | pm4
| GX_DISPMODE_VRAM_C      | Macro | diamondtrust
| GX_DISPMODE_VRAM_D      | Macro | diamondtrust
||
| GX_VRAM_LCDC_ALL | Macro | pm4
| GX_VRAM_LCDC_C   | Macro | diamondtrust
| GX_VRAM_LCDC_D   | Macro | diamondtrust
||
| GX_VRAM_BG_NONE     | Macro | pm4
| GX_VRAM_BG_128_A    | Macro | pm4
| GX_VRAM_BG_128_B    | Macro | pm4
| GX_VRAM_BG_128_C    | Macro | pm4
| GX_VRAM_BG_128_D    | Macro | pm4
| GX_VRAM_BG_256_AB   | Macro | pm4
| GX_VRAM_BG_384_ABC  | Macro | pm4
| GX_VRAM_BG_384_ABD  | Macro | pm4
| GX_VRAM_BG_512_ABCD | Macro | pm4
||
| GX_VRAM_SUB_BG_NONE  | Macro | pm4
| GX_VRAM_SUB_BG_32_H  | Macro | pm4
| GX_VRAM_SUB_BG_48_HI | Macro | pm4
| GX_VRAM_SUB_BG_128_C | Macro | pm4
||
| GX_VRAM_OBJ_NONE  | Macro | pm4
| GX_VRAM_OBJ_128_A | Macro | pm4
| GX_VRAM_OBJ_128_B | Macro | pm4
| GX_VRAM_OBJ_128_C | Macro
| GX_VRAM_OBJ_128_D | Macro
| GX_VRAM_OBJ_64_E  | Macro | pm4
| GX_VRAM_OBJ_16_F  | Macro | pm4
| GX_VRAM_OBJ_16_G  | Macro | pm4
||
| GX_VRAM_SUB_OBJ_NONE  | Macro | pm4
| GX_VRAM_SUB_OBJ_16_I  | Macro | pm4
| GX_VRAM_SUB_OBJ_128_D | Macro | pm4
||
| GX_VRAM_BGEXTPLTT_01_F       | Macro | pm4
| GX_VRAM_BGEXTPLTT_0123_FG    | Macro | pm4
| GX_VRAM_SUB_BGEXTPLTT_0123_H | Macro | pm4
| GX_VRAM_SUB_OBJEXTPLTT_0_I   | Macro | pm4
| GX_VRAM_OBJEXTPLTT_0_F       | Macro | pm4
| GX_VRAM_OBJEXTPLTT_0_G       | Macro | pm4
||
| GX_VRAM_TEX_01_AB | Macro | diamondtrust
||
| GX_VRAM_TEXPLTT_0123_E | Macro | diamondtrust
||
| GX_PLANEMASK_NONE | Macro | diamondtrust
| GX_PLANEMASK_BG0  | Macro | diamondtrust
| GX_PLANEMASK_BG1  | Macro | diamondtrust
| GX_PLANEMASK_BG2  | Macro | diamondtrust
| GX_PLANEMASK_BG3  | Macro | diamondtrust
| GX_PLANEMASK_OBJ  | Macro | diamondtrust
||
| GX_BGCHAROFFSET_0x00000      | Macro | pm4
| GX_BGSCROFFSET_0x00000       | Macro | pm4
| GX_BGMODE_0                  | Macro | pm4
| GX_BGMODE_3                  | Macro | pm4
| GX_BGMODE_5                  | Macro | pm4
| GX_BG0_AS_2D                 | Macro | pm4
| GX_BG_SCRSIZE_TEXT_256x256   | Macro | pm4
| GX_BG_SCRSIZE_256BMP_128x128 | Macro | pm4
| GX_BG_SCRSIZE_256BMP_256x256 | Macro | pm4
| GX_BG_SCRSIZE_256BMP_512x256 | Macro | pm4
| GX_BG_SCRSIZE_256BMP_512x512 | Macro | pm4
| GX_BG_SCRSIZE_DCBMP_128x128  | Macro | pm4
| GX_BG_SCRSIZE_DCBMP_256x256  | Macro | pm4
| GX_BG_SCRSIZE_DCBMP_512x256  | Macro | pm4
| GX_BG_SCRSIZE_DCBMP_512x512  | Macro | pm4
| GX_BG_AREAOVER_XLU           | Macro | pm4
| GX_BG_AREAOVER_REPEAT        | Macro | pm4
| GX_BG_BMPSCRBASE_0x00000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x04000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x08000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x0c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x10000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x14000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x18000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x1c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x20000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x24000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x28000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x2c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x30000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x34000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x38000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x3c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x40000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x44000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x48000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x4c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x50000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x54000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x58000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x5c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x60000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x64000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x68000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x6c000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x70000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x74000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x78000     | Macro | pm4
| GX_BG_BMPSCRBASE_0x7c000     | Macro | pm4
| GX_BG_COLORMODE_16           | Macro | pm4
| GX_BG_CHARBASE_0x00000       | Macro | pm4
| GX_BG_SCRBASE_0x0000         | Macro | pm4
| GX_BG_EXTPLTT_01             | Macro | pm4
||
| GX_OBJVRAMMODE_CHAR_1D_32K  | Macro | pm4
| GX_OBJVRAMMODE_CHAR_1D_64K  | Macro | pm4
| GX_OBJVRAMMODE_CHAR_1D_128K | Macro | pm4
| GX_OBJVRAMMODE_CHAR_1D_256K | Macro | pm4
||
| GX_BLEND_PLANEMASK_NONE | Macro | pm4
| GX_BLEND_PLANEMASK_BG0  | Macro | pm4, diamondtrust
| GX_BLEND_PLANEMASK_BG1  | Macro | pm4, diamondtrust
| GX_BLEND_PLANEMASK_BG2  | Macro | pm4, diamondtrust
| GX_BLEND_PLANEMASK_BG3  | Macro | pm4, diamondtrust
| GX_BLEND_PLANEMASK_OBJ  | Macro | pm4, diamondtrust
| GX_BLEND_PLANEMASK_BD   | Macro | pm4, diamondtrust
||
| GX_OAM_MODE_XLU       | Macro | pm4
| GX_OAM_MODE_BITMAPOBJ | Macro | diamondtrust
||
| GX_OAM_EFFECT_NONE | Macro | diamondtrust
||
| GX_OAM_SHAPE_64x64 | Macro | diamondtrust
||
| GX_OAM_COLOR_16 | Macro | diamondtrust
||
| GX_TEXSIZE_S8    | Macro | diamondtrust
| GX_TEXSIZE_S16   | Macro | diamondtrust
| GX_TEXSIZE_S32   | Macro | diamondtrust
| GX_TEXSIZE_S64   | Macro | diamondtrust
| GX_TEXSIZE_S128  | Macro | diamondtrust
| GX_TEXSIZE_S256  | Macro | diamondtrust
| GX_TEXSIZE_S512  | Macro | diamondtrust
| GX_TEXSIZE_S1024 | Macro | diamondtrust
| GX_TEXSIZE_T8    | Macro | diamondtrust
| GX_TEXSIZE_T16   | Macro | diamondtrust
| GX_TEXSIZE_T32   | Macro | diamondtrust
| GX_TEXSIZE_T64   | Macro | diamondtrust
| GX_TEXSIZE_T128  | Macro | diamondtrust
| GX_TEXSIZE_T256  | Macro | diamondtrust
| GX_TEXSIZE_T512  | Macro | diamondtrust
| GX_TEXSIZE_T102  | Macro | diamondtrust
||
| GX_TEXFMT_NONE    | Macro | diamondtrust
| GX_TEXFMT_PLTT4   | Macro | diamondtrust
| GX_TEXFMT_PLTT16  | Macro | diamondtrust
| GX_TEXFMT_PLTT256 | Macro | diamondtrust
| GX_TEXFMT_DIRECT  | Macro | diamondtrust
||
| GX_TEXPLTTCOLOR0_USE  | Macro | diamondtrust
| GX_TEXPLTTCOLOR0_TRNS | Macro | diamondtrust
||
| GX_TEXGEN_NONE     | Macro | diamondtrust
| GX_TEXGEN_TEXCOORD | Macro | diamondtrust
||
| GX_TEXREPEAT_NONE | Macro | diamondtrust
||
| GX_TEXFLIP_NONE | Macro | diamondtrust
||
| GX_LIGHTMASK_NONE | Macro | diamondtrust
||
| GX_POLYGONMODE_MODULATE | Macro | diamondtrust
||
| GX_CULL_NONE | Macro | diamondtrust
||
| GX_BEGIN_QUADS | Macro | diamondtrust
||
| GX_RGB | Macro | diamondtrust
||
| GX_CAPTURE_SIZE_256x192        | Macro | diamondtrust
| GX_CAPTURE_MODE_A              | Macro | diamondtrust
| GX_CAPTURE_SRCA_2D3D           | Macro | diamondtrust
| GX_CAPTURE_DEST_VRAM_C_0x00000 | Macro | diamondtrust
| GX_CAPTURE_DEST_VRAM_D_0x00000 | Macro | diamondtrust
||
| GX_SORTMODE_MANUAL | Macro | diamondtrust
||
| GX_BUFFERMODE_Z | Macro | diamondtrust
||
| GX_MTXMODE_POSITION_VECTOR | Macro | diamondtrust
| GX_MTXMODE_TEXTURE         | Macro | diamondtrust
||
| GXVRamBG  | Typedef | pm4
| GXVRamOBJ | Typedef | pm4
||
| GXOamAttr         | Struct  | pm4
| GXOamMode         | Typedef | pm4
| GXBGScrSize256Bmp | Typedef | pm4
| GXBGScrSizeDcBmp  | Typedef | pm4
| GXBGAreaOver      | Typedef | pm4
| GXBGBmpScrBase    | Typedef | pm4
| GXBGScrSizeText   | Typedef | pm4
| GXBGColorMode     | Typedef | pm4
| GXBGScrBase       | Typedef | pm4
| GXBGCharBase      | Typedef | pm4
||
| GXOBJVRamModeChar | Typedef | pm4
||
| GXTexFmt   | Typedef | diamondtrust
| GXTexSizeS | Typedef | diamondtrust
| GXTexSizeT | Typedef | diamondtrust
| GXSt       | Typedef | diamondtrust
||
| GX_ST      | Macro | diamondtrust
||
| GXTexPlttColor0 | Typedef | diamondtrust
| GXCaptureSrcB | Typedef | diamondtrust
||
| GX_Init        | Function | pm4, diamondtrust
| GX_InitGXState | Function | gtact
| GX_DispOff     | Function | pm4, diamondtrust
| GX_DispOn      | Function | pm4, diamondtrust
||
| GX_VBlankIntr | Function | pm4, diamondtrust
| GX_HBlankIntr | Function | pm4
||
| GX_VRAMCNT_SetLCDC_ | Function | gtact
||
| GX_SetBankForLCDC | Function | pm4, diamondtrust
| GX_DisableBankForLCDC | Function | pm4, diamondtrust
| GX_SetBankForBG | Function | pm4
| GX_SetBankForOBJ | Function | pm4
| GX_SetBankForSubBG | Function | pm4, diamondtrust
| GX_SetBankForSubOBJ | Function | pm4, diamondtrust
| GX_SetBankForTex | Function | diamondtrust
| GX_SetBankForTexPltt | Function | diamondtrust
| GX_SetGraphicsMode | Function | pm4, diamondtrust
| GXS_SetGraphicsMode | Function | pm4, diamondtrust
||
| GX_LoadOAM | Function | pm4
| GXS_LoadOAM | Function | pm4, diamondtrust
||
| GX_LoadBG0Char  | Function | pm4
| GX_LoadBG0Scr   | Function | pm4
| GX_LoadBG1Char  | Function | pm4
| GX_LoadBG1Scr   | Function | pm4
| GX_LoadBG2Bmp   | Function | pm4
| GX_LoadBG2Char  | Function | pm4
| GX_LoadBG2Scr   | Function | pm4
| GX_LoadBG3Bmp   | Function | pm4
| GX_LoadBG3Char  | Function | pm4
| GX_LoadBG3Scr   | Function | pm4
| GXS_LoadBG0Char | Function | pm4
| GXS_LoadBG0Scr  | Function | pm4
| GXS_LoadBG1Char | Function | pm4
| GXS_LoadBG1Scr  | Function | pm4
| GXS_LoadBG2Bmp  | Function | pm4
| GXS_LoadBG2Char | Function | pm4
| GXS_LoadBG2Scr  | Function | pm4
| GXS_LoadBG3Bmp  | Function | pm4
| GXS_LoadBG3Char | Function | pm4
| GXS_LoadBG3Scr  | Function | pm4
| GX_LoadBGPltt   | Function | pm4
| GX_LoadOBJPltt  | Function | pm4
| GXS_LoadBGPltt  | Function | pm4
| GXS_LoadOBJPltt | Function | pm4
| GX_LoadOBJ      | Function | pm4
| GXS_LoadOBJ     | Function | pm4
||
| GX_TrySetBankForBGExtPltt     | Function | pm4
| GX_TrySetBankForSubBGExtPltt  | Function | pm4
| GX_TrySetBankForOBJExtPltt    | Function | pm4
| GX_TrySetBankForSubOBJExtPltt | Function | pm4
| GX_ResetBankForBGExtPltt      | Function | pm4
| GX_ResetBankForSubBGExtPltt   | Function | pm4
| GX_ResetBankForOBJExtPltt     | Function | pm4
| GX_ResetBankForSubOBJExtPltt  | Function | pm4
||
| GX_BeginLoadBGExtPltt   | Function | pm4
| GX_LoadBGExtPltt        | Function | pm4
| GX_EndLoadBGExtPltt     | Function | pm4
| GXS_BeginLoadBGExtPltt  | Function | pm4
| GXS_LoadBGExtPltt       | Function | pm4
| GXS_EndLoadBGExtPltt    | Function | pm4
| GX_BeginLoadOBJExtPltt  | Function | pm4
| GX_LoadOBJExtPltt       | Function | pm4
| GX_EndLoadOBJExtPltt    | Function | pm4
| GXS_BeginLoadOBJExtPltt | Function | pm4
| GXS_LoadOBJExtPltt      | Function | pm4
| GXS_EndLoadOBJExtPltt   | Function | pm4
| GX_BeginLoadTexPltt     | Function | diamondtrust
| GX_LoadTexPltt          | Function | diamondtrust
| GX_EndLoadTexPltt       | Function | diamondtrust
| GX_BeginLoadTex         | Function | diamondtrust
| GX_LoadTex              | Function | diamondtrust
| GX_EndLoadTex           | Function | diamondtrust
||
| GXS_DispOff      | Function | pm4, diamondtrust
| GXS_DispOn       | Function | pm4, diamondtrust
| GX_SetPower      | Function | pm4
| GX_SetDispSelect | Function | pm4
||
| GX_SetOBJVRamModeChar  | Function | pm4
| GXS_SetOBJVRamModeChar | Function | pm4
||
| GX_GetVCount | Function | pm4
||
| GX_SetVisiblePlane | Function | pm4
| GXS_SetVisiblePlane | Function | pm4
||
| GX_SetBGCharOffset | Function | pm4
| GX_SetBGScrOffset | Function | pm4
||
| GX_SetCapture | Function | diamondtrust
||
| GXS_SetOBJVRamModeBmp | Function | diamondtrust
||
| HW_PLTT            | Macro | pm4, diamondtrust
| HW_PLTT_SIZE       | Macro | pm4, diamondtrust
| HW_DB_PLTT         | Macro | pm4, diamondtrust
| HW_DB_PLTT_SIZE    | Macro | pm4, diamondtrust
| HW_BG_VRAM         | Macro
| HW_BG_VRAM_SIZE    | Macro
| HW_DB_BG_VRAM      | Macro
| HW_DB_BG_VRAM_SIZE | Macro
| HW_OBJ_VRAM        | Macro | gtpd
| HW_OBJ_VRAM_SIZE   | Macro | gtpd | Deduced from HW_OBJ_VRAM
| HW_LCDC_VRAM       | Macro | pm4
| HW_LCDC_VRAM_SIZE  | Macro | pm4
| HW_OAM             | Macro | pm4, diamondtrust
| HW_OAM_SIZE        | Macro | pm4, diamondtrust
| HW_DB_OAM          | Macro | pm4, diamondtrust
| HW_DB_OAM_SIZE     | Macro | pm4, diamondtrust
||
| IC_InvalidateAll | Function
| IC_InvalidateRange | Function
||
| MB_USER_NAME_LENGTH | Macro | diamondtrust
||
| MBParentBssDesc | Struct | diamondtrust
| MBGameRegistry  | Struct | diamondtrust
| MBUserInfo      | Struct | diamondtrust
||
| MB_IsMultiBootChild | Function | diamondtrust
| MB_GetMultiBootParentBssDesc | Function | diamondtrust
||
| MI_DmaFill32 | Function | pm4
| MI_DmaCopy16 | Function | pm4
| MI_DmaCopy32 | Function | pm4
| MI_IsDmaBusy | Function | pm4
||
| _MI_CpuFill | Function
| MI_CpuFill8 | Function | pm4
| MI_CpuCopy8 | Function | pm4
| MI_CpuCopy16 | Function
| MI_CpuCopy32 | Function
| MI_CpuFill32 | Function | gtpd
| MI_Swap | Function
||
| MI_CpuClearFast | Function | pm4, diamondtrust, gtpd
| MI_CpuFillFast | Function | pm4, diamondtrust
||
| OS_CACHE_LINE_SIZE | Macro
||
| OS_IE_V_BLANK | Macro | pm4
| OS_IE_H_BLANK | Macro | pm4
||
| OS_ARENA_MAIN          | Macro | pm4
| OS_ARENA_ITCM          | Macro | pm4 | Deduced from OS_GetITCMArenaLo
| OS_ARENA_DTCM          | Macro | pm4 | Deduced from OS_GetDTCMArenaLo
| OS_CURRENT_HEAP_HANDLE | Macro | pm4
||
| OS_MESSAGE_NOBLOCK | Macro | diamondtrust
| OS_MESSAGE_BLOCK   | Macro | pm4, diamondtrust
||
| OS_CONSOLE_ISDEBUGGER | Macro | pm4
| OS_CONSOLE_NITRO      | Macro | pm4
||
| OS_LOCK_ID_ERROR | Macro | pm4, GameSpy
||
| OS_THREAD_LAUNCHER_PRIORITY | Macro | diamondtrust
||
| OSLinkedList   | Struct
| OSThread       | Struct | pm4, diamondtrust
| OSMessageQueue | Struct | pm4, diamondtrust
| OSMessage      | Struct | pm4, diamondtrust
| OSAlarm        | Struct | pm4
| OSMutex        | Struct | pm4, diamondtrust
| OSDma          | Struct
||
| OSHeapHandle   | Typedef | pm4, diamondtrust
| OSTime         | Typedef | pm4
| OSIntrMode     | Typedef | diamondtrust
||
| OS_Init | Function | pm4, diamondtrust
| OS_InitThread | Function | diamondtrust
| OS_InitTick | Function | pm4, diamondtrust
| OS_InitAlarm | Function | pm4, diamondtrust
| OS_Terminate | Function | diamondtrust, gtpd
||
| OS_SetIrqFunction | Function | pm4, diamondtrust
| OS_EnableIrqMask | Function | pm4, diamondtrust
||
| OS_WaitVBlankIntr | Function | pm4, diamondtrust
| _OS_SpinWait | Function
| OS_SpinWait | Function | diamondtrust
||
| OS_InitMutex | Function | pm4, diamondtrust
| OS_LockMutex | Function | pm4, diamondtrust
| OS_UnlockMutex | Function | pm4, diamondtrust
||
| OS_TPrintf  | Function | pm4, diamondtrust
| OS_Printf   | Function | pm4, diamondtrust
| OS_TVPrintf | Function | diamondtrust
| OS_TPanic   | Function | diamondtrust
| OS_Panic    | Function | pm4, diamondtrust, gtpd
| OS_Halt     | Function | gtact
||
| OS_ResetSystem | Function | pm4
||
| OS_InitAlloc        | Function | pm4, diamondtrust
| OS_GetArenaLo       | Function | pm4, diamondtrust | Deduced from OS_GetMainArenaLo and similar functions
| OS_GetArenaHi       | Function | pm4, diamondtrust | Deduced from OS_GetMainArenaHi and similar functions
| OS_SetArenaLo       | Function | diamondtrust
| OS_AllocFromArenaLo | Function | pm4 | Deduced from OS_AllocFromMainArenaLo
| OS_CreateHeap       | Function | pm4, diamondtrust
| OS_SetCurrentHeap   | Function | pm4, diamondtrust
| OS_DumpHeap         | Function | pm4
| OS_AllocFromHeap    | Function
| OS_FreeFromHeap     | Function
| OS_CheckHeap        | Function | diamondtrust
||
| OS_Sleep | Function | pm4, diamondtrust
||
| OS_CreateThread            | Function | pm4, diamondtrust
| OS_WakeupThread            | Function | gtact
| OS_WakeupThreadDirect      | Function | pm4, diamondtrust
| OS_IsThreadTerminated      | Function | pm4
| OS_KillThread              | Function | pm4
| OS_GetCurrentThread        | Function | pm4
| OS_SleepThread             | Function | diamondtrust
| OS_CheckStack              | Function | pm4
| OS_SetSwitchThreadCallback | Function | gtact
| OSSwitchThreadCallback     | Typedef  | gtact | Deduced from OS_SetSwitchThreadCallback
| OS_InitContext             | Function | gtact
| OS_SaveContext             | Function | gtact
| OS_LoadContext             | Function | gtact
| OS_SetThreadDestructor     | Function | gtact
| OS_ExitThread              | Function | gtact
| OS_DisableScheduler        | Function | gtact
| OS_EnableScheduler         | Function | gtact
| OS_RescheduleThread        | Function | gtact
| OS_SelectThread            | Function | gtact
| OS_SetThreadPriority       | Function | gtact
| OS_GetThreadPriority       | Function | gtact
||
| OSi_IdleThreadProc               | Function | gtact
| OSi_InsertLinkToQueue            | Function | gtact
| OSi_RemoveLinkFromQueue          | Function | gtact
| OSi_RemoveSpecifiedLinkFromQueue | Function | gtact
| OSi_RescheduleThread             | Function | gtact
| OSi_GetUnusedThreadId            | Function | gtact
| OSi_InsertThreadToList           | Function | gtact
| OSi_RemoveThreadFromList         | Function | gtact
| OSi_ExitThread_ArgSpecified      | Function | gtact
| OSi_ExitThread                   | Function | gtact
| OSi_ExitThread_Destroy           | Function | gtact
| OSi_UnlockAllMutex               | Function | gtact
||
| OS_InitMessageQueue | Function | pm4, diamondtrust
| OS_ReceiveMessage   | Function | pm4, diamondtrust
| OS_SendMessage      | Function | pm4, diamondtrust
||
| OS_CreateAlarm      | Function | pm4
| OS_SetPeriodicAlarm | Function | pm4
| OS_CancelAlarm      | Function | pm4
||
| OSi_SleepAlarmCallback | Function | gtact
||
| OS_GetTick | Function | pm4, diamondtrust
||
| OS_GetConsoleType | Function | pm4
||
| OS_GetLockID | Function | pm4, GameSpy
||
| OS_DisableInterrupts | Function | diamondtrust
| OS_RestoreInterrupts | Function | diamondtrust
| OS_EnableInterrupts  | Function | diamondtrust
| OS_SetIrqCheckFlag   | Function | pm4, diamondtrust
| OS_EnableIrq         | Function | pm4, diamondtrust
||
| OS_GetMainArenaLo       | Function | pm4, diamondtrust
| OS_GetMainArenaHi       | Function | pm4, diamondtrust
| OS_GetITCMArenaLo       | Function | pm4
| OS_GetITCMArenaHi       | Function | pm4
| OS_GetDTCMArenaLo       | Function | pm4
| OS_GetDTCMArenaHi       | Function | pm4
| OS_SetMainArenaLo       | Function | pm4
| OS_AllocFromMainArenaLo | Function | pm4
| OS_Alloc                | Function | pm4, diamondtrust
| OS_Free                 | Function | pm4, diamondtrust
||
| OS_MilliSecondsToTicks | Function
| OS_MicroSecondsToTicks | Function | pm4
| OS_TicksToMilliSeconds | Function | diamondtrust
||
| OS_GetProcMode | Function | gtact
||
| OS_IsRunOnTwl | Function | diamondtrust
||
| PAD_BUTTON_A      | Macro | pm4
| PAD_BUTTON_B      | Macro | pm4
| PAD_BUTTON_SELECT | Macro | pm4
| PAD_BUTTON_START  | Macro | pm4, diamondtrust
| PAD_KEY_RIGHT     | Macro | pm4
| PAD_KEY_LEFT      | Macro | pm4
| PAD_KEY_UP        | Macro | pm4
| PAD_KEY_DOWN      | Macro | pm4
| PAD_BUTTON_R      | Macro | pm4
| PAD_BUTTON_L      | Macro | pm4
| PAD_BUTTON_X      | Macro | pm4
| PAD_BUTTON_Y      | Macro | pm4
| PAD_BUTTON_ALL    | Macro | pm4
| PAD_KEY_ALL       | Macro
| PAD_ALL           | Macro | pm4
||
| PAD_DetectFold | Function | pm4, diamondtrust
| PAD_Read       | Function | pm4, diamondtrust
||
| PM_GoSleepMode | Function | pm4
| PM_SetLCDPower | Function | diamondtrust
||
| RTCDate | Struct | pm4, diamondtrust
| RTCTime | Struct | pm4, diamondtrust
||
| RTC_Init                    | Function | pm4, diamondtrust
| RTC_GetDate                 | Function | pm4, diamondtrust
| RTC_GetTime                 | Function | pm4, diamondtrust
| RTC_ConvertDateTimeToSecond | Function | pm4, diamondtrust
||
| SND_COMMAND_NOBLOCK | Macro | pm4, diamondtrust
| SND_COMMAND_BLOCK   | Macro | pm4
||
| SND_TIMER_CLOCK | Macro | pm4, diamondtrust
||
| SND_WAVE_FORMAT_PCM16 | Macro | diamondtrust
||
| SND_CHANNEL_LOOP_REPEAT | Macro | diamondtrust
||
| SND_CHANNEL_DATASHIFT_NONE | Macro | diamondtrust
||
| SNDAlarmCallback | Typedef
||
| SNDCommandType | Enum
| SNDCommand | Struct
||
| SND_Init             | Function | pm4, diamondtrust
| SND_RecvCommandReply | Function | pm4, diamondtrust
| SND_FlushCommand     | Function | pm4, diamondtrust
||
| SND_UnlockChannel    | Function | pm4
| SND_LockChannel      | Function | pm4, diamondtrust
| SND_SetChannelVolume | Function | diamondtrust
| SND_SetChannelPan    | Function | diamondtrust
| SND_SetupChannelPcm  | Function | pm4, diamondtrust
||
| SND_SetupAlarm | Function | pm4, diamondtrust
| SND_StartTimer | Function | pm4, diamondtrust
| SND_StopTimer  | Function | pm4
||
| SND_GetCurrentCommandTag | Function | pm4
| SND_WaitForCommandProc   | Function | pm4
||
| STD_CompareNString | Function | pm4
| STD_CompareString  | Function | pm4
| STD_CopyString     | Function | pm4
| STD_SearchString   | Function | pm4
||
| SVC_WaitVBlankIntr | Function | pm4
||
| TP_VALIDITY_VALID      | Macro | pm4, diamondtrust
| TP_VALIDITY_INVALID_X  | Macro | pm4
| TP_VALIDITY_INVALID_Y  | Macro | pm4
| TP_VALIDITY_INVALID_XY | Macro | pm4
||
| TP_REQUEST_COMMAND_AUTO_SAMPLING | Macro | diamondtrust
||
| TP_RESULT_SUCCESS | Macro | diamondtrust
||
| TP_TOUCH_ON | Macro | diamondtrust
||
| TPCalibrateParam | Struct | pm4, diamondtrust
| TPData           | Struct | pm4, diamondtrust
||
| TPRequestCommand | Typedef | diamondtrust
| TPRequestResult  | Typedef | diamondtrust
||
| TP_Init               | Function | pm4, diamondtrust, gtpd, gs456
| TP_SetCallback        | Function | diamondtrust
| TP_GetUserInfo        | Function | pm4, diamondtrust, gtpd, gs456
| TP_SetCalibrateParam  | Function | pm4, diamondtrust, gtpd, gs456
| TP_GetCalibratedPoint | Function | pm4, gs456
||
| _TP_RequestAutoSamplingStart      | Function
| TP_GetLatestCalibratedPointInAuto | Function | diamondtrust
| TP_RequestRawSampling             | Function | pm4, gs456
| TP_RequestAutoSamplingStart       | Function | diamondtrust
||
| WM_SYSTEM_BUF_SIZE | Macro | diamondtrust
||
| WM_ERRCODE_SUCCESS        | Macro | diamondtrust
| WM_ERRCODE_FAILED         | Macro | diamondtrust
| WM_ERRCODE_ILLEGAL_STATE  | Macro | diamondtrust
| WM_ERRCODE_OPERATING      | Macro | diamondtrust
| WM_ERRCODE_TIMEOUT        | Macro | diamondtrust
| WM_ERRCODE_NO_ENTRY       | Macro | diamondtrust
| WM_ERRCODE_OVER_MAX_ENTRY | Macro | diamondtrust
| WM_ERRCODE_SEND_FAILED    | Macro | diamondtrust
||
| WM_STATECODE_PARENT_START | Macro | diamondtrust
| WM_STATECODE_PARENT_FOUND | Macro | diamondtrust
| WM_STATECODE_MP_START     | Macro | diamondtrust
| WM_STATECODE_CONNECTED    | Macro | diamondtrust
| WM_STATECODE_BEACON_LOST  | Macro | diamondtrust
| WM_STATECODE_DISCONNECTED | Macro | diamondtrust
| WM_STATECODE_PORT_RECV    | Macro | diamondtrust
||
| WM_SIZE_BSSID | Macro | diamondtrust
| WM_SIZE_SSID  | Macro | diamondtrust
||
| WM_ATTR_FLAG_ENTRY | Macro | diamondtrust
| WM_ATTR_FLAG_MB    | Macro | diamondtrust
||
| WM_STATE_PARENT | Macro | diamondtrust
| WM_STATE_CHILD  | Macro | diamondtrust
||
| WMErrCode   | Typedef | diamondtrust
| WMStateCode | Typedef | diamondtrust
||
| WMParentParam            | Struct | diamondtrust
| WMScanParam              | Struct | diamondtrust
| WMGameInfo               | Struct | diamondtrust
| WMBssDesc                | Struct | diamondtrust
| WMCallback               | Struct | diamondtrust
| WMPortRecvCallback       | Struct | diamondtrust
| WMStartMPCallback        | Struct | diamondtrust
| WMStartParentCallback    | Struct | diamondtrust
| WMStartConnectCallback   | Struct | diamondtrust
| WMStartScanCallback      | Struct | diamondtrust
| WMPortSendCallback       | Struct | diamondtrust
| WMMeasureChannelCallback | Struct | diamondtrust
| WMStatus                 | Struct | diamondtrust
||
| WM_Initialize         | Function | diamondtrust
| WM_SetPortCallback    | Function | diamondtrust
| WM_SetEntry           | Function | diamondtrust
| WM_SetParentParameter | Function | diamondtrust
| _WM_SetMPDataToPort   | Function
| WM_SetMPDataToPort    | Function | diamondtrust
||
| WM_GetMPSendBufferSize       | Function | diamondtrust
| WM_GetMPReceiveBufferSize    | Function | diamondtrust
| WM_GetDispersionBeaconPeriod | Function | diamondtrust
| WM_GetDispersionScanPeriod   | Function | diamondtrust
| WM_GetAllowedChannel         | Function | diamondtrust
| WM_GetLinkLevel              | Function | diamondtrust
| WM_GetNextTgid               | Function | diamondtrust
||
| WM_StartParent   | Function | diamondtrust
| _WM_StartConnect | Function
| WM_StartConnect  | Function | diamondtrust
| WM_Disconnect    | Function | diamondtrust
| WM_Reset         | Function | diamondtrust
| WM_End           | Function | diamondtrust
||
| WM_StartMP | Function | diamondtrust
| WM_EndMP   | Function | diamondtrust
||
| WM_StartScan | Function | diamondtrust
| WM_EndScan   | Function | diamondtrust
||
| WM_MeasureChannel | Function | diamondtrust
||
| WM_ReadStatus | Function | diamondtrust
||
