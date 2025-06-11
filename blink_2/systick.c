#include "systick.h"

#define CTRL_ENABLE (1U << 0)
#define CTRL_CLCKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)

#define MSION_MASK 0
#define MSIRDY_MASK 1
#define MSIRANGE_SHIFT 4
#define MSIRANGE_MAX 11

void systick_init(uint8_t clock_selector){
    // init clock_selector at 4MHz
	

	// Tell MSI clock to use MSIRANGE from CR registry (0=CR; 1=CSR)
	RCC->CR |= (1U << 3);
	// Clear current value
	RCC->CR &= ~(0b1111 << MSIRANGE_SHIFT);
	// Set desired speed
	RCC->CR |= clock_selector << MSIRANGE_SHIFT;
    SystemCoreClockUpdate();
}

void systick_msec_delay(uint32_t delay)
{

    // Ready register with 1ms
    // MCU FREQ(hz)/1000 equals 1ms
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;

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

uint8_t cycle_clock_speed(uint8_t clock_selector)
{

	if((RCC->CR & MSION_MASK) ^ (RCC->CR & MSIRDY_MASK)){
        clock_selector++;
        if (clock_selector > MSIRANGE_MAX)
        {
            clock_selector = 0;
        }
        
        // Clear current value
        RCC->CR &= ~(0b1111 << MSIRANGE_SHIFT);
        // Set desired speed
        RCC->CR |= clock_selector << MSIRANGE_SHIFT;
        SystemCoreClockUpdate();
        for(int i=0; i<clock_selector + 1; i++ ){
            toogle_led(GPIOC, GREEN_LED_PIN);
            systick_msec_delay(200);
            toogle_led(GPIOC, GREEN_LED_PIN);
            systick_msec_delay(200);
        }
	}
	return clock_selector;
}