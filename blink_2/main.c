/*
*	Target: NUCLEO-L4R5ZI-P
*	Description: program will turn ON LD1 while button B1 is pressed
*
*/

#include <stdint.h>
#include "stm32l4xx.h"
// #include "stm32l4r5xx.h"

// Enable mask GPIOC
#define GPIOBEN				(1<<1)
#define GPIOCEN				(1<<2)

// PC7 mask | green user LED
#define GREEN_LED_BIT		(7)
#define PIN_C7				(1<<GREEN_LED_BIT)
#define GREEN_LED_PIN		PIN_C7

// PC_TODO mask | red user led
#define RED_LED_BIT			(14)
#define PIN_B14				(1<<RED_LED_BIT)
#define RED_LED_PIN			PIN_B14

// PC_TODO mask | blue user led
#define BLUE_LED_BIT		(7)
#define PIN_B7				(1<<BLUE_LED_BIT)
#define BLUE_LED_PIN		PIN_B7

// PC13 mask
#define BUTTON_BIT			(13)
#define PIN13				(1<<BUTTON_BIT)
#define BUTTON				PIN13


int main(void) {
	// Enable clock access to GPIO
	RCC->AHB2ENR |= GPIOBEN;
	RCC->AHB2ENR |= GPIOCEN;

	// Set output(01) mode for leds
	GPIOB->MODER &= ~(0x3U << (RED_LED_BIT * 2));
	GPIOB->MODER |= (0x1U << (RED_LED_BIT * 2));

	GPIOB->MODER &= ~(0x3U << (BLUE_LED_BIT * 2));
	GPIOB->MODER |= (0x1U << (BLUE_LED_BIT * 2));

	GPIOC->MODER &= ~(0x3U << (GREEN_LED_BIT * 2));
	GPIOC->MODER |= (0x1U << (GREEN_LED_BIT * 2));

	// Set input (00) mode for button
	GPIOC->MODER &= ~(0x3U << (BUTTON_BIT * 2));

	uint8_t counter = 1;

	// initial status only RED on
	GPIOC->ODR |= GREEN_LED_PIN;
	GPIOB->ODR &= ~(RED_LED_PIN | BLUE_LED_PIN); 
	GPIOB->ODR |= RED_LED_PIN;
	
	// main loop
	while(1) {
		// button status, read registry then shift to keep only relevant bit (0 or 1)
		unsigned int button_status = (GPIOC->IDR & BUTTON) >> BUTTON_BIT;

		// if button pressed flip RED led registry to change blink effect
		if(button_status){
			GPIOC->ODR |= GREEN_LED_PIN; // signal button pressed
			GPIOB->ODR ^= RED_LED_PIN;
			// simple debounce
			for(int i = 0; i<50000; i++){}
			GPIOC->ODR &= ~GREEN_LED_PIN;
		}

		// only if button pressed turn on led
		counter = counter << 1;
		GPIOB->ODR ^= (RED_LED_PIN | BLUE_LED_PIN);

		for(int i = 0; i<50000; i++){}
	}
}
