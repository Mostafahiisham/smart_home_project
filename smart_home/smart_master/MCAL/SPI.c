/*
 * SPI.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Mostafa Hisham
 *      Layer : MCAL
 *      SWC   : SPI-IMPLEMENTATION
 */
#include<Std_Types.h>
#include<Registers.h>
#include<Macros.h>
#include<SPI.h>
#include<SPI_Private.h>

void SPI_Master_Init(void)
{
	/* SELECT MASTER OR SLAVE Bit -> bit no.4 */
	/*Master Intilization */
	SET_BIT(SPCR,SPCR_MSTR);
	/*select the clock frequency */
	// Set the frequency to F osc./16;
	SET_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI-enable*/
	SET_BIT(SPCR,SPCR_SPE);
	/* DATA ORDER  DEFAULT (MSB)*/



}
void SPI_Slave_Init(void)
{
	/* SELECT Master or Slave Bit -> bit no.4 */
	/* Slave Initilization */
	CLR_BIT(SPCR,SPCR_MSTR);
	/*SPI-enable*/
	SET_BIT(SPCR,SPCR_SPE);
	/* DATA ORDER  DEFAULT (MSB)*/
}

u8 SPI_Transceive(u8 Data)
{
	/* FUNCTION TO SEND AND RECEIVE DATA */
	// send the data
	SPDR = Data;

	/* wait till transfer is done */
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	/* Get the exchanged data */
	return SPDR;
}
