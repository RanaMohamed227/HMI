/*
 * DC_Motor_Driver.c
 *
 *  Created on: Oct 12, 2023
 *      Author:  Rana Mohamed
 */
#include "gpio.h"
#include "DC_Motor_Driver.h"
#include "std_types.h"
#include "PWM_DRIVER.h"


/* set the two pins of the motor as output/write
 * then intialize them as off --> motor is OFF
 * */
void DcMotor_Init(void){
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN2,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_ENABLE_PORT_ID, DC_MOTOR_ENABLE_PIN_ID,1);
	GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN1, LOGIC_LOW);

	GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN2, LOGIC_LOW);

	/* Set the Enable bit*/
	GPIO_writePin(DC_MOTOR_ENABLE_PORT_ID, DC_MOTOR_ENABLE_PIN_ID,1);
}


/*
 * if state is zero or state==off
 * the motor is off --> two motor pins are logic_low
 *
 * if state is 1 or state == CW
 * the motor is off --> one motor pins are logic_high the other is logic_low
 *
 * if state is 1 or state == A_CW
 * the motor is off --> one motor pins are logic_high the other is logic_low
 * */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(!state){

		GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN2, LOGIC_LOW);
	}
	else{
		if(state== CW){
			GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN1, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN2, LOGIC_LOW);
		}
		else{
			GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN1, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_PIN2, LOGIC_HIGH);

		}

	}
	PWM_Timer0_Start();
}
