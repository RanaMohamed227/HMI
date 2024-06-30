/*
 * APP_functions.h
 *
 *  Created on: Nov 4, 2023
 *      Author: user
 */

#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_



#include"std_types.h"



#define PASSWORD_SIZE     5
#define EEPROM_ADDRESS			  0x0311
#define CHANGE_PASS  	  1
#define CONFIRM_PASS  2
#define PASSWORD_CONF  	  		  3
#define CHECK_PASS      4

#define OPEN_DOOR	   	  		  5
#define CLOSE_DOOR	   	  		  6

#define TIME_15_CW	   	  		  7
#define TIME_15_ACW	   	  	      8
#define TIME_3_delay   	  		  9

#define ATHEIF   	  		  10
#define MAX_WRONG      	  		  3

#define CONFIRM_SEND   	  		  11
#define CONFIRM_RECIEVE   		  12

#define READY_SEND   	  		  13
#define READY_RECIEVE     		  14

#define START_COMM		  		  15

#define PASS_MISMATCH  	  		  16
#define PASS_MATCH     	  		  17

#define TIME_15SEC				  14648
#define TIME_60SEC				  58593
#define TIME_3SEC				  4883

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*

 * A function to get the operation from HMI micro
 */
void CONTROL_getOperation(void);

/*
 * A function that recieve a Operation
 */
volatile uint8 CONTROL_recieveOperation(void);

/*
 * A function that send a Operation
 */
void CONTROL_sendOperation(uint8 op);

/*

 * A function to get the password from HMI micro and check it ,
 * and it returns PASS_MATCH if it the same password or return
 * PASS_MISMATCH if password doesn't match
 */
uint8 CONTROL_checkPassword(void);

/*

 * A function to write new password in EEPROM
 */
void CONTROL_writePasswordInEEPROM(void);

/*
 * A function to change our password
 */
void CONTROL_changePasswordEEPROM(void);

/*
 * A function to Rotate Motor Clockwise for 15 sec
 */
void CONTROL_motorClockwise(void);

/*

 * A function to Rotate Motor
 */
void CONTROL_motorRotate(void);
/*

 * A function to active buzzer for 1 minute
 */
void CONTROL_activeBuzzer(void);

/*
 * A function that increase our global variable each second
 */
void countSec(void);

/*

 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec);


#endif /* APP_FUNCTIONS_H_ */
