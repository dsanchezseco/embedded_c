#include "gpio.h"



void gpio_init(void){
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

	// initial status only RED on
	GPIOC->ODR &= ~GREEN_LED_PIN;
	GPIOB->ODR &= ~(RED_LED_PIN | BLUE_LED_PIN); 
	GPIOB->ODR |= RED_LED_PIN;
}

unsigned int read_button_status(void){
     return (GPIOC->IDR & BUTTON) >> BUTTON_BIT;
}

void toogle_led(GPIO_TypeDef* GPIO, uint32_t led_pin){
	GPIO->ODR ^= led_pin;
}