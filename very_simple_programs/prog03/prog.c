#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t pwm_val = 128;

ISR(INT0_vect)
{
	PORTC |= (1 << PC0);
	pwm_val += 8;
}

ISR(INT1_vect)
{
	PORTC |= (1 << PC1);
	pwm_val -= 8;
}

int main(void)
{
	//Ports I/O
	DDRC = (1 << PC0) | (1 << PC1); // Two outputs for LED's
	DDRD = 0x00; //Only inputs
	PORTC = 0x00; //Low states on pins
	PORTD = (1 << PD2) | (1 << PD3); //Two pullup's on switches

	//Interrupts:	
	GICR = (1 << INT0) | (1 << INT1);
	MCUCR = (1 << ISC01); //Falling edge

	//PWM Timer settings:
	DDRB |= (1 << PB3);
	OCR2 = 128; //Duty 50%
	TCCR2 |= (1 << COM21); //Non-invert mode
	TCCR2 |= (1 << WGM21) | (1 << WGM20); //Fast Mode
	TCCR2 |= (1 << CS21); //Start 8kHz clock

	sei();
	while(1)
	{
		PORTC &= 0b11111100; //Zero on LED's outputs

		if(pwm_val < 1) pwm_val=1;
		if(pwm_val > 255) pwm_val=254;

		OCR2 = pwm_val;

		_delay_ms(5);	
	}

	return 0;
}
