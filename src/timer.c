#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include <util/delay.h>
#include <stdint.h>

void timer_init(void)
{
    cli();
    TCB0.CTRLB = TCB_CNTMODE_INT_gc; // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = 3333;                // Set interval for 1ms (3333 clocks @ 3.3 MHz)
    TCB0.INTCTRL = TCB_CAPT_bm;      // CAPT interrupt enable
    TCB0.CTRLA = TCB_ENABLE_bm;      // Enable
    sei();
}

ISR(TCB0_INT_vect)
{
    
    static uint8_t display_toggle = 0; 

    // Truth table mapping for 7-segment display digits 0-9
    uint8_t digit_map[] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x04};

    // Replace 1 and 2 with the first and second digits of your student number
    uint8_t first_digit = 1;
    uint8_t second_digit = 2;

    if (display_toggle == 0)
    {
        spi_write(digit_map[first_digit]);  // Display first digit on LHS
        _delay_us(10); // Small delay to ensure data latching
        spi_write(digit_map[second_digit]); // Display second digit on RHS
    }
    else
    {
        spi_write(digit_map[second_digit]); // Display second digit on LHS
        _delay_us(10); // Small delay to ensure data latching
        spi_write(digit_map[first_digit]);  // Display first digit on RHS
    }

    display_toggle ^= 1; // Toggle the display state for the next ISR invocation

    TCB0.INTFLAGS = TCB_CAPT_bm;
}