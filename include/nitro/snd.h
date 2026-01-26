#ifndef _NITRO_SND_H
#define _NITRO_SND_H

#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1

#define SND_TIMER_CLOCK 0xffb0ff

#define SND_WAVE_FORMAT_PCM16 1

#define SND_CHANNEL_LOOP_REPEAT 1

#define SND_CHANNEL_DATASHIFT_NONE 0

void SND_Init(void);
void *SND_RecvCommandReply(u32);
void SND_FlushCommand(u32);

void SND_StopTimer(u32 channel, u32, u32 alarm, u32);
void SND_UnlockChannel(u32 channel, u32);
void SND_LockChannel(u32 channel, u32);

void SND_SetupChannelPcm(u32 channel, u32 format, void *buf, u32 loop, u32, u32 numSamples,
                         u32 volume, u32 datashift, u32, u32);

void SND_SetupAlarm(u32 num, u32, u32, void (*callback)(void *arg), void *arg);
void SND_StartTimer(u32 channel, u32, u32 num, u32);

u32 SND_GetCurrentCommandTag(void);
void SND_WaitForCommandProc(u32 tag);

#endif
