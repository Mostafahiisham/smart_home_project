/*
 * KeyPad.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Mostafa Hisham
 *      Layer : HAL
 *      SWC   : KEYPAD - IMPLEMENTATION
 */
#include<Std_Types.h>
#include<DIO.h>
#include<KeyPad.h>
#include<KeyPad_Confg.h>


void KP_PinInit(void)
{
   DIO_SetPortDirection(KP_PORT,0XF0);
   DIO_SetPortLevel(KP_PORT,PORT_LEVEL_HIGH);
}
u8 KP_GetPressedbutton(void)
{
	u8 PressedKey = KP_NOT_PRESSED;

	u8 column_index, row_index,pin_state;

	static u8 KP_Array[ROW_NUMBER][COLUMN_NUMBER] = KP_ARR_VALUE;

	static	u8 KP_Column_Array[COLUMN_NUMBER] = {KP_COLUMN0,KP_COLUMN1,KP_COLUMN2,KP_COLUMN3};

	static u8 KP_Row_Array[ROW_NUMBER] = {KP_ROW0,KP_ROW1,KP_ROW2,KP_ROW3};

	for(column_index = 0 ;column_index<COLUMN_NUMBER ; column_index++)
	{
		/* Activate Current column */
		DIO_SetPinLevel(KP_PORT,KP_Column_Array[column_index],PIN_LOW);

		for(row_index = 0 ; row_index < ROW_NUMBER ; row_index++)
		{
			/*read the current row*/
			pin_state = DIO_ReadPinLevel(KP_PORT,KP_Row_Array[row_index]);
			/*check if the switch is pressed*/
			if(PIN_LOW == pin_state)
			{
				PressedKey = KP_Array[row_index][column_index];
				/* polling (busy wait)*/
			while( PIN_LOW == pin_state )
				{
				pin_state = DIO_ReadPinLevel(KP_PORT,KP_Row_Array[row_index]);
				}
			return PressedKey;
			}

		}
		/*Deactivate the current column */
		DIO_SetPinLevel(KP_PORT,KP_Column_Array[column_index],PIN_HIGH);
	}
	return PressedKey;
}
