/*
 * APP_functions.c
 *
 *  Created on: Nov 4, 2023
 *      Author: user
 */

#include"APP_functions.h"
#include"Buzzer.h"
#include"DC_Motor_Driver.h"
#include"twi.h"
#include"external_eeprom.h"
#include"common_macros.h"
#include"UART.h"
#include"Timer.h"
#include"GPIO.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

static void (*g_functionPtr)(void)=NULL_PTR;


uint8 g_intial_pass[ PASSWORD_SIZE ]={0};
uint8 g_check_op = -1;
uint8 g_seconds=0;



void CONTROL_getOperation(void)
{

	g_check_op=CONTROL_recieveOperation();

	/*Discuss the function which will be done due to operation*/
	switch(g_check_op)
	{
	case CHANGE_PASS:
		g_functionPtr=CONTROL_changePasswordEEPROM;
		break;
	case CONFIRM_PASS:
		CONTROL_writePasswordInEEPROM();
		break;
	case CHECK_PASS:
		g_functionPtr=CONTROL_checkPassword;
		break;
	case OPEN_DOOR:
		g_functionPtr=CONTROL_motorRotate;
		break;
	case ATHEIF:
		g_functionPtr=CONTROL_activeBuzzer;
		break;
	}
	g_functionPtr();
	g_functionPtr=NULL_PTR;

}


volatile uint8 CONTROL_recieveOperation(void)
{

	while(UART_Recieve_byte()!=START_COMM);

	/*tell the HMI that we are ready to recieve*/
	UART_send_byte(READY_RECIEVE);

	/*recieve the operation*/
	return UART_Recieve_byte();
}


void CONTROL_sendOperation(uint8 op)
{
	/*request communication*/
	UART_send_byte(START_COMM);

	/*ready to recieve*/
	while(UART_Recieve_byte()!=READY_RECIEVE);

	/*Send operation*/
	UART_send_byte(op);
}


uint8 CONTROL_checkPassword(void)
{

	uint8 i,temp;

	/*Get password from MC1*/
	for(i=0;i<5;i++){
		g_intial_pass[i]=UART_Recieve_byte();}

	/*Get password from EEPROM*/
	for(i=0;i<5;i++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+i,&temp);

		/*Password doesn't match*/
		if(temp!=g_intial_pass[i])
		{
			UART_send_byte(PASS_MISMATCH);
			return PASS_MISMATCH;
		}
	}

	/*Password match*/
	UART_send_byte(PASS_MATCH);
	return PASS_MATCH;
}

/*
 * A function to write new password in EEPROM
 */
void CONTROL_writePasswordInEEPROM(void)
{
	uint8 counter;
	for(counter=0;counter<5;counter++)
	{
		g_intial_pass[counter]=UART_Recieve_byte();
		/*re-write the password*/
		EEPROM_writeByte(EEPROM_ADDRESS+counter,g_intial_pass[counter]);
	}
}

/*
 * A function to change our password
 */
void CONTROL_changePasswordEEPROM(void)
{
	if(CONTROL_checkPassword()==PASS_MATCH)
	{
		CONTROL_writePasswordInEEPROM();
	}
}

/*
 * A function to Rotate Motor
 */
void CONTROL_motorRotate(void)
{
	/* Rotate motor clockwise*/
	 DcMotor_Rotate(CW ,100);
	delaySeconds(15);
	_delay_ms(300);

	/* Stop motor */
	DcMotor_Rotate(OFF,0);
	delaySeconds(3);
	_delay_ms(300);

	/* Rotate motor anti clockwise*/
	DcMotor_Rotate(A_CW,100);
	delaySeconds(15);
	_delay_ms(300);

	/* Stop motor */
	DcMotor_Rotate(OFF,100);

}

/*
 * A function to active buzzer for 1 minute
 */
void CONTROL_activeBuzzer(void)
{

	/*Turn on the buzzer*/
	Buzzer_on();

	delaySeconds(60);

	Buzzer_off();
}

/*
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec)
{
	/* setting the callBack function to count seconds */
	 Timer1_setCallBack(countSec);
	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1Config = {0,31250,pre256,CTC_mode1}; //8000000/256=31250

	Timer1_init(&timer1Config);
	while(g_seconds < sec);
	g_seconds = 0;
	Timer1_deInit();

}

/*
 * A function that increase our global variable each second
 */
void countSec(void)
{
	g_seconds++;
}
