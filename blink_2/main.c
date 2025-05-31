/*
*	Target: NUCLEO-L4R5ZI-P
*	Description: program will turn ON LD1 while button B1 is pressed
*
*/

#ifndef HEADERS
#define HEADERS
	#include <stdint.h>
	#include <main.h>
#endif


int main(void) {
	// Enable clock access to GPIO
	RCC_AHB2ENR |= GPIOBEN;
	RCC_AHB2ENR |= GPIOCEN;

	// Set output(01) mode for leds
	GPIOB_MODER &= ~(0x3U << (RED_LED_BIT * 2));
	GPIOB_MODER |= (0x1U << (RED_LED_BIT * 2));

	GPIOB_MODER &= ~(0x3U << (BLUE_LED_BIT * 2));
	GPIOB_MODER |= (0x1U << (BLUE_LED_BIT * 2));

	GPIOC_MODER &= ~(0x3U << (GREEN_LED_BIT * 2));
	GPIOC_MODER |= (0x1U << (GREEN_LED_BIT * 2));

	// Set input (00) mode for button
	GPIOC_MODER &= ~(0x3U << (BUTTON_BIT * 2));

	uint8_t counter = 1;

	// initial status only RED on
	GPIOC_ODR &= ~GREEN_LED_PIN;
	GPIOB_ODR &= ~(RED_LED_PIN | BLUE_LED_PIN); 
	GPIOB_ODR |= RED_LED_PIN;
	
	// main loop
	while(1) {
		// button status, read registry then shift to keep only relevant bit (0 or 1)
		unsigned int button_status = (GPIOC_IDR & BUTTON) >> BUTTON_BIT;

		// if button pressed flip RED led registry to change blink effect
		if(button_status){
			GPIOC_ODR |= GREEN_LED_PIN; // signal button pressed
			GPIOB_ODR ^= RED_LED_PIN;
			// simple debounce
			for(int i = 0; i<50000; i++){}
			GPIOC_ODR &= ~GREEN_LED_PIN;
		}

		// only if button pressed turn on led
		counter = counter << 1;
		GPIOB_ODR ^= (RED_LED_PIN | BLUE_LED_PIN);

		for(int i = 0; i<50000; i++){}
	}
}
