#include "nitro/os.h"

#ifdef NITRO_NO_ASM
void CP_SaveContext(CPContext *param1) {
    param1->div       = REG_DIV;
    param1->sqrtParam = REG_SQRT_PARAM;
    param1->divCnt    = REG_DIV_CNT & 3;
    param1->sqrtCnt   = REG_SQRT_CNT & 1;
}
#else
// clang-format off
asm void CP_SaveContext(CPContext *param1) {
    ldconst r1, #0x4000290
    stmdb sp!, {r4}
    ldmia r1, {r2, r3, r4, ip}
    stmia r0!, {r2, r3, r4, ip}
    ldrh ip, [r1, -0x10]
    add r1, r1, 0x28
    ldmia r1, {r2, r3}
    stmia r0!, {r2, r3}
    and ip, ip, 3
    ldrh r2, [r1, -8]
    strh ip, [r0]
    and r2, r2, 1
    strh r2, [r0, 2]
    ldmia sp!, {r4}
    bx lr
}
// clang-format on
#endif

#ifdef NITRO_NO_ASM
void CPi_RestoreContext(CPContext *param1) {
    REG_DIV        = param1->div;
    REG_SQRT_PARAM = param1->sqrtParam;
    REG_DIV_CNT    = param1->divCnt;
    REG_SQRT_CNT   = param1->sqrtCnt;
}
#else
// clang-format off
asm void CPi_RestoreContext(CPContext *param1) {
    stmdb sp!, {r4}
    ldconst r1, #0x4000290
    ldmia r0, {r2, r3, r4, ip}
    stmia r1, {r2, r3, r4, ip}
    ldrh r2, [r0, 0x18]
    ldrh r3, [r0, 0x1a]
    strh r2, [r1, -0x10]
    strh r3, [r1, 0x20]
    add r0, r0, 0x10
    add r1, r1, 0x28
    ldmia r0, {r2, r3}
    stmia r1, {r2, r3}
    ldmia sp!, {r4}
    bx lr
}
// clang-format on
#endif