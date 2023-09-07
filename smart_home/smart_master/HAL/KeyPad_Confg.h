/*
 * KeyPad_Confg.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : KEYPAD- CONFIGURATION
 */

#ifndef INCLUDE_KEYPAD_CONFG_H_
#define INCLUDE_KEYPAD_CONFG_H_

#define KP_PORT		DIO_PORTC

#define KP_ROW0     DIO_PIN0
#define KP_ROW1     DIO_PIN1
#define KP_ROW2		DIO_PIN2
#define KP_ROW3		DIO_PIN3

#define KP_COLUMN0	DIO_PIN4
#define KP_COLUMN1  DIO_PIN5
#define KP_COLUMN2	DIO_PIN6
#define KP_COLUMN3  DIO_PIN7


#define KP_NOT_PRESSED  0xff
#define COLUMN_NUMBER 	4
#define ROW_NUMBER      4
#define KP_ARR_VALUE	 { {'7','8','9','/'}, {'4','5','6','*'} , {'1','2','3','-'} , {'c','0','/','='}}

#endif /* INCLUDE_KEYPAD_CONFG_H_ */
