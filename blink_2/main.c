/*
 *	Target: NUCLEO-L4R5ZI-P
 *	Description: program will turn ON LD1 while button B1 is pressed
 *
 */

#include "gpio.h"
#include "systick.h"



int main(void)
{
	uint8_t clock_selector = 0;
	systick_init(clock_selector);
	gpio_init();

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
