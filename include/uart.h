#include <stdint.h>
#include <avr/io.h>

void uart_init(void);
char uart_getc(void);
void uart_putc(char c);