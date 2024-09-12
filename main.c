#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define FOSC 4915200 
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 

void main(void) {
    
    uart_Init (MYUBRR);
    fdevopen(uart_Transmit, uart_Receive);
    printf("%d", 5);
    
}
