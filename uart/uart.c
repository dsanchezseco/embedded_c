#include "uart.h"

/* LPUART1
 *  TX -> PG7 (AF8)
 *  RX -> PG8 (AF8)
 * 
 *  LPUART1 is connectod to the ST-LINK using the pins PG7 & PG8
 *  it can be used to send back messages via serial for debug.
 * 
 *  GPIO-G is not powered by default, so it need to be enable 
 *  for it to work.
 */

#define DBG_UART_BAUDRATE 115200
#define SYS_FREQ 4000000 // 4MHz (defaulf speed)
#define APB1_CLK SYS_FREQ

void uart_init(void)
{

    // enable power registry
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    // give power to GPIOG & GPIOH
    PWR->CR2 |= PWR_CR2_IOSV;
    
    // enable GPIOG clock access
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOGEN;

    // enable UART clock access
    RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;

    // set GPIO PINS to alternate mode AF8
    // PG7 alternate
    GPIOG->MODER &= ~(GPIO_MODER_MODE7_Msk);
    GPIOG->MODER |= (0b10 << GPIO_MODER_MODE7_Pos);
    // PG7 AF8 (this one is on GPIOG->AFR[0] = AFRL <- pin 0-7)
    GPIOG->AFR[0] &= ~(GPIO_AFRL_AFSEL7_Msk);
    GPIOG->AFR[0] |= (0b1000 << GPIO_AFRL_AFSEL7_Pos);
    
    // PG8 alternate
    GPIOG->MODER &= ~(GPIO_MODER_MODE8_Msk);
    GPIOG->MODER |= (0b10 << GPIO_MODER_MODE8_Pos);
    // PG8 AF8 (this one is on GPIOG->AFR[1] = AFRH <- pin 8-15)
    GPIOG->AFR[1] &= ~(GPIO_AFRH_AFSEL8_Msk);
    GPIOG->AFR[1] |= (0b1000 << GPIO_AFRH_AFSEL8_Pos);
    
    LPUART1->CR1 = 0;
    // set the baudrate with preescaler 0
    LPUART1->BRR = 256 * APB1_CLK / DBG_UART_BAUDRATE;

    // finally enable LPUART TX, RX and Enable
    LPUART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

static void uart_write(uint8_t byte)
{
    // wait till TX Data registry is empty
    while (!(LPUART1->ISR & USART_ISR_TXE_TXFNF))
    {
    }
    LPUART1->TDR = 0xFF & byte;
}

int __io_putchar(char ch)
{
    uart_write((uint8_t) ch);
    return ch;
}

int write(char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        __io_putchar(ptr[i]);
    }
    return len;
}
