/*
	LED Vermelho: 3s	(RD7)
	LED Amarelo:  0,5s	(RD6)
	LED Verde:    1s	(RD5)
	Bot�o:			    (RB0)
	
	SEQU�NCIA = G, Y, R
	
	  Ao pressionar o bot�o 'p' (RD0 - pull up ativado) e se
	estiver no LED Verde (RD5), vai saltar a sequ�ncia acima
	p/ acionar o LED Vermelho (RD7) imediatamente.
	
	OBS: usar a biblioteca criada p/ piscar o LED no pino RD1.
*/

#include <16F877A.h>
#include "registradores16F.h"
#include "Pisca_Alerta.h"

#define LED_VERMELHO PIN_D7
#define LED_AMARELO  PIN_D6
#define LED_VERDE    PIN_D5
#define Botao		 PIN_B0

unsigned int16 contador = 0;  // Contador para controlar os tempos dos LEDs

void setup()
{
   // Perif�ricos
   set_tris_d(0b00000000);  // Define RD7, RD6, RD5 como sa�da
   set_tris_b(0b00000001);  // Define RB0 como entrada
   port_b_pullups(TRUE); 	// Bot�o ativado em n�vel l�gico 0
   
   config_timer0();
   
   // Configura o Timer 1 no modo temporizador
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   
   // Habilita a interrup��o do Timer 1
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   
   // Inicia o Timer 1
   set_timer1(0);
}

#int_timer1
void interrupcao()
{
   set_timer1(0);
   contador++;
   
   // LED Verde por 1 segundo
   if (contador <= 10)  // 1 / 0,104
   {
      output_low(LED_VERMELHO);    // Apaga o LED vermelho
      output_low(LED_AMARELO);     // Apaga o LED amarelo
      output_high(LED_VERDE);      // Acende o LED verde
      
      if(input(Botao) == 0)
      {
      	contador = 15;
      }
   }
   
   // LED Amarelo por 0,5 segundos
   if (contador <= 14 && contador > 10) // 1,5 / 0,104
   {
      output_low(LED_VERMELHO);    // Apaga o LED vermelho
      output_high(LED_AMARELO);    // Acende o LED amarelo
      output_low(LED_VERDE);       // Apaga o LED verde
   }
   
   // LED Vermelho por 3 segundos
   if (contador <= 43 && contador > 14) // 4,5 / 0,104
   {
      output_high(LED_VERMELHO);   // Acende o LED vermelho
      output_low(LED_AMARELO);     // Apaga o LED amarelo
      output_low(LED_VERDE);       // Apaga o LED verde
   }
    
   // Reinicia o contador para retornar ao LED Verde
   if (contador > 43)
   {
      contador = 0;
   }
}

void main()
{
   setup();
   Pisca_Alerta();
   
   while(1)
   {
      // O c�digo dentro da fun��o de interrup��o (timer1_isr) ser� executado a cada interrup��o do Timer 1
   }
}


#ORG 0x1E80, 0x1EFF{}

// C�DIGO OK NA PR�TICA 

/*
						C�LCULOS
				
	>> O Timer 1 � um temporizador de 16 bits, o que significa que pode contar at� 
	o valor m�ximo de 65535 (0xFFFF) antes de ocorrer um estouro (overflow). 
	
	O valor inicial do Timer � definido pelos registradores TMR1H e TMR1L
	>> O per�odo de cada contagem do Timer 1 usando a f�rmula:
		t = ciclo de m�quina * prescaler * contagem(65535 - TMR1H:TMR1L);
    	ciclo de m�quina = 4 / Fosc; >>> ciclo de m�quina = 0,2us
	   
	    t = 0,2us * 1 * 65536 >>> t = 0,0131s
	    t = 0,2us * 8 * 65535>>> t = 0,104s
*/