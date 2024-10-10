#include "OLED.h"
#include "font.h"
void oled_write_command(uint8_t command)
{
    volatile char *ext_oled_command = (char *) 0x1000;
    ext_oled_command[0] = command;
}

void oled_write_data(uint8_t data)
{
    volatile char *ext_oled_data = (char *) 0x1200;
    ext_oled_data[0] = data;
}

void oled_init()
{
    oled_write_command(0xae); // display off
    oled_write_command(0xa1); // segment remap
    oled_write_command(0xda); // common pads hardware: alternative
    oled_write_command(0x12); 
    oled_write_command(0xc8); // common output scan direction: com63~com0
    oled_write_command(0xa8); // multiplex ration mode:63
    oled_write_command(0x3f);
    oled_write_command(0xd5); // display divide ration/osc. freq. mode
    oled_write_command(0x80);
    oled_write_command(0x81); // contrast control
    oled_write_command(0x50);
    oled_write_command(0xd9); // set pre-charge period
    oled_write_command(0x21);
    oled_write_command(0x20); // Set Memory Addressing Mode
    oled_write_command(0x02);
    oled_write_command(0xdb); // VCOM deselect level mode
    oled_write_command(0x30);
    oled_write_command(0xad); // master configuration
    oled_write_command(0x00);
    oled_write_command(0xa4); // out follows RAM content
    oled_write_command(0xa6); // set normal display
    oled_write_command(0xaf); // display on
}

void clear_OLED()
{

    for(uint8_t i = 0; i < 8; i++){
        selectpage(i);
        selectcolumn(0);
        for(int k = 0; k<128; k++){
            oled_write_data(0x00);
        }
    }
}

void selectpage(uint8_t line){
    oled_write_command(0xB0 + line);
        
}
void selectcolumn(uint8_t column){
    oled_write_command(0x00 + (column % 16));
    oled_write_command(0x10 + (column / 16));
    
}

//For printing characters
void oled_print_char(char c)
{
    c = c - 32;
    for(int i = 0 ; i < 8 ; i++)
    {
        int byte = pgm_read_byte(&font8[c][i]);
        oled_write_data(byte);
    }
}

//For printing Strings(as strings are considered as sequence of characters)
void oled_print(char c[])
{
    for(int i = 0; i < strlen(c); i++)
    {
        oled_print_char(c[i]);
    }
}

uint8_t displayMenu(uint8_t i)
{
    oled_init();

    uint8_t pagePointer =  i;
    char pointer[] = "->";
    char title[] = "MENU";
    char subMenu1[] = "PLAY GAME1";
    char subMenu2[] = "PLAY GAME2";
    char subMenu3[] = "PLAY GAME3";
    //choose a page(0-7)
    clear_OLED();
   
    //choose line/page: 
    selectpage(1);

    //Select column
    selectcolumn(25);

    oled_print(title);

    selectpage(2);
    selectcolumn(25);
    oled_print(subMenu1);

    selectpage(3);
    selectcolumn(25);
    oled_print(subMenu2);

    selectpage(4);
    selectcolumn(25);
    oled_print(subMenu3);

    selectpage(pagePointer);
    selectcolumn(5);
    oled_print(pointer);

    return pagePointer;
}

void subMenu1()
{
    oled_init();

    char title[] = "POSITION 2";

    //choose a page(0-7)
    clear_OLED();
   
    //choose line/page: 
    selectpage(1);

    //Select column
    selectcolumn(25);

    oled_print(title);
}

void subMenu2()
{
    oled_init();

    char title[] = "POSITION 3";

    //choose a page(0-7)
    clear_OLED();
   
    //choose line/page: 
    selectpage(1);

    //Select column
    selectcolumn(25);

    oled_print(title);
}

void subMenu3()
{
    oled_init();

    char title[] = "POSITION 4";

    //choose a page(0-7)
    clear_OLED();
   
    //choose line/page: 
    selectpage(1);

    //Select column
    selectcolumn(25);

    oled_print(title);
}