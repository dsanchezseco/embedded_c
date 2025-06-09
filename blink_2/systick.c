#include "systick.h"

#define CTRL_ENABLE (1U << 0)
#define CTRL_CLCKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)

// MCU FREQ(hz)/1000 equals 1ms
// 4MHz
#define ONE_MSEC_LOAD 4000000 / 1000

void systick_msec_delay(uint32_t delay)
{

    // Ready register with 1ms
    SysTick->LOAD = ONE_MSEC_LOAD - 1;

    // clear counter
    SysTick->VAL = 0;

    // Use internal clock as source
    SysTick->CTRL |= CTRL_CLCKSRC;

    // Start counting
    SysTick->CTRL |= CTRL_ENABLE;

    // count delay times 1ms
    for (int i = 0; i < delay; i++)
    {
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0)
        {
        }
    }

    // disable SysTick to save resources
    SysTick->CTRL = 0;
}