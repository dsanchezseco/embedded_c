#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32l4xx.h"

// Enable mask GPIOC
#define GPIOBEN				(1<<1)
#define GPIOCEN				(1<<2)

// PC7 mask | green user LED
#define GREEN_LED_BIT		(7)
#define PIN_C7				(1<<GREEN_LED_BIT)
#define GREEN_LED_PIN		PIN_C7

// PB14 mask | red user led
#define RED_LED_BIT			(14)
#define PIN_B14				(1<<RED_LED_BIT)
#define RED_LED_PIN			PIN_B14

// PB7 mask | blue user led
#define BLUE_LED_BIT		(7)
#define PIN_B7				(1<<BLUE_LED_BIT)
#define BLUE_LED_PIN		PIN_B7

// PC13 mask
#define BUTTON_BIT			(13)
#define PIN_C13				(1<<BUTTON_BIT)
#define BUTTON				PIN_C13


void gpio_init(void);
unsigned int read_button_status(void);
void toogle_led(GPIO_TypeDef*, uint32_t);

#endif // GPIO_H_