#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>



// Send-buffer 0
#define MCP_TXB0SIDH 0x31 // aka 0b0011 0001

//Send-buffer 1
#define MCP_TXB1SIDH 0x41

//Send-buffer 2
#define MCP_TXB2SIDH 0x51

// Motta-buffer 0
#define MCP_RXB0SIDH 0x61

// Motta-buffer 1
#define MCP_RXB1SIDH 0x71


void SPI_MasterTransmit(char cData);
void SPI_MasterInit(void);
char SPI_SlaveReceive(void);
void SPI_set_SS();
void SPI_clear_SS();
void mcp_init();
void mcp_reset();
uint8_t mcp_read(uint8_t andress);
void mcp_write(uint8_t address, uint8_t data);
char mcp_read_status();
void mcp_bit_modify(uint8_t adress, uint8_t mask, uint8_t data);
void mcp_request_to_send_buffer0();
void mcp_set_mode(uint8_t mode);