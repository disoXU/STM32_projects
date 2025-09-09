#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

void Serial_SendByte(uint8_t Byte);
void Serial_Init(void);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNum(uint32_t Num, uint8_t Length);

uint8_t Serial_GetRxFlag(void) ;
void Serial_SendPacket(void);

#endif
