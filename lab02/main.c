#include <avr/io.h>
#include <util/delay.h>

void longdelay(uint16_t ms);

int main(void) {

	DDRA = 0b00001111;
	uint16_t delay = 10;
	uint8_t run = 0;
	uint8_t direction = 0;

	while(1){
		if (!(PINA & 1 << 6)){
			delay+=2;
			longdelay(200);
		}else if (!(PINA & 1 << 7)){
			delay-=2;
			longdelay(200);
		}
		else if(run){
			if (direction){
				PORTA = 0b00000011;
				longdelay(delay);
				PORTA = PORTA << 1;
				longdelay(delay);
				PORTA = PORTA << 1;
				longdelay(delay);
				PORTA = 0b00001001;
				longdelay(delay);
			} else {
				PORTA = 0b00001001;
				longdelay(delay);
				PORTA = 0b00001100;
				longdelay(delay);
				PORTA = 0b00000110;
				longdelay(delay);
				PORTA = 0b00000011;
				longdelay(delay);
			}
		}
		if (!(PINA & 1 << 4)){
			run = !run;
			longdelay(500);
		}
		if (!(PINA & 1 << 5)){
			direction = !direction;
			longdelay(500);
		}
	}
}

void longdelay(uint16_t ms){
	for (uint16_t i = 0; i < ms; i++)
		_delay_ms(1);
}


