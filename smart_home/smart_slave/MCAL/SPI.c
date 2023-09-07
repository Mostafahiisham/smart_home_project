/*
 * SPI.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Mostafa Hisham
 *      Layer : MCAL
 *      SWC   : SPI-IMPLEMENTATION
 *
 */
#include<Std_Types.h>
#include<Registers.h>
#include<Macros.h>
#include<SPI.h>
#include<ADC.h>
#include<DIO.h>
#include<SPI_Private.h>
#include<LCD.h>

void SPI_Master_Init(void)
{
	/* SELECT MASTER OR SLAVE BIT */
		SET_BIT(SPCR,SPCR_MSTR);
		/*select the clock frequency*/
		SET_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);

		/*Spi _ enable*/
	SET_BIT(SPCR,SPCR_SPE);
	/* DATA ORDER  DEFAULT (LSB)*/



}
void SPI_Slave_Init(void)
{
	/* SLAVE INTILIZATION */
	CLR_BIT(SPCR,SPCR_MSTR);
	/*Spi _ enable*/
	SET_BIT(SPCR,SPCR_SPE);
	/* DATA ORDER  DEFAULT (LSB)*/
}

u8 SPI_Transceive(u8 Data)
{	u16 digital;
	u16 LDR_Reading;
	/* FUNCTION TO SEND AND RECEIVE DATA */
	// send the data
	SPDR = Data;

	/* wait till transfer is done */
	while(GET_BIT(SPSR,SPSR_SPIF)==0)
	{
		LCD_CursorPosition(0,0);
		LCD_SendString("temprature =");
		digital =  ADC_AnalogReadSynchronous(ADC_CHANNEL_ADC0);
				digital /=2;
				LCD_DisplayNumber(digital);
				LCD_SendCharacter('C');
				LCD_CursorPosition(1,0);
				LDR_Reading = ADC_AnalogReadSynchronous(ADC_CHANNEL_ADC3);
				LCD_SendString("Light Int. =");

				LCD_DisplayNumber(LDR_Reading);
				LCD_SendCharacter(' ');
				if(LDR_Reading > 100)
				{
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN4,PIN_LOW);
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN5,PIN_LOW);
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN6,PIN_LOW);
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN7,PIN_LOW);
				}
				else if(LDR_Reading > 50 && LDR_Reading < 100)
				{
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN4,PIN_HIGH);
				DIO_SetPinLevel(DIO_PORTA,DIO_PIN5,PIN_LOW);
			    DIO_SetPinLevel(DIO_PORTA,DIO_PIN6,PIN_HIGH);
			    DIO_SetPinLevel(DIO_PORTA,DIO_PIN7,PIN_LOW);
			   }
			   else if( LDR_Reading < 50 )
			   {
			   DIO_SetPinLevel(DIO_PORTA,DIO_PIN4,PIN_HIGH);
			   DIO_SetPinLevel(DIO_PORTA,DIO_PIN5,PIN_HIGH);
			   DIO_SetPinLevel(DIO_PORTA,DIO_PIN6,PIN_HIGH);
			   DIO_SetPinLevel(DIO_PORTA,DIO_PIN7,PIN_HIGH);
			   }

	}
	/* Get the exchanged data */
	return SPDR;
}
