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
    
    static uint8_t toggle = 0;  
    
    uint8_t segment_mapping[] = {
        0b0000001, // 0
        0b1001111, // 1
        0b0010010, // 2
        0b0000110, // 3
        0b1001100, // 4
        0b0100100, // 5
        0b0100000, // 6
        0b0001111, // 7
        0b0000000, // 8
        0b0000100  // 9
    };

    if (toggle == 0)
    {
        
        spi_write(segment_mapping[1]); 

       
        toggle = 1;
    }
    else
    {
        
        spi_write(segment_mapping[1]);  

        
        toggle = 0;
    }

    
    TCB0.INTFLAGS = TCB_CAPT_bm;
}