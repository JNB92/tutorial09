#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void spi_init(void)
{
    PORTC.DIRSET = (PIN0_bm | PIN2_bm); // Set MOSI and SCK as output
    PORTA.OUTSET = PIN1_bm;
    PORTA.DIRSET = PIN1_bm; // Set DISP_LATCH as output
    
    PORTB.OUTCLR = PIN1_bm;
    PORTB.DIRSET = PIN1_bm; // Set DISP_EN as output


    SPI0.CTRLA = SPI_MASTER_bm; // Set SPI to master mode
    SPI0.CTRLB = SPI_SSD_bm;
    SPI0.INTCTRL = SPI_IE_bm; // Enable SPI interrupts
    SPI0.CTRLA |= SPI_ENABLE_bm; // Enable SPI and enable buffer mode
    SPI0.CTRLB &= ~SPI_BUFEN_bm; // Disable buffer mode
}

void spi_write(uint8_t b)
{
    // Wait until SPI is free
    while (!(SPI0.INTFLAGS & SPI_IF_bp));

    // Send byte
    SPI0.DATA = b;
}

ISR(SPI0_INT_vect)
{
    // Create a rising edge on the DISP LATCH net
    PORTA.OUTSET = PIN1_bm;
    _delay_us(1); // Add a short delay to ensure the latch captures the data
    PORTA.OUTCLR = PIN1_bm;
    
    // Clear the interrupt flag
    SPI0.INTFLAGS = SPI_IF_bm;
}
