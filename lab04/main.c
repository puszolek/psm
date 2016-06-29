#include "lcd.h"

static int lcd_putchar(char c, FILE* stream);
static FILE mystdout = FDEV_SETUP_STREAM(lcd_putchar, NULL,_FDEV_SETUP_WRITE);


int main(void){

	stdout = &mystdout;
	DDRA = 0xFF;
	lcd_init();
	lcd_clear();
	float x = 6.66;
	printf("%f", x);

	while(1){

	}
}

static int lcd_putchar(char c, FILE* stream){
	lcd_write_data(c);
	return 0;
}


