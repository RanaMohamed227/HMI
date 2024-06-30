/*
 * PWM_DRIVER.C
 *
 *  Created on: Oct 12, 2023
 *      Author:  Rana Mohamed
 */
#include "std_types.h"
#include <avr/io.h>
#include "PWM_DRIVER.h"
void PWM_Timer0_Start(void){
TCNT0=0; /*intial value of the timer*/
TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<CS01) | (1<<COM01);
/* NON-INVERTING */
DDRB  = DDRB | (1<<PB3); /*PB3 as output to the motor to configure the value of volt sent to the motor so the speed is determined*/

/*
 *  F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 */
/*
 * 255->100%
 * 192->75%
 * 128->50%
 * 64->25%
 */
OCR0=255;
/*
 * if duty_cycle =50
 * duty_cycle/100=0.5
 * 0.5*255=128 = 50% duty cycle --> which is the required
 */
}
