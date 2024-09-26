#define FOSC 4915200 
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "usart.h"


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 


void main(void) {
    
    uart_Init (MYUBRR);
    fdevopen(uart_Transmit, uart_Receive);
    printf("\r\n\n\n\n\n");

    //cli();

    //DDRD |= (1<<PD5);
    DDRD |= (1<<PD4);
    //DDRB |= (1<<PB0);

    TCCR3A |= (1<<WGM30) | (1<<WGM31); //Using 8 bit fast mode based on table 56 page 
    TCCR3B |= (1<<CS30) | (1<<WGM32) | (1<<WGM33); //also 8 bit fast mode but also table 57 so clk /1 
    TCCR3A |= (0<<COM3A1) | (1<<COM3A0); // (1<<COM3B1) | (1<<COM3B0); //Table 55 set OCnA/OcnB when counting up and clear when counting down.

    OCR3A = 0;
    //0b0111111;

    

    SRAM_init();
    SRAM_test();
}
