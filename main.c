#define FOSC 4915200 
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "usart.h"
#include "ADC.h"
#include "OLED.h"


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1 


void main(void) {   

    uart_Init (MYUBRR);
    SRAM_init();
    // Set PB2 as input for joystick button
    DDRB &= ~(1 << PB2);

    //Enable internal pull-up resistor on PB2
    PORTB |= (1 << PB2);

    int is_button_pressed()
    {
        //Read the button state
        if(!(PINB & (1 << PB2)))
        {
            return 1;
        }
        return 0;
    }
    fdevopen(uart_Transmit, uart_Receive);
    //SRAM_test();
    init_clock(); 
    volatile char *adc = (char *)0x1400;
    uint8_t pagePointerI=2;
    displayMenu(pagePointerI);
    uint8_t pagePointerJ;
while(1)
{
    pagePointerJ = print_Joy_dir(adc);
    printf("y: %02d  ", get_joystick_y(adc));
    printf("pagePointer:%02d \n\r", pagePointerJ);
    if(pagePointerJ != pagePointerI)
    {
        displayMenu(pagePointerJ);
        pagePointerI = pagePointerJ;
    }
    if(is_button_pressed() && pagePointerI==2)
        subMenu1();
    else if(is_button_pressed() && pagePointerI==3)
        subMenu2();
    else if(is_button_pressed() && pagePointerI==4)
        subMenu3();
}
        
        
/*while(1){
        
        printf("x: %02d  ", get_joystick_x(adc));
        printf("y: %02d  ", get_joystick_y(adc));
        printf("left: %02d  ", get_leftslider(adc));
        printf("right: %02d \n\r", get_rightslider(adc));
        print_Joy_dir(adc);
        
        

        _delay_us(1000);

}*/
    
}


//TRIAL 1
/*
    volatile char *adc = (char *)0x1400;
        
        
while(1){
        
        printf("x: %02d  ", get_joystick_x(adc));
        printf("y: %02d  ", get_joystick_y(adc));
        printf("left: %02d  ", get_leftslider(adc));
        printf("right: %02d ", get_rightslider(adc));
        print_Joy_dir(adc);
        
        

        _delay_us(1000);

} */


//TRIAL 2