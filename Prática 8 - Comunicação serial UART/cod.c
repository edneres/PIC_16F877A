#include <16F877A.h>
#include "registradores16F.h"
#include "Pisca_Alerta.h"

#bit LED = PORTD.2

unsigned int16 t0, duty_cycle = 300;

void setup()
{
	// PERIFÉRICOS //
	TRISC = 0b00000100;	// RC1 como saída e RC2 como entrada
	//TRISD = 0b00000000;	// RD2 como saída (LED)
	//PORTD = 0x00;		// LED começa desligado
	
	// MODOS E TIMERS //
	setup_ccp1(CCP_CAPTURE_RE);	// CCP1 começa capturando a borda de subida
	setup_ccp2(CCP_PWM);		// CCP2 no modo PWM
	
	config_timer0();
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
	setup_timer_2(T2_DIV_BY_4, 124, 10);
	set_pwm2_duty(duty_cycle);
}

void main()
{
   setup();
   Pisca_Alerta();
   
   while(1)
   {
	   if(CCP1IF == 1)
	   {
		   CCP1IF = 0;
		   
		   if(input(PIN_C2) == 1)
		   {
			   setup_ccp1(CCP_CAPTURE_FE);
			   t0 = CCP_1;
		   }
		   
		   else
		   {
			   CCP_1 = CCP_1 - t0;
			   
			   if(CCP_1 >= 250)
				   output_high(PIN_D2);
				   
			   else
			   	   output_low(PIN_D2);
			   	   
			   setup_ccp1(CCP_CAPTURE_RE);
		   }
	   }
   }
}