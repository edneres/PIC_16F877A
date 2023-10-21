/*
	Se o botão não estiver pressionado, LED pisca a cada 100ms.
	Se o botão estiver pressionado, o LED fica apagado.
*/

#include <16F877A.h>
#include "registradores16F.h"

#define botao PIN_B0
#define LED	  PIN_D2

int cont = 0;

void setup()
{
	// Botão //
	TRISB = 0b00000001;
	PORTB = 0b00000001;		// Botão inicia desativado
	port_b_pullups(TRUE); 	// Botão ativado em nível lógico 0
	
	// LED //
	TRISD = 0b00000000;
	PORTD = 0b00000000;
	
	// Timer0 //
	setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256); // Oscilador interno: modo temporizador
	set_timer0(0);
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER0);

	/*
	OPTION_REG = 0b000000111;	// ... Prescaler de 256
	GIE		   = 1;				// Habilita Interrupção Global
	PEIE	   = 1;				// Habilita Interrupção dos Periféricos
	TMR0IE	   = 1;				// Habilita Interrupção do Timer0	
	TMR0       = 0;		
	*/
}

#int_timer0
void interrupcao()
{
	//TMR0IF = 0;
	cont++;
	set_timer0(0);
			
	if(cont == 8) // 8 ~= 7,69
	{
		cont = 0;
		
		if(input(botao) == 0)
			output_low(LED);
					
		else
			output_toggle(LED);
	}
	
	if(input(botao) == 0)
			output_low(LED);	
}

void main()
{
	setup();	
	
	while(1)
	{
			
	}
}

#ORG 0x1E80, 0x1EFF{} // Reservar

// CÓDIGO OK NA PRÁTICA //

/*
				CÁLCULOS
				
	>> Ciclo de Máquina = 0,2us (não vai mudar ao londo da matéria)
	>> t = 0,2*10^-6 * prescaler * (prescaler - TMR0)
	   > t = 0,2*10^-6 * 256 * (256 - 0) ~= 0,013
	   > 0,1/0,013 ~= 7,69
	   
	>> Logo: cont == 8 
*/