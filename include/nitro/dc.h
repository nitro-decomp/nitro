#ifndef _NITRO_DC_H
#define _NITRO_DC_H

void DC_StoreAll(void);
void DC_StoreRange(void *ptr, u32 size);

void DC_FlushAll(void);
void DC_FlushRange(void *ptr, u32 size);

#endif
