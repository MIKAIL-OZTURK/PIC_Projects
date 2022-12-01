// Configurations 1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// Configurations 2 
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// LCD Pin Configurations 
#define LCD_RS       RD2
#define LCD_EN       RD3
#define LCD_D4       RD4
#define LCD_D5       RD5
#define LCD_D6       RD6
#define LCD_D7       RD7
#define LCD_RS_DIR   TRISD2
#define LCD_EN_DIR   TRISD3
#define LCD_D4_DIR   TRISD4
#define LCD_D5_DIR   TRISD5
#define LCD_D6_DIR   TRISD6
#define LCD_D7_DIR   TRISD7

#define _XTAL_FREQ 8000000               
#include <xc.h>                           
#include "LCD.h"                          

uint8_t DS18B20_Start();                      
void DS18B20_Write_Bit(uint8_t value);
void DS18B20_Write_Byte(uint8_t value);
uint8_t DS18B20_Read_Bit(void);
uint8_t DS18B20_Read_Byte(void);
uint16_t DS18B20_Read(uint16_t* raw_temp_value);

uint16_t raw_temp = 0;
char temp[] = "000.0000 C";

void main(void)
{
    OSCCON = 0x70;      
    ANSELH = 0;         
    __delay_ms(1000);   

    LCD_Begin();        
    LCD_CLEAR;

    temp[8] = 223;      

    while (1)
    {
        if (DS18B20_Read(&raw_temp))            
        {
            if (raw_temp & 0x8000)             
            {
                temp[0] = '-';                  
                raw_temp = (~raw_temp) + 1;     
                LCD_Goto(1, 2);               
                LCD_Print("Low Temperature");   
            }
            else                             
            {
                if ((raw_temp >> 4) >= 100)     
                {
                    temp[0] = '1';             
                    LCD_Goto(1, 2);             
                    LCD_Print("High Temperature"); 
                }
                else                          
                {
                    temp[0] = ' ';      
                    LCD_Goto(1, 2);
                    LCD_Print("                           ");
                }
            }
            
            temp[1] = (((raw_temp >> 4) / 10) % 10 + '0');  
            temp[2] = ((raw_temp >> 4) % 10 + '0');
            temp[4] = (((raw_temp & 0x0F) * 625) / 1000 + '0');        
            temp[5] = ((((raw_temp & 0x0F) * 625) / 100) % 10 + '0');  
            temp[6] = ((((raw_temp & 0x0F) * 625) / 10) % 10 + '0');      
            temp[7] = (((raw_temp & 0x0F) * 625) % 10 + '0');             

            LCD_Goto(4, 1);     
            LCD_Print(temp);    
        }
        else    
        {
            LCD_Goto(4, 2);             
            LCD_Print("  Error!  ");
        }
        __delay_ms(1000);                
    }
}


uint8_t DS18B20_Start()
{
    RB1 = 0;              
    TRISB1 = 0;           
    __delay_us(500);      

    TRISB1 = 1;           
    __delay_us(100);      

    if (!RB1)
    {
        __delay_us(400);    
        return 1;           
    }
    return 0;               
}


void DS18B20_Write_Bit(uint8_t value)
{
    RB1 = 0;
    TRISB1 = 0;          
    __delay_us(2);       

    RB1 = (__bit)value;
    __delay_us(80);       

    TRISB1 = 1;         
    __delay_us(2);       
}


void DS18B20_Write_Byte(uint8_t value)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        DS18B20_Write_Bit(value >> i);
    }
}


uint8_t DS18B20_Read_Bit(void)
{
    static __bit value;

    RB1 = 0;
    TRISB1 = 0;             
    __delay_us(2);

    TRISB1 = 1;             
    __delay_us(5);          

    value = RB1;            
    __delay_us(100);        

    return value;
}


uint8_t DS18B20_Read_Byte(void)
{
    uint8_t value = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        value |= DS18B20_Read_Bit() << i;
    }
    return value;
}


uint16_t DS18B20_Read(uint16_t* raw_temp_value)
{
    if (!DS18B20_Start())            
    {
        return 0;                       
    }
    
    DS18B20_Write_Byte(0xCC);          
    DS18B20_Write_Byte(0x44);         
    
    while (DS18B20_Read_Byte() == 0);   
    
    if (!DS18B20_Start())              
    {
        return 0;                       
    }
    
    DS18B20_Write_Byte(0xCC);           
    DS18B20_Write_Byte(0xBE);           
    
    *raw_temp_value = DS18B20_Read_Byte();
    *raw_temp_value |= (uint16_t)(DS18B20_Read_Byte() << 8);
    
    return 1;   
}