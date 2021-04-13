/*
 * File:   Lab07.c
 * Author: fredy
 *
 * Created on April 12, 2021, 11:12 PM
 */


#include <xc.h>
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

    

void main(void) {
    // Oscilador
    IRCF0 = 1;       // Configuración del reloj interno 
    IRCF1 = 1;
    IRCF2 = 0;       // 500khz   
    // Configurar Timer0
    PS0 = 1;
    PS1 = 0;
    PS2 = 1;         //Prescaler de 64
    T0CS = 0;
    PSA = 0;
    INTCON = 0b10101000;
    
    // Configurar puertos
    TRISA = 0;  // Definir el puerto A como salida
    TRISC = 0;  // Definir el puerto C como salida
    TRISD = 0;  // Definir el puerto D como salida
    TRISE = 0;  // Definir el puerto D como salida
    //Limpieza de puertos
    PORTB = 0;
    PORTC = 0;
    PORTD = 01;
    PORTE = 0;
    // Declaraciones de variables
    int B_Inc = RB7;
    int B_Dec = RB6;
    int Unidades = RE2;
    int Decenas  = RE1;
    int Centenas = RE0;
    int Contador1 = 0;
    //loop principal
    for(;;){  
        
        RE2 =1;
        
    } // fin loop principal while
    
} // fin main

void __interrupt() isr (void){
    
    // Interrupcion del timer0
    if (T0IF == 1){
        T0IF = 0;
        
        TMR0 = 0;    
    } // Fin de If interrupcion timer0
}