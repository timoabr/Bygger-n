#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"

#define FOSC 4915200 
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 

void main(void) {
    
    uart_Init (MYUBRR);
    fdevopen(uart_Transmit, uart_Receive);
    printf("\r\n\n\n\n\n");
    SRAM_init();
    SRAM_test();
    
}
