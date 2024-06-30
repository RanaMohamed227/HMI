
#include"std_types.h"

/*******************************************************************************
 *                         	    Definitions                                    *
 *******************************************************************************/
#define CHANGE_PASS  	  1
#define CONFIRM_PASS  	  2
#define CHECK_PASS 	  		  4

#define OPEN_DOOR	   	  		  5
#define CLOSE_DOOR	   	  		  6

#define TIME_15_CW	   	  		  7
#define TIME_15_ACW	   	  	      8
#define TIME_3_delay   	  		  9

#define TIME_1_WRONG   	  		  10
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
 * A function that send a Operation
 */
void HMI_sendOperation(uint8 op);

/*
 * A function that recieve a Operation
 */
volatile uint8 HMI_recieveOperation(void);
/*
 * A function to get the password from user while entering it
 * and send it to control ECU .
 */
void HMI_sendPassword(uint8 row,uint8 col,uint8 op);



/*
 * A function to create system password
 */
void HMI_createSystemPassword(void);

/*
 * A function to open door
 */
void HMI_openDoor(void);
void HMI_threeWrong();


/*
 * A function to open door
 */
void HMI_UnlockDoor(void);

/*
 * A function to change the password
 */
void HMI_changePass(void);

/*
 * A function to get what the user wants to do
 */
void HMI_changeOrOpen(void);


/*
\
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec);

/*
\
 * A function that increase our global variable each second
 */
void countSec(void);
