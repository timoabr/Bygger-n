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

    

    SRAM_init();
    SRAM_test();

    typedef struct
    {
        int8_t x;
        int8_t y;
    } JoystickPosition;

    typedef enum{
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NEUTRAL
    }JoystickDirection;

    JoystickPosition getJoystickPosition()
    {
        volatile char *adc = (char *)0x1400;
        adc[0] = 0x06;
        _delay_us(100);

        adc[0] = 0x07;
        _delay_us(100);
        uint8_t x_value = adc[0];
        uint8_t y_value = adc[0];

        JoystickPosition position;
        position.x = ((int16_t)x_value - 128) * 100/128;
        position.y = ((int16_t)y_value - 128) * 100/128;

        return position;
    }
    JoystickDirection getJoystickDirection(JoystickPosition position)
    {
        int8_t threshold = 30;
        if(position.x > threshold)
        {
            return RIGHT;
        }
        else if(position.x < - threshold)
        {
            return LEFT;
        }
        else if(position.y < threshold)
        {
            return UP;
        }
        else if(position.y < -threshold)
        {
            return DOWN;
        }
        else
        {
            return NEUTRAL;
        }
    }
    
    while(1)
    {
        JoystickPosition position = getJoystickPosition();
        JoystickDirection direction = getJoystickDirection(position);

        //Print the joystick position
        printf("Joystick postion x = %d%%, Y = %d%%\n\r", position.x, position.y);

        //Print the joystick direction
        switch(direction)
        {
            case LEFT:
                printf("Direction: Left   ");
                break;
            case RIGHT:
                printf("Direction: Right   ");
                break;
            case UP:
                printf("Direction: Up   ");
                break;
            case DOWN:
                printf("Direction: Down   ");
                break;
            case NEUTRAL:
                printf("Direction: Neutral");
                break;
        }
        _delay_ms(700);
    }

        /*volatile char *adc = (char *) 0x1400; //adc start adresse    
        
        while(1){
        adc[0] = 0x04; //4 = left slider // sier til adc at vi skal hente infor fra AIN1 (5 , 6 og 7 for de andre)

        _delay_us(1000); //potesnielt ikke nødvendig
        

        uint8_t value_left =adc[0]; //leser 8-bit data fra adc basert på channel valgt
        uint8_t value_right =adc[0]; //leser 8-bit data fra adc basert på channel valgt
        uint8_t Joystick =adc[0]; //leser 8-bit data fra adc basert på channel valgt


        adc[0] = 0x05;
        _delay_us(100);
        uint8_t y_value = adc [0];_SLIDER: %02d   ", value_left); //printer value til putty
        printf("RIGHT_SLIDER: %02d   ", value_right); //printer value til putty
        printf("JOYSTICK: %02d\r\r\n", Joystick); //printer value til putty

        _delay_ms(2000); //for at det skal bli oversiktlig
        }*/


    



    SRAM_test();
    }

