#ifndef __UART_H_
#define __UART_H_

#include <stdint.h>
#include "stm32l4xx.h"

void uart_init(void);
int write (char*, int);

#endif // __UART_H