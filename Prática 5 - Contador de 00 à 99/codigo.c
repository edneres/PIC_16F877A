/*
#include <16F877A.h>
#include "Pisca_Alerta.h"
#include "registradores16F.h"
//#byte PORTD = 0x08

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
	port_b_pullups(TRUE);	
	set_tris_d(0x00);		// Transistores como sa�da
	//PORTD = 0b00000000; // Displays come�am desligados
	
	
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
	/*
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
		
		ms_delay(20);
					
		transistor_dez = 1;
		//PORTD = 0b00001000;
		display(dezena);
		ms_delay(10);
		//PORTD = 0b00000000;
		transistor_dez = 0;
	}
}*/

#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    // Watch Dog Timer disabled (WDT disabled)
#FUSES HS                       // High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    // No Power Up Timer
#FUSES NOPROTECT                // Code not protected from reading
#FUSES NODEBUG                  // No Debug mode for ICD
#FUSES BROWNOUT                 // Reset when brownout detected
#FUSES NOLVP                    // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    // No EE protection
#FUSES NOWRT                    // Program memory not write protected

#use delay(clock=20000000)       // Define a frequ�ncia do clock

#define LED_PIN PIN_A0            // Pino do LED

void main()
{
   setup_ccp1(CCP_PWM);           // Configura CCP1 como sa�da PWM
   setup_timer_2(T2_DIV_BY_16, 249, 1);  // Configura Timer2 para fornecer a frequ�ncia do PWM
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);  // Configura Timer0 para gerar o atraso
   
   int dutyCycle = 0;
   
   while (1)
   {
      if (tmr0_flag)  // Verifica se a flag de estouro do Timer0 est� ativada
      {
         tmr0_flag = 0;  // Limpa a flag de estouro do Timer0
         
         dutyCycle++;  // Incrementa o ciclo ativo do sinal PWM
         
         if (dutyCycle > 255)
            dutyCycle = 0;  // Volta para 0 quando atingir o m�ximo
         
         set_pwm1_duty(dutyCycle);  // Define o ciclo ativo do sinal PWM
      }
   }
}


#ORG 0x1E80, 0x1EFF{}