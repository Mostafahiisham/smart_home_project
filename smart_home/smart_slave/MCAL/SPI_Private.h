/*
 * SPI_Private.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Mostafa Hisham
 *      Layer : MCAL
 *      SWC   : SPI-PRIVATE
 */

#ifndef MCAL_SPI_PRIVATE_H_
#define MCAL_SPI_PRIVATE_H_

#define SPSR_SPIF		7		/*SPI INTERRUPT FLAG*/
#define SPSR_SPI2X		0		/*SPI prescaler bit 2*/

#define SPCR_SPE		6		/* SPI control register*/
#define SPCR_MSTR		4		/* SPI enable */
#define SPCR_SPR1		1		/* PRE-scaler bit 1*/
#define SPCR_SPR0		0		/* PRE-scaler bit 0*/

#endif /* MCAL_SPI_PRIVATE_H_ */
