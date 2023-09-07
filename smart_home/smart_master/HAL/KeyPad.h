/*
 * KeyPad.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : KEYPAD - PROTOTYPE
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



void KP_pinInit(void);
u8 KP_GetPressedButton(void);

#endif /* INCLUDE_KEYPAD_H_ */
