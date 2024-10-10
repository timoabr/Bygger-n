#include "ADC.h"
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "OLED.h"

void init_clock(){

    //DDRD |= (1<<PD5);
    DDRD |= (1<<PD4);
    //DDRB |= (1<<PB0);

    TCCR3A |= (1<<WGM30) | (1<<WGM31); //Using 8 bit fast mode based on table 56 page 
    TCCR3B |= (1<<CS30) | (1<<WGM32) | (1<<WGM33); //also 8 bit fast mode but also table 57 so clk /1 
    TCCR3A |= (0<<COM3A1) | (1<<COM3A0); // (1<<COM3B1) | (1<<COM3B0); //Table 55 set OCnA/OcnB when counting up and clear when counting down.

    OCR3A = 0;

}


uint8_t get_joystick_x(volatile char *adc)
{
    uint8_t value;
    uint8_t x = check_ADC(2,adc);
    if(x <=183){
        value = 50*(x-32)/151;
    }
    else{
        value = 50 + ((x-183)/((255-183)/50));
    }

    return value;
}
uint8_t get_joystick_y(volatile char *adc){

    uint8_t value;
    uint8_t y = check_ADC(3,adc);
    if(y <=193){
        value = 50*(y-32)/161;
    }
    else{
        value = 50 + ((y-193)/((255-193)/(50)));
    }
    return value;
}

uint8_t get_leftslider(volatile char *adc){
    uint8_t value;
    uint8_t left = check_ADC(0,adc);
    if(left <=180){
        value = 50*(left-24)/156;
    }
    else{
        value = 50 + ((left-180)/1.5);
    }
    return value;
}

uint8_t get_rightslider(volatile char *adc){
    uint8_t value;
    uint8_t right = check_ADC(1,adc);
    if(right <=180){
        value = 50*(right-24)/156;
    }
    else{
        value = 50 + ((right-180)/1.5);
    }
    return value;
}



uint8_t check_ADC(uint8_t a, volatile char *adc){
    
    adc[0] = 0x04; 

    _delay_us(100); 

    uint8_t value_right =adc[0]; 
    uint8_t value_left =adc[0]; 
    uint8_t Joystick_y =adc[0]; 
    uint8_t Joystick_x = adc[0];

    _delay_ms(100); 

    switch(a)
        {
            case 0:
                return value_left;
                break;
            case 1:
                return value_right;
                break;
            case 2:
                return Joystick_x;
                break;
            case 3:
                return Joystick_y;
                break;
            
        }
}

uint8_t Joy_Direction(volatile char *adc){

    uint8_t x = get_joystick_x(adc);
    uint8_t y = get_joystick_y(adc);
    if((abs(x-50))>abs(y-50)){
        if(x>122 || x<=46 && x>0){
            return 0;
        }else if((x>49 && x<=122)){
            return 1;
        }else{
            return 4;
        }
    }else{
        if(y>122 || y<46 && y>0){
            return 2;
        }else if((y>55)){
            return 3;
        }else{
            return 4;
        }
    }
}

    uint8_t iDown = 0;
    uint8_t iUp = 0;
    uint8_t pagePointer = 2;
uint8_t print_Joy_dir(volatile char *adc){
    uint8_t dir= Joy_Direction(adc);
     uint8_t y = get_joystick_y(adc);
    switch(dir)
        {
            case 0:
                //LEFT
                clear_OLED();
                break;
            case 1:
                //RIGHT
                break;
            case 2:
                //DOWN
                if(y==254 && pagePointer<=4)
                    pagePointer++;
                break;
            case 3:
                //UP
                if(pagePointer > 2 && y==112)
                    pagePointer--;
                break;
            case 4:
                break;
        }
        iDown = 0;
        return pagePointer;
}








