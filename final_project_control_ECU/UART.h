/*
 * UART.h
 *
 *  Created on: Oct 13, 2023
 *      Author: user
 */

#ifndef UART_H_
#define UART_H_
#include "std_types.h"
#ifndef F_CPU
#define F_CPU 16000000
#endif
typedef enum{
	BitData_5,
	BitData_6,
	BitData_7,
	BitData_8
}UART_BitData;
typedef enum{
mod2400=2400,mod4800=4800,mod9600=9600
}UART_BaudRate;
typedef enum{
parity_disabled,even_parity=2,odd_parity=3
}UART_Parity;
typedef enum{
	stop_1bit,stop_2bit
}UART_StopBit;
typedef struct{
UART_BitData bit_data;
UART_Parity parity;
UART_StopBit stop_bit;
UART_BaudRate baud_rate;
}UART_ConfigType;
void UART_init(const UART_ConfigType * Config_Ptr);
uint8 UART_Recieve_byte(void);
void UART_send_byte(uint8 data);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
