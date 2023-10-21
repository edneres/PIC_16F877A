/*
	LÓGICA:	
		Faça um programa utilizando a interrupção de cada módulo a seguir:
		timer1 >> p/ comutar RD0 a cada 0,5s 
		timer2 >> p/ comutar RD1 a cada 0,25s 	
		Externa (RB0/INT) >> p/ comutar RD2 a cada borda de subida no pino RB0 
							(habilitar interrupção externa - INTF e INTE)
							(soltar botão a interrupção é ativada)
							(botão -> res. pull-up -> capacitor de 120 em paralelo com o botão)
							ext_int_edge( )
							enable_interrupts( )

	OBS: zerar todas as flags, ativar PEIE
	
	while(1)  
	{
		// void
	}
*/

#include <16F877a.h>
#include "registradores16F.h"

unsigned int cont_timer1 = 0;

void setup()
{
	// PERIFÉRICOS //
	set_tris_d(0b00000000);
	set_tris_b(0b00000001);
	port_b_pullups(TRUE);
	
	// TIMERS // 
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
	set_timer1(0);
	// t = 0,2us * 8 * 65535>>> t = 0,104s -> cont = 5
	setup_timer_2(T2_DIV_BY_16, 155, 1);
	set_timer2(155);
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER1);
	enable_interrupts(INT_TIMER2);
	enable_interrupts(INT_EXT_L2H);	
}

#int_timer1
void comutar_RD0()
{
	cont_timer1++;
	set_timer1(0);
	
	if(cont_timer1 == 5) // Se 0,5s...
	{
		cont_timer1 = 0;
		output_toggle(PIN_D1);
	}
}

#int_timer2
void comutar_RD1()
{
	set_timer2(155);
	output_toggle(PIN_D1);
}

#int_ext
void comutar_RD2()
{
	output_toggle(PIN_D2);
}

void main()
{
	setup();
	
	while(1)
	{
	
	}
}

#ORG 0x1E80, 0x1EFF{}