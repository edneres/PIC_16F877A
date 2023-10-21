/*
	Piscar LED a cada 100ms usando timer0
				23/05/23
*/

#include <16F877A.h>
#include "registradores16F.h"

#define LED PIN_D1	// ok
int cont = 0;

void setup()
{
	// TIMER0 //
	setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256 | RTCC_8_BIT);	// Cristal  interno, prescaler de 256
	//set_timer0(0);								// TMR0 come�a em 0
	TMR0 = 0;
	enable_interrupts(INT_TIMER0); 					// Habilita a interrup��o do TIMER0
	enable_interrupts(GLOBAL);						// Habilita as interrup��es globais
	
	// PERIF�RICOS //
	set_tris_d(0b00000000);
	output_high(LED);
}

/////////////////////////////////////////
// Rotina para a interrup��o do TIMER0 //
/////////////////////////////////////////
#int_timer0
void interrupcao() 
{
	TMR0 = 0;
	cont++;
	
	if(cont == 8)
	{
		cont = 0;
		
		output_toggle(LED);
	}
}

void main()
{
	setup();	
	
	while(1)
	{
		
	}
}

#ORG 0x1E80, 0x1EFF{}

// C�DIGO OK NA PR�TICA //

/*
				C�LCULOS
				
	>> Ciclo de M�quina (CM) = 0,2us
	>> t = CM * Prescaler * (256 - TMR0)
	   > t = 0,0000002s * 256 * 256 = 0,0131s
	   > 0,1/0,0131 ~= 7,63
	   
	>> Logo: para um tempo de 100ms s�o necess�rios
	8 estouros do TIMER0.
*/