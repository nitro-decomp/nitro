#ifndef _NITRO_PM_H
#define _NITRO_PM_H

#ifdef __cplusplus
extern "C" {
#endif

// TODO: These two may swap values
#define PM_TRIGGER_COVER_OPEN 4
#define PM_TRIGGER_CARD 8

void PM_GoSleepMode(u32, u32, u32);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
