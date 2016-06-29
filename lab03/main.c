#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t count;

ISR (INT0_vect){
	TCCR1B |= (1<<CS12);
}

ISR (TIMER1_OVF_vect){
	TCCR1B = 0;
	TCNT1 = 0xFFFF - 4300;

	if(!(PIND&(1<<2)))
		count++;
}

int main(void){

	count = 0;

	DDRA=0b11111111; //0xFF
	GICR |= (1<<INT0);
	MCUCR |= (1<<ISC01);
	TCNT1 = 0xFFFF - 4300;
	TIMSK |= (1<<TOIE1);
	sei();

	while(1){
		PORTA=~count;
	}
}



