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
#include "mcp.h"
#include "can.h"


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
    mcp_set_mode(MODE_LOOPBACK);
    printf("mode: %x\r\n", mcp_read(MCP_CANSTAT));
    message_t message1 = make_message(1,6,"hallo");
    message_print(message1);
    can_write(&message1);
    message_t message2 = can_recieve();
    message_print(message2);



    

    



    
    //Need to set CAN to configuration mode before i start
    
    //init_menu(adc, x_start, y_start);


}


/*mcp_write(MCP_TXB0SIDH, 0xA7);
    uint8_t byte1 = mcp_read(MCP_TXB0SIDH);
    printf("motta1:  %x\r\n", byte1);
    _delay_ms(10);
    mcp_request_to_send(0);

    _delay_ms(10);
    uint8_t byte = mcp_read(MCP_RXB0SIDH);
    printf("mottar:  %x\r\n", byte);
    _delay_ms(2000);
    printf("\n\r");
    printf("\n\r");
    printf("\n\r");
    _delay_ms(2000);
*/