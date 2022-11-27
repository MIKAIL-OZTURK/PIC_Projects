#define _XTAL_FREQ  8000000     // MCU Frequence 8MHz

/* LCD PINS */
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include <lcd.h>

#pragma config FOSC = HS        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void main(void) 
{
    TRISD = 0x00;
    PORTD = 0x00;
    
    Lcd_Init();
    
    while(1)
    {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Merhaba Dunya.");
        
        for(int i = 0; i<15; i++)
        {
            __delay_ms(250);
            Lcd_Shift_Left();
        }

        for(int i = 0; i<15; i++)
        {
            __delay_ms(250);
            Lcd_Shift_Right();
        }
        Lcd_Clear();
    }
    return;
}
