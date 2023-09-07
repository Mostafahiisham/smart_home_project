/*
 * SPI.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Mostafa Hisham
 *      Layer : MCAL
 *      SWC   : SPI-PROTOTYPE
 */

#ifndef MCAL_SPI_H_
#define MCAL_SPI_H_



void SPI_Master_Init(void);
void SPI_Slave_Init(void);
u8 SPI_Transceive(u8 Data);








#endif /* MCAL_SPI_H_ */
