#include"APP_functions.h"
#include<avr/io.h>
#include"Buzzer.h"
#include"DC_Motor_Driver.h"
#include"external_eeprom.h"
#include"twi.h"
#include"common_macros.h"
#include"UART.h"
#include"Timer.h"
#include"GPIO.h"
#include<avr/io.h>
#include<avr/interrupt.h>

int main(void)
{
	DcMotor_Init();
	Buzzer_init();
	SREG |= (1<<7);

	UART_ConfigType conf_UART={BitData_8,parity_disabled,stop_1bit, mod9600};

	UART_init(&conf_UART);

	/* I2C configurations structure */
	TWI_ConfigType i2cConfig = {0x20,0b0000010};

	/* initialize I2C */
	TWI_init(&i2cConfig);

	while(1)
	{
		CONTROL_getOperation();
	}
}
