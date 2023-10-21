/*
	CCP1 >> Modo Captura, para medir o tempo de nível alto de um sinal	(TIMER1 em borda de subida)
					Alta precisão e pouca interferência da CPU			
	CCP2 >> Modo PWM, cuja frequência será 10KHz (T = 0,1ms = 100us)	(TIMER2)
	
	D = (tempo em nível alto) / (Período de 100us) = x% 
	
	LÓGICA: 
		Se (tempo em nível alto) > 50us, LED acende.
		Se não, apaga.
		
		LED >> RD2
		RC1 >> Saída
		RC2 >> Entrada 
*/

/*
#include <16F877A.h>
#bit CCP1IF = 0x0C.0

void setup()
{
	// MODOS E TIMERS //
	setup_ccp1(CCP_CAPTURE_RE);	// CCP1 começa capturando a borda de subida
	setup_ccp2(CCP_PWM);		// CCP2 no modo PWM
	set_pwm2_duty(75);
}

void main()
{
   setup();
   CCP1IF = 0;
   unsigned int16 primeira_captura = 1, ti, periodo;
   
   while(1)
   {
	   if(CCP1IF == 1)	// Faz a medição do período
	   {
		   CCP1IF = 0;
		   
		   if(primeira_captura == 1)
		   {
			   ti = CCP_1;
			   primeira_captura = 0;
		   }
		   
		   else
		   {
			   periodo = CCP_1 - ti;
			   primeira_captura = 1;
		   }
	   }		   
		
	   if(periodo > 5000)	// Tratando o dado medido (período)
	   		output_high(pin_d2);	
				   
	   else
			output_low(pin_d2);
   }
}
*/

#include <16F877A.h>
#bit CCP1IF = 0x0C.0
//#bit LED = 0x08.2

unsigned int16 t0, duty_cycle = 100; 

void setup()
{
	// PERIFÉRICOS //
	set_tris_c(0b00000100);	// RC1 como saída e RC2 como entrada
	set_tris_d(0b00000000);	// RD2 como saída (LED)
	output_low(PIN_D2);
	
	// MODOS E TIMERS //
	setup_ccp1(CCP_CAPTURE_RE);	// CCP1 começa capturando a borda de subida
	setup_ccp2(CCP_PWM);		// CCP2 no modo PWM
	
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
	setup_timer_2(T2_DIV_BY_4, 124, 10);
	set_pwm2_duty(duty_cycle);
}

void main()
{
   setup();
   
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