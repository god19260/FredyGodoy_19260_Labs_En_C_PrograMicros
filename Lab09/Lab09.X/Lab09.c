/*
 * File:   Lab08.c
 * Author: fredy
 *
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (RC oscillator: 
                // CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
                                // pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
                                // protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
                                // protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit 
                                //(Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
                                // (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM 
                       // pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out 
                                // Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable 
                                // bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//------------------------------------------------------------------------------
//********************* Declaraciones de variables *****************************
    char  Contador1 = 0;
    char  Dis_Centena;
    char  Dis_Decena;
    char  Dis_Unidad;
    float Division;
    char  Centena;
    char  Decena;
    char  Unidad;
    char  multi = 1;
    char  V_Display = 0;
//------------------------------------------------------------------------------
//***************************** Prototipos *************************************

//------------------------------------------------------------------------------
//*************************** Interrupciones ***********************************
void __interrupt() isr (void){
    // Interrupcion del ADC module
    if (ADIF == 1){
        ADIF = 0;
        if (ADCON0bits.CHS == 3){
            PORTB = ADRESH;
            CCPR1L = (PORTB >> 1) + 126.1;
            CCP1CONbits.DC1B1 = PORTBbits.RB0;
            CCP1CONbits.DC1B0 = ADRESL>>7;
            
            ADCON0bits.CHS = 4;
        } 
        else{
            PORTB = ADRESH;
            CCPR2L = (PORTB >> 1) + 125.5;
            CCP2CONbits.DC2B1 = PORTBbits.RB0;
            CCP2CONbits.DC2B0 = ADRESL>>7;
            ADCON0bits.CHS = 3;
        }   
        __delay_us(50);
        ADCON0bits.GO = 1; 
    }
  
}    

void main(void) {
    
    // Oscilador
    IRCF0 = 1;       // Configuración del reloj interno 
    IRCF1 = 1;
    IRCF2 = 1;       // 4 Mhz   
  
    INTCON = 0b11101000;
 
    // Configurar PWM
    PR2 = 249;
    CCP1CONbits.P1M = 0;
    CCP1CONbits.CCP1M = 0b00001100;
    CCP2CONbits.CCP2M = 0b00001100;
    CCPR1L = 0x0F;
    CCPR2L = 0x0F;
    CCP1CONbits.DC1B = 0;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 0;
    
    // Configurarcion del TMR2
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS0 = 1; //prescaler de 16
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.TMR2ON = 1;
   
    // Configuración del modulo ADC
    PIE1bits.ADIE = 1;
    ADIF = 0; // Bandera de interrupción
    ADCON1bits.ADFM = 0; // Justificado a la izquierda    
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG0 = 0; // Voltajes de referencia en VSS y VDD
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 1; // FOSC/8
    ADCON0bits.ADON = 1;
    __delay_us(50);
    ADCON0bits.GO = 1;

    // Configurar puertos
    ANSEL  = 0b00011000;
    ANSELH = 0;
    TRISA  = 0b11111000;  // Definir el puerto A como salida
    TRISC  = 0;  // Definir el puerto C como salida
    TRISD  = 0;  // Definir el puerto D como salida
    TRISB  = 0;  // Definir el puerto B como salida
    TRISE  = 0;  // Definir el puerto E como salida
    
    //Limpieza de puertos
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    RA0 =1;
    
    //loop principal
    while(1){  
        
    } // fin loop principal while 
} // fin main


  