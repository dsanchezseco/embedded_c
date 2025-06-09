/*
 *	Target: NUCLEO-L4R5ZI-P
 *	Description: program will turn ON LD1 while button B1 is pressed
 *
 */

#include "gpio.h"
#include "systick.h"

#define MSION_MASK 0
#define MSIRDY_MASK 1
#define MSIRANGE_SHIFT 4
#define MSIRANGE_MAX 11

uint8_t cycle_clock_speed(uint8_t clock_selector)
{

	if((RCC->CR & MSION_MASK) ^ (RCC->CR & MSIRDY_MASK)){
	toogle_led(GPIOC, GREEN_LED_PIN);
	clock_selector++;
	if (clock_selector > MSIRANGE_MAX)
	{
		clock_selector = 0;
	}

	// Clear current value
	RCC->CR &= ~(0b1111 << MSIRANGE_SHIFT);
	// Set desired speed
	RCC->CR |= clock_selector << MSIRANGE_SHIFT;
	systick_msec_delay(500);
	toogle_led(GPIOC, GREEN_LED_PIN);
	}
	return clock_selector;
}

int main(void)
{

	gpio_init();
	// init clock_selector at 4MHz
	uint8_t clock_selector = 7;

	// Tell MSI clock to use MSIRANGE from CR registry (0=CR; 1=CSR)
	RCC->CR |= (1U << 3);
	// Clear current value
	RCC->CR &= ~(0b1111 << MSIRANGE_SHIFT);
	// Set desired speed
	RCC->CR |= clock_selector << MSIRANGE_SHIFT;

	// main loop
	while (1)
	{
		// button status, read registry then shift to keep only relevant bit (0 or 1)
		unsigned int button_status = read_button_status();

		// if button pressed flip RED led registry to change blink effect
		if (button_status)
		{

			clock_selector = cycle_clock_speed(clock_selector);
			// simple debounce
			systick_msec_delay(500);
		}
		toogle_led(GPIOB, RED_LED_PIN);
		toogle_led(GPIOB, BLUE_LED_PIN);

		systick_msec_delay(1000);
	}
}
