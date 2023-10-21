#include <16F877A.h>
#include "Pisca_Alerta.h"
#include "registradores16F.h"

//#define Incremento PIN_C0 // N�o precisa, pois com o bot�o, a onda � gerada automaticamente, "estourando" o timer1
#bit transistor_unid = PORTD.2	// Display 1
#bit transistor_dez	 = PORTD.3	// Display 2

unsigned int8 contagem;
unsigned int8 unidade; 
unsigned int8 dezena; 
unsigned int8 delay; 

void setup()
{
	// Perif�ricos //
	set_tris_b(0x00);	// RB0 � RB7 para o display
	set_tris_c(0xFF);	// RC0 para o Bot�o de Incremento 
	setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);	// RC0 como fonte do clock 
	port_b_pullups(TRUE);	// Reset ativado em 0
	set_tris_d(0x00);		// Transistores como sa�da
	PORTD = 0b00000000; // Displays come�am desligados
	
    // Timer 1 no modo contador com prescaler 1:1 e interrup��es habilitadas //
    setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
	port_b_pullups(TRUE);
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER1);
	set_timer1(0);
    
    config_timer0();
}

void display(unsigned int8 num)
{
   // Tabela de segmentos para exibir os d�gitos de 0 � 9
   					                  //  Pgfedcba
   const unsigned int8 segmentos[10] = {0b00111111,  // 0
                                        0b00000110,  // 1
                                        0b01011011,  // 2
                                        0b01001111,  // 3
                                        0b01100110,  // 4
                                        0b01101101,  // 5
                                        0b01111101,  // 6
                                        0b00000111,  // 7
                                        0b01111111,  // 8
                                        0b01101111}; // 9
		
	PORTB = segmentos[num];
}

void ms_delay(unsigned int8 tempo)
{
	unsigned int8 i, j;
	
	for(i = 0; i < tempo; i++);
	for(j = 0; j < 254; j++);
}


void main()
{  
	setup();
	Pisca_Alerta();
	
	/*	
    while (1)	// Funcional na PR�TICA!
    {  		
		for(dezena = 0; dezena < 10; dezena++)
		{
			for(unidade = 0; unidade < 10; unidade++)
			{
				for(delay = 0; delay < 200; delay++)  // Tempo razo�vel de ciclo de m�quina
				{
					transistor_unid = 1;
					//PORTD = 0b00000100;
					display(unidade);
					ms_delay(10);
					//PORTD = 0b00000000;
					transistor_unid = 0;
					
					transistor_dez = 1;
					//PORTD = 0b00001000;
					display(dezena);
					ms_delay(10);
					//PORTD = 0b00000000;
					transistor_dez = 0;
				}
			}
		}
	}
	*/
	
	while(1)
	{
		contagem = get_timer1();
		
		if(contagem == 100)
		{
			set_timer1(0);
			// contagem = 0;
		}
		
		unidade = contagem%10;
		dezena  = contagem/10;
		
		transistor_unid = 1;
		//PORTD = 0b00000100;
		display(unidade);
		ms_delay(10);
		//PORTD = 0b00000000;
		transistor_unid = 0;
					
		transistor_dez = 1;
		//PORTD = 0b00001000;
		display(dezena);
		ms_delay(10);
		//PORTD = 0b00000000;
		transistor_dez = 0;
		
		ms_delay(95);
	}
}

#ORG 0x1E80, 0x1EFF{}