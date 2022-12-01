#define _XTAL_FREQ  4000000
#include <xc.h>
/*
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
*/

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
