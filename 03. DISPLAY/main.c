#define _XTAL_FREQ 4000000
#include <xc.h>

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


const unsigned char disp[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void main(void)
{
    unsigned char i = 0;
    TRISB = 0x01;
    TRISC = 0;
    PORTC = 0x3F;   // Display 0

    while (1)
    {
        if (RB0)
        {
            i++;
            if (i == 10)
            {
                i = 0;
            }
            PORTC = disp[i];
            while (RB0);
        }
        if (RB1)
        {
            i--;
            if (i = 255)
            {
                i = 9;
            }
            PORTC = disp[i];
            while (RB1);
        }
        if (RB2)
        {
            i = 0;
            PORTC = disp[i];
            while (RB2);
        }

    }
    return;
}
