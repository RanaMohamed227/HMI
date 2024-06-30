/*
 * UART.c
 *
 *  Created on: Oct 13, 2023
 *      Author: user
 */
#include <avr/io.h>
#include "std_types.h"
#include "common_macros.h"
#include "UART.h"

void UART_init(const UART_ConfigType * Config_Ptr){
	uint16 ubrr_value=0;
	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL);
	UCSRC |= ( ( Config_Ptr -> bit_data &  0X01 ) << 1 ) | ( ( Config_Ptr -> bit_data &  0X02 ) << 2);
	UCSRC |= ((UCSRC & 0XCF) | (((Config_Ptr ->parity )&0X03)<<4) ) ;
	UCSRC |= ((UCSRC & 0XF7) | (((Config_Ptr ->stop_bit )&0X01)<<3 ) ) ;
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr -> baud_rate) * 8UL))) - 1);

		/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
		UBRRH = ubrr_value>>8;
		UBRRL = ubrr_value;

}
uint8 UART_Recieve_byte(void){
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
}
void UART_send_byte(uint8 data){
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR=data;
}
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_send_byte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_Recieve_byte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_Recieve_byte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}


