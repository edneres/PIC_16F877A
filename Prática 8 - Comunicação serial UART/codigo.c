/*
	Half - Duplex
	
	Lógica:
		A cada um segundo, um contador é incrementado.
		O valor desse contador é informado através do PORTB.
		Esse valor é enviado pela porta serial.
		Se a tecla "p" for pressionada, a contagem é parada.
		Se a tecla "c" for pressionada, a contagem é continuada.
		
		#use232(...)
		kbhit() // lê/recebe
		putc()	// envia >> ASCI
		
		if(kbhit(serial))
		{
			opcao = getc();
			
			if(opcao == 'p')
			{
			
			}
			
			else		// if(opcao == 'c')
			{
			
			}
		}
*/

#include <16F877A.h>
#include "registradores16F.h"
#use delay(clock = 20M)
#use rs232(baud = 9600, xmit = PIN_C6, rcv = PIN_C7, bits = 8, parity = N, stop = 1, stream = serial)

unsigned int8 counter = 0, cont = 8;
boolean counting = TRUE;

void setup()
{
	// PERIFÉRICOS // 
	TRISB = 0b0000000;
	PORTB = 0b0000000; 
	
	// TIMERS //
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);  
    set_timer1(0);  						  
    enable_interrupts(INT_TIMER1);
    enable_interrupts(GLOBAL);
}

#int_timer1
void interrupcao()
{
	set_timer1(0);
	cont++;
	
    if(cont > 10)
    	cont = 0;
   
    if(cont == 10 && counting)
    {
		cont = 0;
      	counter++;
        putc((counter/100) + 48);		// Centena
        putc((counter%100)/10 + 48);	// Dezena
        putc((counter%100)%10 + 48);	// Unidade
        printf("\r\n");					// Quebra de linha 
        
        PORTB = counter;
    }
}

void main()
{	  
	setup();
	
    while(1)
    {
		if(kbhit())  				// Verifica se há caracteres disponíveis na porta serial
        {
        	char input = getc();
         
	        if(input == 'p' || input == 'P')
	        	counting = FALSE;  	// Para a contagem
            
	        else if(input == 'c' || input == 'C')
	            counting = TRUE;  	// Continua a contagem
          
	        putc(input);
	        printf("\r\n");	
      }
   }
}


#ORG 0x1E80, 0x1EFF{}

/*
				CÁLCULOS
				
	t = 0,0000002s*8*65536 = 0,1048
	1/0,1048 = 9,54 ~= 10
*/