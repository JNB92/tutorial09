#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"
#include "uart.h"
#include "timer.h"

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
    /** CODE: Write your code for Ex 9.3 within this ISR. */
    
    static uint8_t displayLeft = 1;  // start with left digit
    const uint8_t digitMap[] = {0b0000001, 0b1001111, 0b0010010, 0b0000110, 0b1001100, 0b0100100, 0b0100000, 0b0001111, 0b0000000, 0b0000100};

    // The first and second digits from the student number are '1' and '1' respectively
    const uint8_t FirstDigit = 0b1001111;
    const uint8_t SecondDigit = 0b1001111;

    if (displayLeft)
    {
        // Display first digit of student number on LHS of the 7-segment display
        spi_write(digitMap[FirstDigit]);
    }
    else
    {
        // Display second digit of student number on RHS of the 7-segment display
        spi_write(digitMap[SecondDigit]);
    }

    displayLeft = !displayLeft; // Toggle display side
    TCB0.INTFLAGS = TCB_CAPT_bm;
}
