/*
 * TWI.h
 *
 * Created: 10/9/2020 12:46:50 PM
 *  Author: DELL
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define F_TWI 400000UL
#define MyTWPS 1

#define MyTWBR ((F_CPU/F_TWI)-16)/(2*(4^MyTWPS))
                             
#define TW_Address_Reg     (*((volatile unsigned char*)0x22))
#define TW_BitRate_Reg     (*((volatile unsigned char*)0x20))
#define TW_Ctrl_Reg        (*((volatile unsigned char*)0x56))
#define TW_Data_Reg        (*((volatile unsigned char*)0x23))
#define TW_Status_Reg      (*((volatile unsigned char*)0x21))

#define TW_INT_Flag        7
#define TW_ACKBIT_EN       6
#define TW_STARTBIT        5
#define TW_STOPBIT         4
#define TW_EN              2

void TWI_Init(unsigned char address);
unsigned char TWI_Start();
void TWI_Stop();
unsigned char TWI_Status();
unsigned char TWI_Data(unsigned char data);
unsigned char TWI_ReadACK(unsigned char * data);
unsigned char TWI_ReadNACK(unsigned char * data);




#endif /* TWI_H_ */