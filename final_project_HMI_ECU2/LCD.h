/*
 * LCD.h
 *
 *  Created on: Oct 3, 2023
 *      Author:  Rana Mohamed
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
#define LCD_RS_PORT_ID                 PORTA_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTA_ID
#define LCD_RW_PIN_ID                  PIN4_ID

#define LCD_E_PORT_ID                  PORTA_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTC_ID

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_DATA_BITS_MODE             8
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
void LCD_init(void);
void LCD_SendCommand(uint8 command);
void LCD_DisplayCharacter(uint8 character);
void LCD_DisplayString(uint8 *string);

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif
void LCD_clearScreen(void);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
#endif /* LCD_H_ */
