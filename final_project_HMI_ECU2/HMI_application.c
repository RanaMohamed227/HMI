#include "LCD.h"
#include "std_types.h"
#include <avr/io.h>
#include "Keypad.h"
#include<util/delay.h>
#include<avr/interrupt.h>
#include"APP_functions.h"

#include"common_macros.h"
#include"UART.h"
#include"Timer.h"
#include"GPIO.h"
/*
void main_options(void){
	LCD_moveCursor(0,0);
	LCD_DisplayString("+: Open Door ");
	LCD_moveCursor(1,0);
	LCD_DisplayString("-: Change Pass");
}*/
int main(void){

	SREG |= (1<<7);
	LCD_init();

	UART_ConfigType conf_UART = {BitData_8,parity_disabled,stop_1bit, mod9600};

	UART_init(& conf_UART);
		LCD_init();
		HMI_createSystemPassword();

while(1){

}

}
