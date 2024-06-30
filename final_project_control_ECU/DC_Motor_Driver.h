/*
 * DC_Motor_Driver.h
 *
 *  Created on: Oct 12, 2023
 *      Author:  Rana Mohamed
 */

#ifndef DC_MOTOR_DRIVER_H_
#define DC_MOTOR_DRIVER_H_
#define DC_MOTOR_PORT  PORTB_ID
#define DC_MOTOR_PIN1 PIN0_ID
#define DC_MOTOR_PIN2 PIN1_ID
#define DC_MOTOR_ENABLE_PORT_ID PORTB_ID
#define DC_MOTOR_ENABLE_PIN_ID  PIN3_ID

/*to determine the motor direction
 * OFF=0
 * CW=1
 * ANTI_CLK=2
 * */
typedef enum
{
	OFF,CW,A_CW
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_DRIVER_H_ */
