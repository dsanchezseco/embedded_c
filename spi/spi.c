#include "spi.h"

/* Using SPI to connect to a MAX7219 8x7 segments
 *
 *  SPI_B / SPI3 -> APB1
 *  MOSI    -> PB5 (AF6)
 *  SCK     -> PB3 (AF6)
 *  NSS     -> PA4 (AF6)
 *  MISO    -> PB4 (AF6)
 */

void spib_gpio_init(void)
{
    // Enable GPIOA and GPIOB clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // --- PA4: Manual Chip Select (CS) ---
    GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk);
    GPIOA->MODER |= GPIO_MODER_MODE4_0;                  // Output mode
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT4);                 // Push-pull
    GPIOA->OSPEEDR |= (0x3 << GPIO_OSPEEDR_OSPEED4_Pos); // High speed
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD4_Msk);             // No pull-up/down
    GPIOA->BSRR = GPIO_BSRR_BS4;                         // Set high (inactive)

    // --- PB3: SCK (SPI3_SCK, AF6) ---
    GPIOB->MODER &= ~(GPIO_MODER_MODE3_Msk);
    GPIOB->MODER |= GPIO_MODER_MODE3_1; // Alternate function mode
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL3_Msk);
    GPIOB->AFR[0] |= (6 << GPIO_AFRL_AFSEL3_Pos);        // AF6
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT3);                 // Push-pull
    GPIOB->OSPEEDR |= (0x3 << GPIO_OSPEEDR_OSPEED3_Pos); // High speed
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3_Msk);             // Floating (no pull)

    // --- PB4: MISO (SPI3_MISO, AF6) ---
    GPIOB->MODER &= ~(GPIO_MODER_MODE4_Msk);
    GPIOB->MODER |= GPIO_MODER_MODE4_1;
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL4_Msk);
    GPIOB->AFR[0] |= (6 << GPIO_AFRL_AFSEL4_Pos);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT4);                 // Push-pull
    GPIOB->OSPEEDR |= (0x3 << GPIO_OSPEEDR_OSPEED4_Pos); // High speed
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD4_Msk);
    GPIOB->PUPDR |= (0x1 << GPIO_PUPDR_PUPD4_Pos); // Pull-up

    // --- PB5: MOSI (SPI3_MOSI, AF6) ---
    GPIOB->MODER &= ~(GPIO_MODER_MODE5_Msk);
    GPIOB->MODER |= GPIO_MODER_MODE5_1;
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL5_Msk);
    GPIOB->AFR[0] |= (6 << GPIO_AFRL_AFSEL5_Pos);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT5);                 // Push-pull
    GPIOB->OSPEEDR |= (0x3 << GPIO_OSPEEDR_OSPEED5_Pos); // High speed
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD5_Msk);             // Floating (no pull)
}

void max7219_send(uint8_t, uint8_t);
void max7219_init(void);

void spib_config(void)
{
    // enable SPI3/B clock access
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;

    // set clock to fclk/2 -> 2MHz
    SPI3->CR1 &= ~(SPI_CR1_BR_Msk);

    // set CPOL and CPHA both to 0
    SPI3->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);

    // send Most Significant Bit first
    SPI3->CR1 &= ~(SPI_CR1_LSBFIRST);

    // set mode to master
    SPI3->CR1 |= SPI_CR1_MSTR;

    // set 1-line output only mode
    SPI3->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE);

    // set data lenght
    // 16 bit = 0b1111
    SPI3->CR2 &= ~SPI_CR2_DS_Msk;
    SPI3->CR2 |= (0b1111 << SPI_CR2_DS_Pos);

    // set manual slave select
    SPI3->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    // enable SPI
    SPI3->CR1 |= SPI_CR1_SPE;

    max7219_init();
}

void spib_transmit(uint16_t data)
{
    while (!(SPI3->SR & SPI_SR_TXE))
        ;

    // send data
    SPI3->DR = data;

    // wait till transmission finished
    while (!(SPI3->SR & SPI_SR_TXE))
        ;
    while (SPI3->SR & SPI_SR_BSY)
        ;
}

void cs_enable(void)
{
    GPIOA->BRR |= GPIO_BRR_BR4;
}
void cs_disable(void)
{
    GPIOA->BSRR |= GPIO_BSRR_BS4;
    for (volatile int i = 0; i < 100; ++i)
    {
    }
}

void max7219_init(void)
{
    max7219_send(0x0F, 0x00); // Display test: off
    max7219_send(0x0C, 0x01); // Shutdown register: normal operation
    max7219_send(0x0B, 0x07); // Scan limit: display all 8 digits
    max7219_send(0x09, 0xFF); // Decode mode: BCD for all digits
    max7219_send(0x0A, 0x08); // Intensity

    // Clear digits
    for (uint8_t i = 1; i <= 8; i++)
        max7219_send(i, 0x0F); // Display "blank" (or 0x0F for clear)
}

void max7219_send(uint8_t address, uint8_t data)
{
    cs_enable();
    spib_transmit((address << 8) | data);
    cs_disable();
}

void max7219_send_digits(uint32_t data)
{
    // first digit is address 0x1, address 0x0 is No-Op
    for (int i = 1; i < 9; i++)
    {
        max7219_send(i, (data % 10));
        data = data / 10;
    }
}