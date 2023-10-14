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
        volatile uint8_t segs [] = {
        0x08,0x6B,0x44,0x41,0x23,0x11,0x10,0x4B,0x00,0x01
    };

    volatile uint8_t digit1 = 1;
    volatile uint8_t digit2 = 1;

    
    static int digit = 0;
    if (digit) { 
        spi_write(segs[digit1] | (0x01 << 7)); 
    } else {
        spi_write(segs[digit2]);
    }
    digit = !digit;
    TCB0.INTFLAGS = TCB_CAPT_bm;
}