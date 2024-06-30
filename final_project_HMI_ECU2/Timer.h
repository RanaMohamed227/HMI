/*
 * Timer.h
 *
 *  Created on: Oct 30, 2023
 *      Author: user
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"


typedef enum{
normal_mode,CTC_mode1=4,CTC_mode2=12
}Timer1_Mode;



typedef enum{
pre0,pre1,pre8,pre64,pre256,pre1024
}Timer1_Prescaler;



typedef struct {
uint16 intial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;


void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_H_ */
