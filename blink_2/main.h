// peripherals
#define PERIPH_BASE			(0x40000000)

// AHB2 (GPIOC)
#define AHB2PERIPH_OFFSET 	(0x08000000)
#define AHB2PERIPH_BASE 	(PERIPH_BASE + AHB2PERIPH_OFFSET)

// GPIOB
#define GPIOB_OFFSET		(0x00000400)
#define GPIOB_BASE			(AHB2PERIPH_BASE + GPIOB_OFFSET)

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
#define GPIOB_MODER			(*(volatile unsigned int *) (GPIOB_BASE + MODER_OFFSET))
#define GPIOC_MODER			(*(volatile unsigned int *) (GPIOC_BASE + MODER_OFFSET))

// Output data register
#define ODR_OFFSET			(0x14UL)
#define GPIOB_ODR			(*(volatile unsigned int *) (GPIOB_BASE + ODR_OFFSET))
#define	GPIOC_ODR			(*(volatile unsigned int *) (GPIOC_BASE + ODR_OFFSET))


// Input data register
#define IDR_OFFSET			(0x10UL)
#define GPIOC_IDR			(*(volatile unsigned int *) (GPIOC_BASE + IDR_OFFSET))

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