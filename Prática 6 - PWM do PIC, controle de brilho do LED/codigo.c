/*
	CCP1 >> Modo Captura, para medir o tempo de n�vel alto de um sinal	(TIMER1 em borda de subida)
					Alta precis�o e pouca interfer�ncia da CPU			
	CCP2 >> Modo PWM, cuja frequ�ncia ser� 10KHz (T = 0,1ms = 100us)	(TIMER2)
	
	D = (tempo em n�vel alto) / (Per�odo de 100us) = x% 
	
	L�GICA: 
		Se (tempo em n�vel alto) > 50us, LED acende.
		Se n�o, apaga.
		
		LED >> RD2
		RC1 >> Sa�da
		RC2 >> Entrada 
*/

#include <16F877A.h>
#bit CCP1IF = 0x0C.0

#bit LED = PORTD.2

unsigned int16 t0, duty_cycle = 100;

void setup()
{
	// PERIF�RICOS //
	TRISC = 0b00000100;	// RC1 como sa�da e RC2 como entrada
	//TRISD = 0b00000000;	// RD2 como sa�da (LED)
	//PORTD = 0x00;		// LED come�a desligado
	
	// MODOS E TIMERS //
	setup_ccp1(CCP_CAPTURE_RE);	// CCP1 come�a capturando a borda de subida
	setup_ccp2(CCP_PWM_MODE);		// CCP2 no modo PWM
	
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

/*
			C�LCULOS
				
	>> Timer1
		t = 0,2us * 1 * (65536 - TMR1)
		50us = 0,2us * 1 * (65536 - TMR1)
		TMR1 = 65286 -> EXATO!
		
		# A cada 50us acontece ou um evento de subida
		ou um evento de descida de borda do Timer1.
		
	----------------------------------------------------
	
	>> Timer2
		t = ciclo de m�quina * prescaler * potscaler * PR2
			> Postscale: n�mero de 1 � 16 que determina quantos 
			estouros do timer deve haver antes de uma interrup��o.
			> PR2: registro de 8 bits de leitura e escrita.
			TMR2 incrementa de 00h at� que seu valor seja igua a
			PR2, depois reinicia a 00h.
			> F = 10KHz -> P = 0,0001 = 0,1ms = 100us
			> D = (tempo em n�vel alto) / (Per�odo de 100us)
			> Duty Cycle(%) = (CCPRxL / (Per�odo do PWM)) * 100


	  TIMER2 � um temporizador de 8 bits com um divisor( prescaler ) e um postscaler. 
	Ele pode ser usado como a base de tempo de PWM para o modo de PWM do m�dulo CCP. 
	O registo TMR2 � leg�vel e grav�vel, e � eliminada em qualquer redefini��o do dispositivo.
	
	  O rel�gio de entrada (FOSC / 4) tem uma op��o de pr�-escala de 1:1, 1:4, ou 1:16, 
	selecionados por bits de controle T2CKPS1: T2CKPS0 (T2CON.01 : 00).
	
	O m�dulo Timer2 tem um registo de 8 bits: PR2. TMR2 incrementos de 00h at� que seu valor 
	seja igua a PR2, depois reinicia a 00h. PR2 � um registo de leitura e escrita.
	
	  A cada n compara��es, ser� gerada uma interru��o. n � definido pelo Potscaler(1:1 - 1:16). 
	Quer dizer que se Potscaler for igual a 1:4, depois de 4 compara��es (TMR2=PR2) ser� gerada uma interrup��o.
*/