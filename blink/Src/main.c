/*
*	Target: NUCLEO-L4R5ZI-P
*	Description: program will turn ON LD1 while button B1 is pressed
*
*/


// peripherals
#define PERIPH_BASE			(0x40000000)

// AHB2 (GPIOC)
#define AHB2PERIPH_OFFSET 	(0x08000000)
#define AHB2PERIPH_BASE 	(PERIPH_BASE + AHB2PERIPH_OFFSET)

// GPIOC
#define GPIOC_OFFSET		(0x00000800)
#define GPIOC_BASE			(AHB2PERIPH_BASE + GPIOC_OFFSET)

// RCC
#define RCC_OFFSET			(0x00021000)
#define RCC_BASE			(PERIPH_BASE + RCC_OFFSET)

// Offset for AHB2
#define RCC_AHB2ENR_OFFSET	(0x4CUL)
// Address of AHB2ENR
#define RCC_AHB2ENR			(*(volatile unsigned int *) (RCC_BASE + RCC_AHB2ENR_OFFSET))

// Offset for Mode register
#define MODER_OFFSET		(0x00UL)
#define GPIOC_MODER			(*(volatile unsigned int *) (GPIOC_BASE + MODER_OFFSET))

// Output data register
#define ODR_OFFSET			(0x14UL)
#define	GPIOC_ODR			(*(volatile unsigned int *) (GPIOC_BASE + ODR_OFFSET))

// Input data register
#define IDR_OFFSET			(0x10UL)
#define GPIOC_IDR			(*(volatile unsigned int *) (GPIOC_BASE + IDR_OFFSET))

// Enable mask GPIOC
#define GPIOCEN				(1<<2)

// PC7 mask
#define LED_BIT				(7)
#define PIN7				(1<<LED_BIT)
#define LED_PIN				PIN7

// PC13 mask
#define BUTTON_BIT			(13)
#define PIN13				(1<<BUTTON_BIT)
#define BUTTON				PIN13


int main(void) {
	// Enable clock access to GPIOC
	RCC_AHB2ENR |= GPIOCEN;

	// Set output(01) mode for led
	GPIOC_MODER &= ~(0x3U << (LED_BIT * 2));
	GPIOC_MODER |= (0x1U << (LED_BIT * 2));

	// Set input (00) mode for button
	GPIOC_MODER &= ~(0x3U << (BUTTON_BIT * 2));

	// main loop
	while(1) {
		// button status, read registry then shift to keep only relevant bit (0 or 1)
		unsigned int button_status = (GPIOC_IDR & BUTTON) >> BUTTON_BIT;
		// only if button pressed turn on led
		if (button_status){
			// LED ON
			GPIOC_ODR |= LED_PIN;
		}else{
			// LED OFF
			GPIOC_ODR &= ~LED_PIN;
		}
	}
}
