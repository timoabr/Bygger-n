#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void oled_init();
void oled_write_data(uint8_t data);
void oled_write_command(uint8_t command);
void clear_OLED();
void selectpage(uint8_t line);
void selectcolumn(uint8_t column);
void oled_print_char(char c);
void oled_print(char c[]);
uint8_t displayMenu(uint8_t i);
void subMenu1();
void subMenu2();
void subMenu3();