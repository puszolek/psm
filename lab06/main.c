#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

volatile uint8_t buff[8];
volatile uint8_t led;
volatile uint8_t counter;


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
		;
	/* Put data into buffer, sends the data */
	UDR = data;
}


ISR (USART_RXC_vect){

	buff[counter++]=UDR;

	if (buff[counter-1] == '\n'){

		counter = 0;
		if (!strncmp(buff, "on", 2))
			led = 1;
		else if (!strncmp(buff, "off", 2))
			led = 0;
		else if (!strncmp(buff, "dupa", 2)){
			USART_Transmit(' ');
			USART_Transmit('c');
			USART_Transmit('h');
			USART_Transmit('y');
			USART_Transmit('b');
			USART_Transmit('a');
			USART_Transmit(' ');
			USART_Transmit('t');
			USART_Transmit('y');
			USART_Transmit(' ');
		}
	}
}


void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

int main(void){

	USART_Init(71);
	sei();

	DDRD = 0b00000010;
	DDRA = 0b00000001;
	DDRC = 0b00000001;

	while(1){
		if(led)
			PORTA = 0b00000000;
		else
			PORTA = 0b00000001;
	}
}


