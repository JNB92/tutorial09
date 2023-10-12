#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



void spi_init(void)
{
    cli(); // Disable interrupts
    PORTC.DIRSET = (PIN0_bm | PIN2_bm); // Set MOSI and SCK as output

    PORTA.OUTCLR = PIN1_bm; // Set DISP_LATCH low
    // PORTA.OUTSET = PIN1_bm; // Set DISP_LATCH high
    PORTA.DIRSET = PIN1_bm; // Set DISP_LATCH as output

    PORTB.DIRSET = PIN1_bm; // Set DISP_BLANK as output

    SPI0.CTRLA = SPI_MASTER_bm; // Set SPI to master mode
    SPI0.CTRLB = SPI_SSD_bm;
    SPI0.INTCTRL = SPI_IE_bm; // Enable SPI interrupts
    SPI0.CTRLA |= SPI_ENABLE_bm; // Enable SPI
    sei(); // Enable interrupts
}


void spi_write(uint8_t b)
{
    // Write the byte to the data register to transmit
    SPI0.DATA = b;
    
    // Wait for transmission to complete
    while (!(SPI0.INTFLAGS & SPI_IF_bm));
}

ISR(SPI0_INT_vect)
{
    // Create a rising edge on the DISP LATCH net
    //PORTA.OUTCLR = PIN1_bm;
    
    PORTA.OUTSET = PIN1_bm;
    // _delay_us(1); // Add a short delay to ensure the latch captures the data
    
    // Clear the interrupt flag
    SPI0.INTFLAGS = SPI_IF_bm;
}
