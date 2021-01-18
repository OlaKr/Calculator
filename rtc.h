#ifndef rtc_h
#include <stdint.h>

void rtc_init(void);

void rtc_reset(void);

uint32_t rtc_update(void);

#endif