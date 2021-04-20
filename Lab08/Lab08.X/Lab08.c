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
//------------------------------------------------------------------------------
//***************************** Prototipos *************************************
void C_D_U (char variable);
void Multiplexar(void);
//------------------------------------------------------------------------------
//*************************** Interrupciones ***********************************
void __interrupt() isr (void){
    // Interrupcion del timer0
    if (T0IF == 1){
        //Contador1++;
        multi = 1;
        TMR0 = 246;  
        T0IF = 0;
    } // Fin de interrupción timer0
    
    // Interrupcion del PORTB
    if (RBIF == 1){
       
        if(RB6 == 0){
            PORTC++;
        }
        if(RB7 == 0){
            PORTC--;
        }
        RBIF = 0; 
    }// Fin de interrupción del PORTB
}    

void main(void) {
    
    // Oscilador
    IRCF0 = 0;       // Configuración del reloj interno 
    IRCF1 = 1;
    IRCF2 = 1;       // 4 Mhz   
    
    // Configurar Timer0
    PS0 = 1;
    PS1 = 0;
    PS2 = 1;         //Prescaler de 64
    T0CS = 0;
    PSA = 0;
    INTCON = 0b10101000;
    TMR0 = 246;
    
    // Configuración del puerto B
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB7=1;
    WPUBbits.WPUB6=1;
    
    // Activación Interrup on change
    IOCB7 = 1;
    IOCB6 = 1;
    
    // Configurar puertos
    ANSEL  = 0;
    ANSELH = 0;
    TRISA  = 0b11111000;  // Definir el puerto A como salida
    TRISC  = 0;  // Definir el puerto C como salida
    TRISD  = 0;  // Definir el puerto D como salida
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
        if (multi == 1){
            Multiplexar();
        }
    } // fin loop principal while 
} // fin main


void Multiplexar (void){
    char tabla [16]= {
        0b0111111, // Cero
        0b0000110, // Uno
        0b1011011, // Dos
        0b1001111, // Tres
        0b1100110, // Cuatro
        0b1101101, // Cinco
        0b1111101, // Seis 
        0b0000111, // Siete
        0b1111111, // Ocho
        0b1100111, // Nueve
        0b1110111, // A
        0b1111100, // B
        0b0111001, // C
        0b1011110, // D
        0b1111001, // E
        0b1110001, // F
    }; 
    multi = 0;
    C_D_U(PORTC);
    PORTD = 0;
    if (RA0 == 1){
        PORTD = tabla[Decena];
        PORTA = 0b010;
    }
    else if(RA1 == 1){
        PORTD = tabla[Unidad];
        PORTA = 0b100;
    }
    else{
        PORTD = tabla[Centena];
        PORTA = 0b001;
    }
}
void C_D_U (char variable){
    Division = variable/100;
    Centena = (int)Division;
    
    variable = variable-100*Centena;
    Division = variable/10;
    Decena = (int)Division;
    
    
    variable = variable-10*Decena;
    Division = variable;
    Unidad = (int)Division;
    //char Valores[3]={Centena,Decena,Unidad};
    //return Valores;
}
  