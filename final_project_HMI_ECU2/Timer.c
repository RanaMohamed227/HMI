/*
 * Timer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: user
 */
#include "avr/io.h"
#include "Timer.h"
#include "common_macros.h"
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}


void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A= (1<<FOC1A) | ( 1 << FOC1B )   ;
	TCCR1B=(TCCR1B & 0XF8) | (Config_Ptr -> prescaler) | ( (( (Config_Ptr -> mode) &0Xe7)<<4)) ; /*clear the first 3 bits in ADCSRA then take the prescaler value and OR it with the first 3 bits in the register*/
	if ((Config_Ptr -> mode)== normal_mode )
		{
		TIMSK = ( 1 << TOIE1 );
		TCNT1 = Config_Ptr -> intial_value ;
		}
		else if ((Config_Ptr -> mode)== 12)
			{

			TIMSK |= (1<<OCIE1A);
			ICR1 = Config_Ptr -> compare_value;
			}
		else
		{
			OCR1A = Config_Ptr -> compare_value;


					TIMSK=(1<<OCIE1A);
		}

}
void Timer1_deInit(void){
	/* Clear All Timer1/ICU Registers */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		ICR1 = 0;
		TIMSK = 0;
		OCR1A = 0;

		/* Reset the global pointer value */
		g_callBackPtr = NULL_PTR;


}
Timer1_setCallBack(void(*a_ptr)(void)){

	g_callBackPtr = (volatile void (*)(void))a_ptr;

}
