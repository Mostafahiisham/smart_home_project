/*
 * main.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Mostafa Hisham
 *      Layer : APP
 */
#include<Std_Types.h>
#include<Macros.h>
#include<Registers.h>
#include<DIO.h>
#include<SPI.h>
#include<TIMER.h>
#include<GIE.h>
#include<LCD.h>
#include<KeyPad.h>
#include<util/delay.h>


void Alarm(void)
{	static u16 Local_Counter = 0;
	Local_Counter++;
	if(Local_Counter == 4000)
	{
		DIO_TogglePinLevel(DIO_PORTD,DIO_PIN0);
		Local_Counter = 0;
	}
}
void main(void)
{
	 u8 Data ;
	//SET SS PIN
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN4,PIN_INPUT_PULLUP);
	//SET MOSI PIN FOR MASTER
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN5,PIN_OUTPUT);
	//SET MISO PIN FOR MASTER
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN6,PIN_INPUT);
	//SET SCK PIN FOR MASTER
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN7,PIN_OUTPUT);
	SPI_Master_Init();
	KP_PinInit();
	LCD_Init();
	LCD_SendString("welcome");
	LCD_CursorPosition(1,0);
	LCD_SendString("Smart Home");
	_delay_ms(100);
	LCD_DisplayClear();
	while(1)
	{


		do{
			Data = KP_GetPressedbutton();
				}while(Data == 0xff);
			SPI_Transceive(Data);
		LCD_SendCharacter(Data);
		_delay_ms(300);
		LCD_DisplayClear();

		if(Data =='7')
		{
		DIO_SetPinDirection(DIO_PORTD,DIO_PIN0,PIN_OUTPUT);
		TIMER_2Init();
		TIMER_SetCTCValue(250,TIMER2);
		TIMER_CTC2SetCallBack(&Alarm);
		GIE_Enable();
		}
		// IF THE  C KEY IS PRESSED THE ALARM SYSTEM STOPS ALSO THE FIRE DISTINGUISHER STOPS IN THE SLAVE SYSTEM
		if(Data =='c')
		{
		DIO_SetPinDirection(DIO_PORTD,DIO_PIN0,PIN_INPUT);
		}
	}

}

