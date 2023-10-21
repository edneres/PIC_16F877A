#include <16F877A.h>

unsigned int cont_timer1 = 0;

void setup()
{
	// PERIFÉRICOS //
	set_tris_d(0b00000000);
	set_tris_b(0b00000001);
	port_b_pullups(TRUE);

	enable_interrupts(GLOBAL);
	enable_interrupts(INT_EXT_L2H);	
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
		sleep();
	}
}

#ORG 0x1E80, 0x1EFF{}