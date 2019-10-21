#include <avr/io.h>
#include <util/delay.h>

void sleep(uint16_t millisec)
{
        while(millisec)

        {
                _delay_ms(1);
                millisec--;
        }
}

main()
{

        DDRC |=1<<PC2;
        while(1)
        {
                PORTC &= ~(1<<PC2);
                sleep(1000);
                PORTC |=(1<<PC2);
                sleep(1000);
        }
}
