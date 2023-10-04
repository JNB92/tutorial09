#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void spi_init(void)
{
    // TODO: Initialize SPI0 for unbuffered mode
    // TODO: Enable required pins as outputs
    // TODO: Enable the SPI interrupt via the IE bit in INTCTRL
}

void spi_write(uint8_t b)
{
    // TODO: Write byte b out via the SPI interface
}

ISR(SPI0_INT_vect)
{
    // TODO: Handle the SPI interrupt and create a rising edge on the DISP LATCH net
}
