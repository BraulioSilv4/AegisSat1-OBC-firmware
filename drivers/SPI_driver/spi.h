#ifndef SPI_H
#define SPI_H

#include "FreeRTOS.h"
#include "semphr.h"

void init_SPI();
int spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t len, uint32_t timeout);


#endif
