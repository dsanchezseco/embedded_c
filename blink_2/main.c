/*
 *	Target: NUCLEO-L4R5ZI-P
 *	Description: program will turn ON LD1 while button B1 is pressed
 *
 */

#include "gpio.h"

int main(void)
{

	gpio_init();

	// main loop
	while (1)
	{
		// button status, read registry then shift to keep only relevant bit (0 or 1)
		unsigned int button_status = read_button_status();

		// if button pressed flip RED led registry to change blink effect
		if (button_status)
		{
			toogle_led(GPIOC, GREEN_LED_PIN);
			toogle_led(GPIOB, RED_LED_PIN);
			// simple debounce
			for (int i = 0; i < 50000; i++)
			{
			}
			toogle_led(GPIOC, GREEN_LED_PIN);
		}
		toogle_led(GPIOB, RED_LED_PIN);
		toogle_led(GPIOB, BLUE_LED_PIN);

		for (int i = 0; i < 50000; i++)
		{
		}
	}
}
