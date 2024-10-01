#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>


void init_clock();

uint8_t get_joystick_x(volatile char *adc);
uint8_t get_joystick_y(volatile char *adc);
uint8_t get_leftslider(volatile char *adc);
uint8_t get_rightslider(volatile char *adc);
uint8_t check_ADC(uint8_t a, volatile char *adc);
uint8_t Joy_Direction(volatile char *adc);
void print_Joy_dir(volatile char *adc);
