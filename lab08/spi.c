/*
 * spi.c
 *
 *  Created on: 31-03-2016
 *      Author: psm8
 */

#include <avr/io.h>

#define DD_MOSI 5
#define DD_SCK 7
#define DD_SS 4

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t SPI_mtr(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
		;
	return SPDR;
}
