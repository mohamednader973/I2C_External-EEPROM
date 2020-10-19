/*
* TWI.c
*
* Created: 10/9/2020 12:46:38 PM
*  Author: DELL
*/

#include "TWI.h"


void TWI_Init(unsigned char address){
	//TWBR = MyTWBR;
	TW_BitRate_Reg=MyTWBR;
	//TWAR = address;
	TW_Address_Reg=address;
	//TWCR = (1<<TWEN)|(1<<TWINT);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag);
}
unsigned char TWI_Start(){
	//TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTA);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag)|(1<<TW_STARTBIT);
	//while(!(TWCR & (1<<TWINT)));
	while(!(TW_Ctrl_Reg & (1<<TW_INT_Flag)));
	return (TWI_Status());
}
void TWI_Stop(){
	//TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag)|(1<<TW_STOPBIT);
}
unsigned char TWI_Status(){
	//return (TWSR & 0xF8);
	return (TW_Status_Reg & 0xF8);
}
unsigned char TWI_Data(unsigned char data){
	//TWDR = data;
	TW_Data_Reg=data;
	//TWCR = (1<<TWEN)|(1<<TWINT);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag);
	//while(!(TWCR & (1<<TWINT)));
	while(!(TW_Ctrl_Reg & (1<<TW_INT_Flag)));
	return (TWI_Status());
}

unsigned char TWI_ReadACK(unsigned char * data){
	//TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag)|(1<<TW_ACKBIT_EN);
	//while(!(TWCR & (1<<TWINT)));
	while(!(TW_Ctrl_Reg & (1<<TW_INT_Flag)));
	//*data = TWDR;
	*data = TW_Data_Reg;
	return (TWI_Status());
}
unsigned char TWI_ReadNACK(unsigned char * data){
	//TWCR = (1<<TWINT)|(1<<TWEN);
	TW_Ctrl_Reg=(1<<TW_EN)|(1<<TW_INT_Flag);
	//while(!(TWCR & (1<<TWINT)));
	while(!(TW_Ctrl_Reg & (1<<TW_INT_Flag)));
	//*data = TWDR;
	*data = TW_Data_Reg;
	return (TWI_Status());
}