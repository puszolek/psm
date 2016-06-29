#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	DDRA = 1;

	//int i = 0;

	while(1) {

		if(PINA & (1<<1)) {
			PORTA = 0;
		} else {
			PORTA = 1;
		}
		_delay_ms(100);
		//i++;
	}
}
