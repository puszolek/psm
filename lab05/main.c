#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t digits[10]={
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10010000
};

volatile uint8_t cyfry[4];
volatile uint8_t anode;

void clear_anodes(){
	PORTA |= 0xF0;
}

void set_anode(uint8_t anode){
	PORTA &= ~(1<<(anode+4));
}

void display(uint16_t x){
	cyfry[0] = x%10;
	cyfry[1] = (x/10)%10;
	cyfry[2] = (x/100)%10;
	cyfry[3] = (x/1000)%10;
}

ISR (TIMER1_OVF_vect){
	TCNT1 = 0xFFFF - 4300;
	clear_anodes();
	PORTC = digits[cyfry[anode]];
	set_anode(anode++);
	anode = anode%4;
}

int main(void){

	anode = 0b00000000;
	uint16_t liczba = 6969;

	DDRA = 0xF0;
	DDRC = 0xFF;
	PORTA |= 0xF0;

	TCNT1 = 0xFFFF - 4300;
	TIMSK |= (1<<TOIE1);
	TCCR1B |= (1<<CS11);

	sei();
	uint16_t x = 0;

	while(1){

		display(x++);
		_delay_ms(10);

		if (x == 9999)
			x = 0;

	}
}


