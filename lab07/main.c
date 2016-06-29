#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

#define DD_SS 4

static int lcd_putchar(char c, FILE* stream);
static FILE mystdout = FDEV_SETUP_STREAM(lcd_putchar, NULL,_FDEV_SETUP_WRITE);

static int lcd_putchar(char c, FILE* stream){
	lcd_write_data(c);
	return 0;
}

int main(void){

	DDRA=0b11111111;
	stdout = &mystdout;
	SPI_MasterInit();
	lcd_init();

	while(1){
		PORTB &= ~(1<<DD_SS);
		SPI_mtr(1);
		uint16_t hi = SPI_mtr(0b10100000);
		uint16_t lo = SPI_mtr(0);
		hi &= 0x0F;
		uint16_t dane = (hi << 8) | lo;
		float d = dane*5000.0/4096.0;
		PORTB |= (1<<DD_SS);
		lcd_clear();
		printf("%.2f mV", d);
		_delay_ms(300);

	}
}


