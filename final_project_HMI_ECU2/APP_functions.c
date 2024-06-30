/*
 * APP_functions.c
 *
 *  Created on: Nov 4, 2023
 *      Author: user
 */

#include"APP_functions.h"
#include"common_macros.h"
#include"UART.h"
#include"Timer.h"
#include"GPIO.h"
#include"LCD.h"
#include"Keypad.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

uint8 static g_checkPassword=0;
uint8 g_seconds=0;


volatile uint8 HMI_recieveOperation(void)
{
	/*Polling till we get a request for communication*/
	while(UART_Recieve_byte()!=START_COMM);

	/*tell the other micro that we are ready to recieve*/
	UART_send_byte(READY_RECIEVE);

	/*recieve the operation*/
	return UART_Recieve_byte();
}
void HMI_sendOperation(uint8 op)
{
	/*request communication*/
	UART_send_byte(START_COMM);

	/*ready to recieve*/
	while(UART_Recieve_byte()!=READY_RECIEVE);

	/*Send operation*/
	UART_send_byte(op);
}
void HMI_sendPassword(uint8 row,uint8 col,uint8 op)
{
	uint8 counter=0;

	/* Sending our operation to MC2 and ask him to start*/
	HMI_sendOperation(op);
	_delay_ms(300);

	/*Move LCD cursor to the place which we will get password from*/
	LCD_moveCursor(row,col);
	_delay_ms(300);
	/*get password and display * instead of entered character*/
	for(counter=0;counter<5;counter++)
	{
		UART_send_byte( KEYPAD_getPressedKey());
		_delay_ms(100);
		LCD_DisplayCharacter('*');
		_delay_ms(100);
	}

	/* Polling till the user entered = as enter button */
	while( KEYPAD_getPressedKey() != '=' );
	_delay_ms(300);
}

void HMI_openDoor(void)
{
	/*Rotate motor clockwise*/
	HMI_sendOperation(OPEN_DOOR);
	_delay_ms(20);

	_delay_ms(1000);
	HMI_changeOrOpen();
}

void HMI_threeWrong()
{
	/*We exceeded 3 wrong entries*/
	if(g_checkPassword==MAX_WRONG)
	{
		_delay_ms(20);
		/*Tell control MCU*/
		HMI_sendOperation(TIME_1_WRONG);

		/*Display wrong pass on screen*/
		LCD_clearScreen();
		_delay_ms(20);
		LCD_DisplayString("Error !! wrong password");

		delaySeconds(20);
		g_checkPassword=0;
		HMI_changeOrOpen();
	}
}

void HMI_createSystemPassword(void)
{
	LCD_clearScreen();
	/*Ask the user to enter password first time*/
	LCD_DisplayString("enter password:");
	_delay_ms(20);
	HMI_sendPassword(1,0,CONFIRM_PASS);
	_delay_ms(200);

	/*Ask the user to enter password second time*/
	LCD_moveCursor(1,0);
	LCD_DisplayString("same password : ");
	_delay_ms(20);
	HMI_sendPassword(1,17,CHECK_PASS);
	_delay_ms(200);

	/*repeat the previous step again*/
	while(UART_Recieve_byte()==PASS_MISMATCH)
	{
		HMI_createSystemPassword();
	}

	LCD_clearScreen();
	_delay_ms(1000);
	HMI_changeOrOpen();

}



void HMI_UnlockDoor(void)
{
	LCD_clearScreen();
	/*Ask the user to enter password*/
	LCD_DisplayString("please enter password:");

	HMI_sendPassword(1,0,CHECK_PASS);

	uint8 pass_stat=UART_Recieve_byte();

	/*Password matches*/
	if(pass_stat == PASS_MATCH)
	{
		LCD_clearScreen();
		HMI_openDoor();
		_delay_ms(20);
		g_checkPassword=0;
		HMI_sendOperation(OPEN_DOOR);
		return;
	}
	/*Password doesn't match*/
	while(pass_stat == PASS_MISMATCH)
	{
		g_checkPassword++;
		_delay_ms(1000);
		HMI_threeWrong();

		LCD_clearScreen();
		/*Call the function again*/
		HMI_UnlockDoor();

		HMI_sendPassword(1,0,CHECK_PASS);

		pass_stat=UART_Recieve_byte();
		if(g_checkPassword==0)
			break;
	}
}

void HMI_changePass(void){
	LCD_clearScreen();
	Timer1_deInit();
		/*Ask the user to enter password first time*/
		LCD_DisplayString("please enter password:");
		_delay_ms(10);
		HMI_sendPassword(1,0,CHECK_PASS);

		uint8 pass_stat=UART_Recieve_byte();
		if(pass_stat == PASS_MATCH)
			{
				LCD_clearScreen();
				HMI_createSystemPassword();
				g_checkPassword=0;
				_delay_ms(1000);
				HMI_changeOrOpen();
				return;
			}
		while(pass_stat == PASS_MISMATCH)
			{
				g_checkPassword++;
				HMI_threeWrong();

				LCD_clearScreen();
				LCD_DisplayString("please enter password:");

				HMI_sendPassword(1,0,CHECK_PASS);

				pass_stat=UART_Recieve_byte();
				if(g_checkPassword==0)
					break;
			}


}
void HMI_changeOrOpen(void)
{
	uint8 key;
	LCD_clearScreen();
	/*Ask the user to enter what he wants to do*/
	LCD_DisplayString("+ : Open the door");
	LCD_moveCursor(1,0);
	LCD_DisplayString("- : Change Password");
	_delay_ms(500);

	key=KEYPAD_getPressedKey();
	_delay_ms(500);
	/*The user chose to open door , so we call it's function*/
	if(key=='+')
	{
		HMI_UnlockDoor();
	}

	/*The user chose to change password , so we call it's function*/
	else if(key=='-')
	{
		HMI_changePass();
	}
}

/*
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec)
{
	/* setting the callBack function to count seconds */
	Timer1_setCallBack(countSec);
	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1Config = {0,31250,pre256,CTC_mode1};

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
