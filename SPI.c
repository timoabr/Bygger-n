#include "SPI.h"
#include <util/delay.h>



void SPI_MasterInit(void)
{
//Set MOSI and SCK output, all others input
//DDR_SPI = (1<<DD_MOSI) | (1<<DD_SCK);
DDRB = (1<<PB5) | (1<<PB7) | (1<<PB4);

//Enable SPI, Master, set clock rate fck/16
SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) |(1<<SPIE);

SPI_set_SS();
}

void SPI_MasterTransmit(char cData) //MOSI
{
    //Start transmission
    SPDR = cData;
    //Wait for transmission complete
    while(!(SPSR & (1<<SPIF))){ //SPIF is the register that is set when data transfer is completed
        
    }
}


// SPI-mode is initially set to mode 0; 

char SPI_Receive(void)
{   
    SPDR = 0xFF;

    //Wait for reception complete 
    while(!(SPSR & (1<<SPIF))){

    }
    //return data register
    return SPDR;
}

void SPI_set_SS(){
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);
}

void SPI_clear_SS(){
    PORTB &= ~(1<<PB4);
}

void mcp_init(){
    SPI_MasterInit();
    mcp_reset();

    _delay_ms(1);

    /*uint8_t value = mcp_read(0b00001110);
    if((value & MODE_MASK) != MODE_CONFIG){
        printf("MCP2115 er ikke i konfigurasjonsmodus etter reset. CANSTAT: %x \n\r", value);
    }*/
}

void mcp_reset() {
    SPI_clear_SS();
    SPI_MasterTransmit(MCP_RESET);
    SPI_set_SS();

}

uint8_t mcp_read(uint8_t address){
    SPI_clear_SS();
    SPI_MasterTransmit(MCP_READ);
    SPI_MasterTransmit(address);
    uint8_t data = SPI_Receive();
    SPI_set_SS();

    return data;
}
void mcp_write(uint8_t address, uint8_t data){
    SPI_clear_SS();
    SPI_MasterTransmit(MCP_WRITE);
    SPI_MasterTransmit(address);
    SPI_MasterTransmit(data);
    SPI_set_SS();
}

char mcp_read_status()
{
    SPI_clear_SS();
    SPI_MasterTransmit(MCP_READ_STATUS);
    char data = SPI_Receive();
    SPI_set_SS();
    return data;
    
}

void mcp_bit_modify(uint8_t adress, uint8_t mask, uint8_t data){
    SPI_clear_SS();

    SPI_MasterTransmit(MCP_BITMOD);
    SPI_MasterTransmit(adress);
    SPI_MasterTransmit(mask); //f.eks 0b00011000 this means that we want to modefy the bits with 1. 
    SPI_MasterTransmit(data);
    SPI_set_SS();
}

void mcp_request_to_send_buffer0()
{
SPI_clear_SS();
char data = MCP_RTS_TX0;
SPI_MasterTransmit(data);
SPI_set_SS();

}
void mcp_set_mode(uint8_t mode){
    mcp_bit_modify(0b00001111, 0b11100000, mode);
}
