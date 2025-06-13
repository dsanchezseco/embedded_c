/*
 *	Target: NUCLEO-L4R5ZI-P
 *	Description: program to test UART functionality and ST-LINK
 *  using the LPUART1 as it is connected by default to ST-LINK
 *  for debugging purposes
 *
 */

#include "uart.h"

int main(void)
{

    // prepare UART before sending data
    uart_init();

    // main loop
    while (1)
    {
        write("Hello (embedded) world!\r\n", 25);
        for (int i = 0; i < 200000; i++)
        {
        }
    }
}
