/* LCD PINS */  
#define RS  RD2
#define EN  RD3
#define D4  RD4
#define D5  RD5
#define D6  RD6
#define D7  RD7

#define _XTAL_FREQ  8000000     // MCU Frequence 8 MHz
#include <xc.h>
#include <lcd.h>                // LCD Library
#include <stdio.h>

void main(void) 
{
    TRISD = 0x00;               // LCD is output
    PORTD = 0x00;               // LCD is reset
    
    char array[20]; 
    float temperature = 24.5;
    
    Lcd_Init();
    Lcd_Clear();
    
    while(1)
    {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Merhaba");
        
        sprintf(array, "Sicaklik = %f", temperature);
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(array);
        __delay_ms(1000);
    }
    return;
}
