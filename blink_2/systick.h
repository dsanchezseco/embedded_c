#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include "stm32l4xx.h"
#include "system_stm32l4xx.h"
#include "gpio.h"

void systick_init(uint8_t clock_selector);
void systick_msec_delay(uint32_t delay);
uint8_t cycle_clock_speed(uint8_t clock_selector);

#endif // SYSTICK_H