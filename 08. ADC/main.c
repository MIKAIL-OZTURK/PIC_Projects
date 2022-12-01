#define _XTAL_FREQ  8000000     // MCU Frequence 8 MHz
#include <xc.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned int Read_ADC(unsigned char channel)
{
    if((channel < 0) || (channel > 7))
    {
        return 0;
    }
    
    ADCON0 &= 0b11000101;
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8 ) + ADRESL);
}


void main(void) 
{
    unsigned int ADC_Value = 0;
    
    TRISA = 0xFF;
    TRISB = 0x00;
    TRISC = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    ADCON0 = 0b10010001;
    ADCON1 = 0b10000000;
    
    while(1)
    {
        ADC_Value = Read_ADC(0);
        PORTB = ADC_Value;
        PORTC = ADC_Value >> 8;
    }
    return;
}
