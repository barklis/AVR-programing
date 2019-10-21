#include <avr/io.h>
#include <util/delay.h>

const int hz = 1000;
int pwm_val = 128;

int main(void)
{
	DDRC = 0b00000011;
	PORTC = 0b00001100;

	DDRB |= (1 << PB3);
	OCR2 = 128; //Duty 50%
	TCCR2 |= (1 << COM21); //Non-invert mode
	TCCR2 |= (1 << WGM21) | (1 << WGM20); //Fast Mode
	TCCR2 |= (1 << CS21); //Start 8kHz clock

	while(1)
	{
		PORTC &= 0b11111100;
		if(!(PINC & 0b00000100))
		{
			PORTC |= 0b00000001;
			//PORTC &= 0b11111101;
			pwm_val++;	
		}
		if(!(PINC & 0b00001000))
		{
			PORTC |= 0b00000010;
			//PORTC &= 0b11111110;
			pwm_val--;
		}

		if(pwm_val < 1) pwm_val=1;
		if(pwm_val > 255) pwm_val=254;

		OCR2 = pwm_val;

		_delay_ms(5);	
	}

	return 0;
}
