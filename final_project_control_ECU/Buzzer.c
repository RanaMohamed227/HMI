/*
 * Buzzer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: user
 */
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h"
#include <stdlib.h>
#include "Buzzer.h"
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_LOW);
}
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PIN,BUZZER_PIN,LOGIC_HIGH);
}
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_LOW);
}
