/*
	Contador de 0 à 9 com entrada de reset
	
	>> Lógica	
	   > Ao pressionar o botão P, a contagem será incrementada;
	   > Se passar de 9, volta para 0;
	   > Em qualquer momento, se pressionar o botão R, a contagem
	   será zerada.
	   
			 BOTÃO P -> RC0 
			 BOTÃO R -> RB7 (resistor de pull-up)
	PINOS DO DISPLAY -> RB0 à RB6
	    PINO BOLINHA -> RESISTOR DE 470
*/

#include <16F877A.h>
#include "registradores16F.h"
#include "Pisca_Alerta.h"

#define Incremento PIN_C0
#define Reset      PIN_B7

int num = 0; // Contador para a contagem no display de 7 segmentos

void setup()
{
	// Periféricos //
	set_tris_b(0b10000000);	  // Define o pino RB7 como entrada (Reset)
	port_b_pullups(TRUE); 	  // Botão de Reset ativado em nível lógico 0
	set_tris_c(0b11111111);	  // Define o pino RC0 como entrada (Incremento) 
   
    // Timer 1 no modo contador com prescaler 1:1 e interrupções habilitadas //
    setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
    set_timer1(0);
    enable_interrupts(INT_TIMER1);
    enable_interrupts(GLOBAL);
    T1CON = 1;
    
    config_timer0();
}

void display1(int dig)
{
   // Tabela de segmentos para exibir os dígitos de 0 à 9
   					                  //  Pgfedcba
   const int segmentos[10] = {			0b00111111,  // 0
                                        0b00000110,  // 1
                                        0b01011011,  // 2
                                        0b01001111,  // 3
                                        0b01100110,  // 4
                                        0b01101101,  // 5
                                        0b01111101,  // 6
                                        0b00000111,  // 7
                                        0b01111111,  // 8
                                        0b01101111}; // 9
		
	PORTB = segmentos[dig];
}
/*
#int_timer1
void interrupcao()
{
}
*/

void main()
{  
	setup();
	Pisca_Alerta();
	display1(6);
		
    while (1)
    {
	    num = get_timer1();
	    
	    if(num > 9)
	    {
	    	num = 0;
	    }
	    
	    display1(6);
	}
}
#ORG 0x1E80, 0x1EFF{}

/*
						CÁLCULOS
				
	>> O Timer 1 é um temporizador de 16 bits, o que significa que pode contar até 
	o valor máximo de 65535 (0xFFFF) antes de ocorrer um estouro (overflow). 
	
	O valor inicial do Timer é definido pelos registradores TMR1H e TMR1L
	>> O período de cada contagem do Timer 1 usando a fórmula:
		Tempo de estouro (ms) = (Período do Timer1) * (Valor máximo do Timer1)
		Tempo de estouro (ms) = (0,2us) * 65535 = 13.107 ms = 0,013107s
*/