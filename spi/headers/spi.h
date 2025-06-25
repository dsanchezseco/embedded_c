#ifndef __SPI_H_
#define __SPI_H_

#include <stdint.h>
#include "stm32l4xx.h"

void spib_gpio_init(void);
void spib_config(void);
void spib_transmit(uint16_t data);
// void spib_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

void max7219_send(uint8_t address, uint8_t data);
void max7219_send_digits(uint32_t data);

#endif // __SPI_H_