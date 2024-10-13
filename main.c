#define FOSC 4915200 
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "ADC.h"
#include "OLED.h"
#include "SPI.h"


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 


void main(void){   

    uart_Init (MYUBRR);
    SRAM_init();
    
    fdevopen(uart_Transmit, uart_Receive);
    init_clock(); 
    volatile char *adc = (char *)0x1400;
    uint8_t x_start = check_ADC(2,adc);
    uint8_t y_start = check_ADC(3,adc);

    mcp_init();
    mcp_set_mode(LOOPBACK_MODE);
    printf("mode: %x\r\n", mcp_read(CANSTAT));
    mcp_write(MCP_TXB0SIDH, 0xA7);
    mcp_request_to_send_buffer0();
    uint8_t byte = mcp_read(MCP_RXB0SIDH);
    printf("mottar:  %x\r\n", byte);

    



    
    //Need to set CAN to configuration mode before i start
    
    //init_menu(adc, x_start, y_start);


}


