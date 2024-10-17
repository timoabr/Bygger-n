#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>



typedef struct Message{
    unsigned int id;
    int length;
    char data[8];
}message_t, *message_ptr;

message_t can_recieve();
void can_write(message_ptr message);
void message_print(message_t message);
message_t make_message(unsigned int id, int length, char data[]);