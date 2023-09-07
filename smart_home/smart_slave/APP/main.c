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
#include<ADC.h>
#include<LCD.h>
#include<DC_Motor.h>
#include<util/delay.h>

void main(void)
{
	u8 data;
	u16 Iterator ;
	//SET SS PIN
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN4,PIN_INPUT);
	//SET MOSI PIN FOR SLAVE
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN5,PIN_INPUT);
	//SET MISO PIN FOR SLAVE
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN6,PIN_OUTPUT);
	//SET SCK PIN FOR SLAVE
	DIO_SetPinDirection(DIO_PORTB,DIO_PIN7,PIN_INPUT);

	//ROOMS
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN0,PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN1,PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN2,PIN_OUTPUT);
	//TV
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN3,PIN_OUTPUT);
	//AIR-CONDITIONER
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN4,PIN_OUTPUT);
	//LM35
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN0,PIN_INPUT);
	//LDR
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,PIN_INPUT);
	//Garden Lights
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN4,PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN5,PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN6,PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN7,PIN_OUTPUT);

	SPI_Slave_Init();
	LCD_Init();
	ADC_Init();

	while(1)

	{
		// 10 IS AGARBAGE VALUE
		data = SPI_Transceive(10);
		LCD_DisplayClear();
		switch(data)
		{
		case '1':
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN0,PIN_HIGH);
			break;
		case '2':

			DIO_SetPinLevel(DIO_PORTD,DIO_PIN1,PIN_HIGH);
			break;
		case'3':

			DIO_SetPinLevel(DIO_PORTD,DIO_PIN2,PIN_HIGH);
		break;
		case'4':
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN3,PIN_HIGH);
		break;
		case'5':
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN4,PIN_HIGH);
		break;
		case'6':
			DIO_SetPinDirection(DIO_PORTD,DIO_PIN5,PIN_OUTPUT);
			TIMER_1Init();
			TIMER1_SetTopValue(20000);
			for(Iterator =750 ; Iterator < 2500 ; Iterator++)
			{
				TIMER_SetCTCValue(Iterator,TIMER1);
			}
		break;
		case '7':
				// TO START THE FIRE DISTINGUISHER SYSTEM
				DCMOTOR_RotateClockwise(MOTOR1);
		break;
		case 'c':
				// TO STOP THE FIRE DISTINGUISHER SYSTEM (MOTOR)
				DCMOTOR_Stop(MOTOR1);
		break;
		case'0':
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN0,PIN_LOW);
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN1,PIN_LOW);
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN2,PIN_LOW);
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN3,PIN_LOW);
			DIO_SetPinLevel(DIO_PORTD,DIO_PIN4,PIN_LOW);
			DIO_SetPinDirection(DIO_PORTD,DIO_PIN5,PIN_OUTPUT);
			TIMER_1Init();
			TIMER1_SetTopValue(20000);
			for(Iterator = 2500 ; Iterator >750 ; Iterator--)
				{
					TIMER_SetCTCValue(Iterator,TIMER1);
				}
		break;
		}
	}



}

