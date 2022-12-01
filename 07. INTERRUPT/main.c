#define _XTAL_FREQ  4000000
#include <xc.h>

void __interrupt() KESME(void)
{
    GIE = 0;
    if (RBIF)
    {
        if (RB5)
        {
            PORTC++;
            if (PORTC == 10)
            {
                PORTC = 0;
            }
        }
        if (RB6)
        {
            PORTC--;
            if (PORTC = 255)
            {
                PORTC = 9;
            }
        }
        if (RB7)
        {
            PORTC = 0;
        }
        RBIF = 0;
    }

    GIE = 0;
}

void main(void)
{
    /* GPIO Configurations */
    TRISB = 0xFF;
    TRISC = 0;
    PORTC = 0;

    /* Interrupt Configurations */
    RBIE = 1;
    RBIF = 0;
    GIE = 1;

    while (1)
    {
        
    }
    return;
}
