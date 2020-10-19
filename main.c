/*
* TWI_E2PROM_H18.c
*
* Created: 10/9/2020 12:46:23 PM
* Author : Mohamed Nader
*/

#include "TWI.h"

void E2PROM_Write(unsigned long lOCAddress,unsigned char data);
void E2PROM_Read(unsigned long lOCAddress,unsigned char * data);

int main(void)
{
	DDRC |= (1<<7);
	TWI_Init(0b00000011);
	unsigned char data = 0;
	unsigned char wdata = 0;
	unsigned long lOCAddress = 0;
	while(1){
		E2PROM_Write(lOCAddress,wdata);
		_delay_ms(200);
		E2PROM_Read(lOCAddress,&data);
		if(data == 'M')
		PORTC ^= (1<<7);
	}
}

void E2PROM_Write(unsigned long lOCAddress,unsigned char wdata){
	if(TWI_Start() == 0x08){
		if(TWI_Data(0b10100100) == 0x18){
			if(TWI_Data(0b00000000) == 0x28){
				if(TWI_Data('M') == 0x28){
					TWI_Stop();
				}
			}
		}
		
	}
}


void E2PROM_Read(unsigned long lOCAddress,unsigned char * data){
	if(TWI_Start() == 0x08){
		if(TWI_Data(0b10100100) == 0x18){
			if(TWI_Data(0b00000000) == 0x28){
				if(TWI_Start() == 0x10){
					if(TWI_Data(0b10100101) == 0x40){
						TWI_ReadNACK(data);
						TWI_Stop();
					}
				}
			}
		}
		
	}
}
