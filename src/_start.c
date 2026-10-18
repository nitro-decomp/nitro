#include "nitro/hw.h"
#include "nitro/mi.h"
#include "nitro/os.h"
#include "nitro/reg.h"

typedef struct INIT_AutoloadInfo {
    /* 00 */ void *baseAddress;
    /* 04 */ u32 codeSize;
    /* 08 */ u32 bssSize;
    /* 0c */
} INIT_AutoloadInfo;

typedef struct INIT_BuildInfo {
    /* 00 */ INIT_AutoloadInfo *autoloadInfosStart;
    /* 04 */ INIT_AutoloadInfo *autoloadInfosEnd;
    /* 08 */ void *autoloadBlocks;
    /* 0c */ u32 bssStart;
    /* 10 */ u32 bssEnd;
    /* 14 */ u32 compressedCodeEnd;
    /* 18 */ u32 sdkVersion;
    /* 1c */
} INIT_BuildInfo;

extern void NitroMain(void);
extern void __call_static_initializers(void);
extern void func_02147c38(void);

extern INIT_BuildInfo BuildInfo;

void _start(void);
static void init_cp15(void);
static void NitroStartUp(void);
static void do_autoload(void);
static void INITi_CpuClear32(u32 value, s32 addr, u32 size);
void _start_AutoloadDoneCallback();

#ifdef NITRO_NO_ASM
    #warning _start has no implementation in NITRO_NO_ASM // TODO
#else
THUMB_DISABLE();
ASM void _start(void){
    #if __MWERKS__ // clang-format off
    mov r12, #0x4000000
    str r12, [r12, #0x208]
_vcount_wait:
#if NITRO_VERSION >= 0x30000000
    ldrh r0, [r12, #0x6]
    cmp r0, #0x0
    bne _vcount_wait
#endif
_vcount_wait_end:
    bl init_cp15
    mov r0, #0x13
    msr cpsr_c, r0
    lda r0, __DTCM_LO
    add r0, r0, #0x3fc0
    mov sp, r0
    mov r0, #0x12
    msr cpsr_c, r0
    lda r0, __DTCM_LO
    add r0, r0, #0x3fc0
    sub r0, r0, #0x40
#if NITRO_VERSION >= 0x30000000
    sub sp, r0, #0x4
    tst sp, #0x4
    subeq sp, sp, #0x4
#else
    mov sp, r0
#endif
    ldr r1, =0x800
    sub r1, r0, r1
    mov r0, #0x1f
    msr cpsr_fsxc, r0
    sub sp, r1, #0x4
    mov r0, #0x0
    lda r1, __DTCM_LO
    mov r2, #0x4000
    bl INITi_CpuClear32
    mov r0, #0x0
    ldconst r1, #HW_PLTT_ADDR
    mov r2, #HW_PLTT_SIZE
    bl INITi_CpuClear32
    mov r0, #0x200
    ldconst r1, #HW_OAM_ADDR
    mov r2, #HW_OAM_SIZE
    bl INITi_CpuClear32
    lda r1, BuildInfo
    ldr r0, [r1, #0x14]
    bl MIi_UncompressBackward
    bl do_autoload
    lda r0, BuildInfo
    ldr r1, [r0, #0xc]
    ldr r2, [r0, #0x10]
    mov r3, r1
    mov r0, #0x0
_zero_bss:
    cmp r1, r2
    strlo r0, [r1], #0x4
    blo _zero_bss
_zero_bss_end:
    bic r1, r3, #0x1f
_invalidate_cache:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r1, c7, c5, 1
    mcr p15, 0, r1, c7, c14, 1
    add r1, r1, #0x20
    cmp r1, r2
    blt _invalidate_cache
_invalidate_cache_end:
    ldr r1, =REG_027FFF9C_ADDR
    str r0, [r1, #0x0]
    lda r1, __DTCM_LO
    add r1, r1, #0x3fc0
    add r1, r1, #0x3c
    lda r0, OS_IrqHandler
    str r0, [r1, #0x0]
    bl func_02147c38
    bl NitroStartUp
    bl __call_static_initializers
    lda r1, NitroMain
    ldconst lr, #HW_BIOS_ADDR
#if NITRO_VERSION >= 0x30000000
    tst sp, #0x4
    subne sp, sp, #0x4
#endif
    bx r1
    #endif // clang-format on
} THUMB_ENABLE();
#endif

#ifdef NITRO_NO_ASM
static void INITi_CpuClear32(u32 value, s32 addr, u32 size) {
    s32 end = addr + size;
    while (true) {
        if (addr >= end) {
            break;
        }
        *(u32 *) (addr++) = value;
    }
}
#else
THUMB_DISABLE();
static void INITi_CpuClear32(u32 value, s32 addr, u32 size) {
    #if __MWERKS__ // clang-format off
    asm {
        add ip, r1, r2
    _loop:
        cmp r1, ip
        stmltia r1!, {r0}
        blt _loop
    }
    #endif // clang-format on
}
THUMB_ENABLE();
#endif

#ifdef NITRO_NO_ASM
    #warning MIi_UncompressBackward has no implementation in NITRO_NO_ASM
#else
THUMB_DISABLE();
ASM void MIi_UncompressBackward(void *addr){
    #if __MWERKS__ // clang-format off
    cmp r0, #0
    beq _return
_uncompress_start:
    stmdb sp!, {r4, r5, r6, r7}
    ldmdb r0, {r1, r2}
    add r2, r0, r2
    sub r3, r0, r1, lsr #24
    bic r1, r1, #0xff000000
    sub r1, r0, r1
    mov r4, r2
_read_flag_byte:
    cmp r3, r1
    ble _uncompress_end
    ldrb r5, [r3, #-1]!
    mov r6, #8
_read_token:
    subs r6, r6, #1
    blt _read_flag_byte
    tst r5, #0x80
    bne _handle_length_distance_pair
_handle_literal:
    ldrb r0, [r3, #-1]!
    strb r0, [r2, #-1]!
    b _next_token
_handle_length_distance_pair:
    ldrb ip, [r3, #-1]!
    ldrb r7, [r3, #-1]!
    orr r7, r7, ip, lsl #8
    bic r7, r7, #0xf000
    add r7, r7, #2
    add ip, ip, #0x20
_repeat_byte:
    ldrb r0, [r2, r7]
    strb r0, [r2, #-1]!
    subs ip, ip, #0x10
    bge _repeat_byte
_next_token:
    cmp r3, r1
    mov r5, r5, lsl #1
    bgt _read_token
_uncompress_end:
    mov r0, #0
    bic r3, r1, #OS_CACHE_LINE_SIZE - 1
_invalidate_cache:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r3, c7, c5, 1
    mcr p15, 0, r3, c7, c14, 1
    add r3, r3, #OS_CACHE_LINE_SIZE
    cmp r3, r4
    blt _invalidate_cache
    ldmia sp!, {r4, r5, r6, r7}
_return:
    bx lr
    #endif // clang-format on
} THUMB_ENABLE();
#endif

#ifdef NITRO_NO_ASM
    #warning do_autoload has no implementation in NITRO_NO_ASM
#else
THUMB_DISABLE();
static ASM void do_autoload(void){
    #if __MWERKS__ // clang-format off
    lda r0, BuildInfo
    ldr r1, [r0, #0x0]
    ldr r2, [r0, #0x4]
    ldr r3, [r0, #0x8]
_next_autoload:
    cmp r1, r2
    beq _end
    ldr r5, [r1], #0x4
    ldr r7, [r1], #0x4
    add r6, r5, r7
    mov r4, r5
_move_autoload:
    cmp r4, r6
    ldrmi r7, [r3], #0x4
    strmi r7, [r4], #0x4
    bmi _move_autoload
    ldr r7, [r1], #0x4
    add r6, r4, r7
    mov r7, #0x0
_zero_bss:
    cmp r4, r6
    strlo r7, [r4], #0x4
    blo _zero_bss
    bic r4, r5, #0x1f
_invalidate_cache:
    mcr p15, 0, r7, c7, c10, 4
    mcr p15, 0, r4, c7, c5, 1
    mcr p15, 0, r4, c7, c14, 1
    add r4, r4, #0x20
    cmp r4, r6
    blt _invalidate_cache
    b _next_autoload
_end:
    b _start_AutoloadDoneCallback
    #endif // clang-format on
} THUMB_ENABLE();
#endif

THUMB_DISABLE();
void _start_AutoloadDoneCallback(void) {}
THUMB_ENABLE();

#ifdef NITRO_NO_ASM
    #warning init_cp15 has no implementation in NITRO_NO_ASM
#else
THUMB_DISABLE();
static ASM void init_cp15(void){
    #if __MWERKS__ // clang-format off
    mrc p15, 0, r0, c1, c0, 0
    ldconst r1, #0xf9005
    bic r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    mov r0, #0x0
    mcr p15, 0, r0, c7, c5, 0
    mcr p15, 0, r0, c7, c6, 0
    mcr p15, 0, r0, c7, c10, 4
    ldconst r0, #0x4000033
    mcr p15, 0, r0, c6, c0, 0
    ldconst r0, #0x200002d
    mcr p15, 0, r0, c6, c1, 0
    ldconst r0, #0x27e0021
    mcr p15, 0, r0, c6, c2, 0
    ldconst r0, #0x8000035
    mcr p15, 0, r0, c6, c3, 0
    lda r0, __DTCM_LO
    orr r0, r0, #0x1a
    orr r0, r0, #0x1
    mcr p15, 0, r0, c6, c4, 0
    ldconst r0, #0x100002f
    mcr p15, 0, r0, c6, c5, 0
    ldconst r0, #0xffff001d
    mcr p15, 0, r0, c6, c6, 0
    ldconst r0, #0x27ff017
    mcr p15, 0, r0, c6, c7, 0
    mov r0, #0x20
    mcr p15, 0, r0, c9, c1, 1
    lda r0, __DTCM_LO
    orr r0, r0, #0xa
    mcr p15, 0, r0, c9, c1, 0
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 1
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 0
    mov r0, #0x2
    mcr p15, 0, r0, c3, c0, 0
    ldconst r0, #0x5100011
    mcr p15, 0, r0, c5, c0, 3
    ldconst r0, #0x15111011
    mcr p15, 0, r0, c5, c0, 2
    mrc p15, 0, r0, c1, c0, 0
    ldconst r1, #0x5707d
    orr r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    bx lr
    #endif // clang-format on
} THUMB_ENABLE();
#endif

THUMB_DISABLE();
static void NitroStartUp(void) {}
THUMB_ENABLE();

THUMB_DISABLE();
void OSi_ReferSymbol(void) {}
THUMB_ENABLE();
