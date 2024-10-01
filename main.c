#define FOSC 4915200 
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "usart.h"
#include "ADC.h"


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 


void main(void) {
    
    uart_Init (MYUBRR);
    SRAM_init();
    fdevopen(uart_Transmit, uart_Receive);
    init_clock(); 
    volatile char *adc = (char *)0x1400;
        
while(1){

        print_Joy_dir(adc);

        _delay_us(1000);

    }

}

