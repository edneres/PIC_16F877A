#include <16F877a.h>
#use delay(clock = 20000000)

#define LED PIN_D1

void main()
{
	set_tris_d(0b00000000);		// Configura todos os pinos do PORTD como saída
	
	while(1)
	{
		output_toggle(LED);
		delay_ms(500);
	}	
}

#ORG 0x1E80, 0x1EFF{} // Reservar (DEU CERTO) (7808 - 7934) ~= (7808 - 8191)

// CÓDIGO OK NA PRÁTICA //