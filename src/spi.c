#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>




void spi_init(void)
{
    cli(); // Disable interrupts
    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;  // SPI pins on PC0-3

    PORTC.DIRSET = (PIN0_bm | PIN2_bm);    // SCK (PC0) and MOSI (PC2) output

    PORTA.OUTCLR = PIN1_bm;     // DISP_LATCH low
    PORTA.DIRSET = PIN1_bm;     // DISP_LATCH output
       
    SPI0.CTRLA = SPI_MASTER_bm;    // Master, /4 prescaler, MSB first
    SPI0.CTRLB = SPI_SSD_bm;       // Mode 0, client select disable, unbuffered
    SPI0.INTCTRL = SPI_IE_bm;      // Interrupt enable
    SPI0.CTRLA |= SPI_ENABLE_bm;   // Enable
    sei(); // Enable interrupts
}


void spi_write(uint8_t b)
{

    SPI0.DATA = b; // Write the byte to the SPI data register

    
}

ISR(SPI0_INT_vect)
{
    PORTA.OUTSET = PIN1_bm; // DISP_LATCH high
    PORTA.OUTCLR = PIN1_bm; // DISP_LATCH low
    SPI0.INTFLAGS = SPI_IF_bm; // Clear the interrupt flag
}


