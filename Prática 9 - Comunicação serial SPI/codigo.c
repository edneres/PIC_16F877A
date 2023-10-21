#include <16f877a.h>
#bit TMR1IF = 0x0C.0

unsigned int8 cont = 0, cont1 = 0;

#INT_SSP
void leitura_completa()
{
	output_high(PIN_C2);
	
	for(int i=0; i < 250;i++);
	
	output_low(PIN_C2);
}

void main()
{
	ENABLE_INTERRUPTS(GLOBAL);
	ENABLE_INTERRUPTS(INT_SSP);
	
	set_tris_c(0x00);
	setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_CLK_DIV_64);
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
	set_timer1(0);
	output_low(PIN_C2);
	
	
	while(1)
	{
		if (TMR1IF == 1)
		{
			cont1++;
			TMR1IF = 0;
			set_timer1(0);
		}
		
		if (cont1 == 10)
		{
			cont++;
			cont1 = 0;
		}
		
		SPI_WRITE(cont);
	}
}

#ORG 0x1E80, 0x1EFF{}