/*
 * File:   Lab10.c
 * Author: fredy
 *
 * Created on May 3, 2021, 1:12 PM
 */

#include <xc.h>
#define _XTAL_FREQ 8000000

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RC oscillator: 
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
int V_Receptor;
int Entrada;
int continuar = 0;
int Valor;
//------------------------------------------------------------------------------
//***************************** Prototipos *************************************
void Texto(char texto[]);
void Menu(void);
//------------------------------------------------------------------------------
//*************************** Interrupciones ***********************************
void __interrupt() isr (void){
    if (RCIF == 1){
        RCIF = 0; 
        RA0 = 1;
        Valor = RCREG;
        continuar = 1;
        if (RCREG == '1'){ // 1 en hexa
            Entrada = 1;
        } else if(RCREG == '2'){
            Entrada = 2;
        }else if(RCREG == '3'){
            Entrada = 3;
        }
            
    }
}    

void main(void) {
    
    // Oscilador
    IRCF0 = 1;       // Configuración del reloj interno 
    IRCF1 = 1;
    IRCF2 = 1;       // 8 Mhz   
 
    // Configuración de Asynchronous TRANSMITTER
    TXEN = 1;
    SYNC = 0;
    SPEN = 1;
    INTCON = 0b11101000;
    // Configuración de Asynchronous RECEIVER
    CREN = 1;
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
    SPBRG=12;  // baudrate 9600 para 8MHz
  
    // Configurar puertos
    ANSEL  = 0;
    ANSELH = 0;
    TRISB  = 0;  // Definir el puerto A como salida
    TRISD  = 0;  // Definir el puerto D como salida
    TRISA  = 0;  // Definir el puerto D como salida
    
    //Limpieza de puertos
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
       
    //loop principal
    //Texto("Hola a todos \r0");
    Menu();
    while(1){  
        if (Entrada == 1){
           Texto("\r");
           Texto("Hola a Todos \r");
           Entrada = 0;
           Texto("\r");
           Texto("\r");
           Menu();
       }else if (Entrada == 2){
           Texto("\r");
           Texto("Ingresa un caracter para el puerto B: ");
           continuar = 0;
           Valor = 0;
           while(continuar == 0){
               __delay_ms(100);
               PORTB = Valor;  
           }
           Entrada = 0;
           Texto("\r");
           Texto("\r");
           Menu();
       }else if (Entrada == 3){
           Texto("\r");
           Texto("Ingresa un caracter para el puerto D: ");
           continuar = 0;
           Valor = 0;
           while(continuar == 0){
               __delay_ms(100);
               PORTD = Valor;  
           }
           Entrada = 0;
           Texto("\r");
           Texto("\r");
           Menu();
       }
       
      
    } // fin loop principal while 
} // fin main

void Texto(char texto[]){
    char i = 0;
    while(texto[i] != '\0'){
        TXREG = texto[i];
        i++;
        __delay_ms(20);
    }
}
void Menu(void){
    Texto("Que accion desea ejcutar? \r");
    Texto("(1) Desplegar cadena de caracteres \r");
    Texto("(2) Cambiar PORTB \r");
    Texto("(3) Cambiar PORTD \r");
}  