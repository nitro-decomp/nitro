#ifndef _NITRO_G2_H
#define _NITRO_G2_H

#include "nitro/fx.h"
#include "nitro/gx.h"
#include "nitro/reg.h"
#include "nitro/types.h"

inline void G2_SetBG0Priority(u32 value) {
    REG_BG0CNT = (REG_BG0CNT & ~0x3) | (value);
}

inline void G2_SetBG1Priority(u32 value) {
    REG_BG1CNT = (REG_BG1CNT & ~0x3) | (value);
}

inline void G2_SetBG2Priority(u32 value) {
    REG_BG2CNT = (REG_BG2CNT & ~0x3) | (value);
}

inline void G2_SetBG3Priority(u32 value) {
    REG_BG3CNT = (REG_BG3CNT & ~0x3) | (value);
}

inline void G2S_SetBG0Priority(u32 value) {
    REG_BG0CNT_SUB = (REG_BG0CNT_SUB & ~0x3) | (value);
}

inline void G2S_SetBG1Priority(u32 value) {
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & ~0x3) | (value);
}

inline void G2S_SetBG2Priority(u32 value) {
    REG_BG2CNT_SUB = (REG_BG2CNT_SUB & ~0x3) | (value);
}

inline void G2S_SetBG3Priority(u32 value) {
    REG_BG3CNT_SUB = (REG_BG3CNT_SUB & ~0x3) | (value);
}

inline void G2_SetBG0Offset(u32 x, u32 y) {
    REG_BG0OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2_SetBG1Offset(u32 x, u32 y) {
    REG_BG1OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2_SetBG2Offset(u32 x, u32 y) {
    REG_BG2OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2_SetBG3Offset(u32 x, u32 y) {
    REG_BG3OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2S_SetBG0Offset(u32 x, u32 y) {
    REG_BG0OFS_SUB = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2S_SetBG1Offset(u32 x, u32 y) {
    REG_BG1OFS_SUB = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2S_SetBG2Offset(u32 x, u32 y) {
    REG_BG2OFS_SUB = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2S_SetBG3Offset(u32 x, u32 y) {
    REG_BG3OFS_SUB = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
}

inline void G2_SetBG0Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                             GXBGCharBase charBase, u32) {
    REG_BG0CNT = (REG_BG0CNT & 0x43) | (scrSize << 0xe) | (colMode << 0x7) | (scrBase << 0x8) |
                 (charBase << 0x2);
}

inline void G2_SetBG1Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                             GXBGCharBase charBase, u32) {
    REG_BG1CNT = (REG_BG1CNT & 0x43) | (scrSize << 0xe) | (colMode << 0x7) | (scrBase << 0x8) |
                 (charBase << 0x2);
}

inline void G2_SetBG2Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                             GXBGCharBase charBase, u32) {
    REG_BG2CNT = (REG_BG2CNT & 0x43) | (scrSize << 0xe) | (colMode << 0x7) | (scrBase << 0x8) |
                 (charBase << 0x2);
}

inline void G2_SetBG3Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                             GXBGCharBase charBase, u32) {
    REG_BG3CNT = (REG_BG3CNT & 0x43) | (scrSize << 0xe) | (colMode << 0x7) | (scrBase << 0x8) |
                 (charBase << 0x2);
}

inline void G2S_SetBG0Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                              GXBGCharBase charBase, u32) {
    REG_BG0CNT_SUB = (REG_BG0CNT_SUB & 0x43) | (scrSize << 0xe) | (colMode << 0x7) |
                     (scrBase << 0x8) | (charBase << 0x2);
}

inline void G2S_SetBG1Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                              GXBGCharBase charBase, u32) {
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & 0x43) | (scrSize << 0xe) | (colMode << 0x7) |
                     (scrBase << 0x8) | (charBase << 0x2);
}

inline void G2S_SetBG2Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                              GXBGCharBase charBase, u32) {
    REG_BG2CNT_SUB = (REG_BG2CNT_SUB & 0x43) | (scrSize << 0xe) | (colMode << 0x7) |
                     (scrBase << 0x8) | (charBase << 0x2);
}

inline void G2S_SetBG3Control(GXBGScrSizeText scrSize, GXBGColorMode colMode, GXBGScrBase scrBase,
                              GXBGCharBase charBase, u32) {
    REG_BG3CNT_SUB = (REG_BG3CNT_SUB & 0x43) | (scrSize << 0xe) | (colMode << 0x7) |
                     (scrBase << 0x8) | (charBase << 0x2);
}

inline void G2_SetBG2Control256Bmp(GXBGScrSize256Bmp scrSize, GXBGAreaOver areaOver,
                                   GXBGBmpScrBase scrBase) {
    REG_BG2CNT =
        (REG_BG2CNT & 0x43) | (scrSize << 0xe) | 0x80 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2_SetBG3Control256Bmp(GXBGScrSize256Bmp scrSize, GXBGAreaOver areaOver,
                                   GXBGBmpScrBase scrBase) {
    REG_BG3CNT =
        (REG_BG3CNT & 0x43) | (scrSize << 0xe) | 0x80 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2S_SetBG2Control256Bmp(GXBGScrSize256Bmp scrSize, GXBGAreaOver areaOver,
                                    GXBGBmpScrBase scrBase) {
    REG_BG2CNT_SUB =
        (REG_BG2CNT_SUB & 0x43) | (scrSize << 0xe) | 0x80 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2S_SetBG3Control256Bmp(GXBGScrSize256Bmp scrSize, GXBGAreaOver areaOver,
                                    GXBGBmpScrBase scrBase) {
    REG_BG3CNT_SUB =
        (REG_BG3CNT_SUB & 0x43) | (scrSize << 0xe) | 0x80 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2_SetBG2ControlDCBmp(GXBGScrSizeDcBmp scrSize, GXBGAreaOver areaOver,
                                  GXBGBmpScrBase scrBase) {
    REG_BG2CNT =
        (REG_BG2CNT & 0x43) | (scrSize << 0xe) | 0x84 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2_SetBG3ControlDCBmp(GXBGScrSizeDcBmp scrSize, GXBGAreaOver areaOver,
                                  GXBGBmpScrBase scrBase) {
    REG_BG3CNT =
        (REG_BG3CNT & 0x43) | (scrSize << 0xe) | 0x84 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2S_SetBG2ControlDCBmp(GXBGScrSizeDcBmp scrSize, GXBGAreaOver areaOver,
                                   GXBGBmpScrBase scrBase) {
    REG_BG2CNT_SUB =
        (REG_BG2CNT_SUB & 0x43) | (scrSize << 0xe) | 0x84 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2S_SetBG3ControlDCBmp(GXBGScrSizeDcBmp scrSize, GXBGAreaOver areaOver,
                                   GXBGBmpScrBase scrBase) {
    REG_BG3CNT_SUB =
        (REG_BG3CNT_SUB & 0x43) | (scrSize << 0xe) | 0x84 | (scrBase << 0x8) | (areaOver << 0xd);
}

inline void G2_SetBG2ControlText(GXBGScrSizeText scrSize, GXBGColorMode colMode,
                                 GXBGScrBase scrBase, GXBGCharBase charBase) {
    G2_SetBG2Control(scrSize, colMode, scrBase, charBase, 0);
}

inline void G2_SetBG3ControlText(GXBGScrSizeText scrSize, GXBGColorMode colMode,
                                 GXBGScrBase scrBase, GXBGCharBase charBase) {
    G2_SetBG3Control(scrSize, colMode, scrBase, charBase, 0);
}

inline void G2S_SetBG2ControlText(GXBGScrSizeText scrSize, GXBGColorMode colMode,
                                  GXBGScrBase scrBase, GXBGCharBase charBase) {
    G2S_SetBG2Control(scrSize, colMode, scrBase, charBase, 0);
}

inline void G2S_SetBG3ControlText(GXBGScrSizeText scrSize, GXBGColorMode colMode,
                                  GXBGScrBase scrBase, GXBGCharBase charBase) {
    G2S_SetBG3Control(scrSize, colMode, scrBase, charBase, 0);
}

void G2_SetBGAffine(u32 *reg, MtxFx22 *mtx, u32, u32, u32, u32);

inline void G2_SetBG2Affine(MtxFx22 *mtx, u32 param2, u32 param3, u32 param4, u32 param5) {
    G2_SetBGAffine(&REG_BG2PA, mtx, param2, param3, param4, param5);
}

inline void G2_SetBG3Affine(MtxFx22 *mtx, u32 param2, u32 param3, u32 param4, u32 param5) {
    G2_SetBGAffine(&REG_BG3PA, mtx, param2, param3, param4, param5);
}

inline void G2_ChangeBlendAlpha(u32 param1, u32 param2) {
    REG_BLDALPHA = param1 | (param2 << 8);
}

inline void G2S_ChangeBlendAlpha(u32 param1, u32 param2) {
    REG_BLDALPHA_SUB = param1 | (param2 << 8);
}

inline void G2_BG0Mosaic(bool32 flag) {
    if (flag) {
        REG_BG0CNT |= 0x40;
    } else {
        REG_BG0CNT &= ~0x40;
    }
}

inline void G2_BG1Mosaic(bool32 flag) {
    if (flag) {
        REG_BG1CNT |= 0x40;
    } else {
        REG_BG1CNT &= ~0x40;
    }
}

inline void G2_BG2Mosaic(bool32 flag) {
    if (flag) {
        REG_BG2CNT |= 0x40;
    } else {
        REG_BG2CNT &= ~0x40;
    }
}

inline void G2_BG3Mosaic(bool32 flag) {
    if (flag) {
        REG_BG3CNT |= 0x40;
    } else {
        REG_BG3CNT &= ~0x40;
    }
}

inline void G2S_BG0Mosaic(bool32 flag) {
    if (flag) {
        REG_BG0CNT_SUB |= 0x40;
    } else {
        REG_BG0CNT_SUB &= ~0x40;
    }
}

inline void G2S_BG1Mosaic(bool32 flag) {
    if (flag) {
        REG_BG1CNT_SUB |= 0x40;
    } else {
        REG_BG1CNT_SUB &= ~0x40;
    }
}

inline void G2S_BG2Mosaic(bool32 flag) {
    if (flag) {
        REG_BG2CNT_SUB |= 0x40;
    } else {
        REG_BG2CNT_SUB &= ~0x40;
    }
}

inline void G2S_BG3Mosaic(bool32 flag) {
    if (flag) {
        REG_BG3CNT_SUB |= 0x40;
    } else {
        REG_BG3CNT_SUB &= ~0x40;
    }
}

inline void G2_SetBGMosaicSize(u32 width, u32 height) {
    REG_MOSAIC = width | (height << 4);
}

inline void G2S_SetBGMosaicSize(u32 width, u32 height) {
    REG_MOSAIC_SUB = width | (height << 4);
}

inline void G2_SetOBJMosaicSize(u32 width, u32 height) {
    REG_OBJMOSAIC = width | (height << 4);
}

inline void G2S_SetOBJMosaicSize(u32 width, u32 height) {
    REG_OBJMOSAIC_SUB = width | (height << 4);
}

inline void G2_BlendNone() {
    REG_BLDCNT = 0;
}

inline void G2S_BlendNone() {
    REG_BLDCNT_SUB = 0;
}

void _G2_SetBlend(u16 *, u32 srcPlane, u32 dstPlane, u32 srcAlpha, u32 dstAlpha);

inline void G2_SetBlendAlpha(u32 srcPlane, u32 dstPlane, u32 srcAlpha, u32 dstAlpha) {
    _G2_SetBlend(&REG_BLDCNT, srcPlane, dstPlane, srcAlpha, dstAlpha);
}

inline void G2S_SetBlendAlpha(u32 srcPlane, u32 dstPlane, u32 srcAlpha, u32 dstAlpha) {
    _G2_SetBlend(&REG_BLDCNT_SUB, srcPlane, dstPlane, srcAlpha, dstAlpha);
}

inline void G2_GetOBJPosition(GXOamAttr *oam, u32 *x, u32 *y) {
    *x = (oam->lo & 0x1ff0000) >> 16;
    *y = oam->lo & 0xff;
}

inline void G2_SetOBJPosition(GXOamAttr *oam, u32 x, u32 y) {
    oam->lo = (oam->lo & 0xfe00ff00) | (y & 0xff) | (x << 0x17 >> 0x7);
}

inline u32 G2_GetOBJCharName(GXOamAttr *oam) {
    return oam->hi & 0x3ff;
}

inline void G2_SetOBJCharName(volatile GXOamAttr *oam, u32 name) {
    oam->hi = (oam->hi & -0x400) | (name);
}

inline u32 G2_GetOBJColorParam(GXOamAttr *oam) {
    return (oam->hi & 0xf000) >> 0xc;
}

// Defined as macro as sometimes `oam` is volatile and other times not
#define G2_GetOBJMode(oam) (GXOamMode)(((oam)->lo & 0xc00) >> 0xa)
// inline GXOamMode G2_GetOBJMode(volatile GXOamAttr *oam) {
//     return ((oam)->lo & 0xc00) >> 0xa;
// }

inline void G2_SetOBJMode(GXOamAttr *oam, GXOamMode mode, u32 color) {
    oam->lo = (oam->lo & ~0xc00) | (mode << 0xa);
    oam->hi = (oam->hi & ~0xf000) | (color << 0xc);
}

inline void G2_SetOBJPriority(GXOamAttr *oam, u32 prio) {
    // no implementation found
}

void *G2_GetBG2ScrPtr(void);
void *G2_GetBG3ScrPtr(void);

#endif
