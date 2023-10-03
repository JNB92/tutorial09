#include "uart.h"
#include "timer.h"

/** Tutorial 09

INTRODUCTION:

In this week's tutorial you will be working with the USART0 and
SPI0 peripherals to read/write data via the USB-UART interface
and to control the 7-segment display.

Interfacing with these hardware devices on the QUTy is a core
requirement for Assessment 2.
*/

/** EX: 9.0

We have declared some functions in "uart.c" and corresponding function
prototypes in "uart.h":

   void uart_init(void);      // Initialise the UART peripheral to 9600 baud, 8N1
   void uart_putc(uint8_t c); // Blocking write of byte c to UART
   void uart_getc(uint8_t c); // Blocking read of byte c from UART

TASK: Complete the function "void uart_puts(char* string)" in "uart.c"
which takes as an argument a pointer to a string,
and transmits this string via the UART using uart_putc.
*/

/** CODE: Write your code for Ex 9.0 in uart.c. */

int main(void)
{
    uart_init();

    /** EX: 9.1

    TASK: Write code below that will call uart_puts() to print
    your student number via the UART interface.

    The string you print should begin with a leading 'n' and
    should be terminated with a newline character '\n';
    */


    /** CODE: Write your code for Ex 9.1 above this line. */

    /** EX: 9.2

    Create two new files:

        src/spi.c
        include/spi.h

    TASK:

    1. In "spi.c", declare and implement a function spi_init() that will initialise
       SPI0 in unbuffered mode, such that data can be written to the shift register that
       controls the 7-segment display.

       This function should also enable the SPI interrupt via the IE bit in INTCTRL.
    2. Declare and implement a function spi_write(uint8_t b) which will write the
       byte b out via the SPI interface.
    3. Declare and implement an ISR that will handle the SPI interrupt enabled
       above, which also creates a rising edge on the DISP LATCH net.

       You may need to add some code to spi_init() to enable the required pins as outputs.

    Declare prototypes for these functions in "spi.h" and include "spi.h at the
    top of "tutorial09.c".

    Once this exercise is complete, uncomment the lines below.
    The 7-segment display should be blank after this code executes.
    */

    /** CODE: Write your code for Ex 9.2 in spi.c and spi.h. */

    /** TODO: Remove this line when Ex 9.2 is complete.

    spi_init();       // Initialise SPI
    spi_write(0xFF);  // Clear display

    /** TODO: Remove this line when Ex 9.2 is complete. */

    /** EX: 9.3

    We have declared some functions in "timer.c" and corresponding function
    prototypes in "timer.h":

        void timer_init(void); // Initialise TCB0 to produce interrupts every 1ms

    TASK:

    Complete the ISR declared in "timer.c" to display simultaneously:
    - the first digit of your student number on the LHS of the 7-segment display
    - the second digit of your student number on the RHS of this display

    after timer_init() is called.

    TIP: You should swap which digit you are displaying every time a new interrupt occurs.

    TIP: Declare a static variable so you know which digit to display on each iteration.

    TIP: Refer to the following truth table for 7-segment digit mapping.
    (remember to check which output Q0..Q6 maps to which segment on the QUTy)

       ABCDEFG
    0: 0000001
    1: 1001111
    2: 0010010
    3: 0000110
    4: 1001100
    5: 0100100
    6: 0100000
    7: 0001111
    8: 0000000
    9: 0000100
    */

    /** CODE: Write your code for Ex 9.3 in timer.c. */

    /** EX: 9.4

    TASK: Write code below that will call timer_init() only after
    the character 'a' has been received via the UART interface.
    */


    /** CODE: Write your code for Ex 9.4 above this line. */

    while (1)
        ; // Loop indefinitely
}

