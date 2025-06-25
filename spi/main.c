/*
 *	Target: NUCLEO-L4R5ZI-P
 *	Description: program to test SPI functionality connecting to a MAX7218
 *
 */

#include "spi.h"

uint32_t seconds_to_ddhhmmss(uint32_t seconds);

int main(void)
{

    // prepare SPI before sending data
    spib_gpio_init();
    spib_config();

    max7219_send(0x0F, 0x0F); // Display test: ON
    for (volatile int i = 0; i < 500000; ++i)
    {
    }
    for (int i = 0; i < 8; i++)
    {
        max7219_send(i + 1, i);
    }

    max7219_send(0x0F, 0x00); // Display test: OFF

    // main loop
    uint32_t counter = 0;
    while (1)
    {
        max7219_send_digits(counter++);
        for (volatile int i = 0; i < 250000; ++i) //TODO: true 1 sec delay
        {
        }
    }
}
