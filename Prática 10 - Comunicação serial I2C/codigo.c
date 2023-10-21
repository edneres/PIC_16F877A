#include <16F877A.h>
#include "registradores16F.h"
#USE delay(clock = 20M)
#USE I2C (master, sda = PIN_C4, scl = PIN_C3, fast = 100000)

void setup()
{
	set_tris_d(0b00000000);
	enable_interrupts(GLOBAL);
}

unsigned int leitura_bot()
{
	unsigned int estado_bot = 0;
	
	i2c_start();
	i2c_write(0x41);     		// Final 1 para leitura
	estado_bot = i2c_read();
	i2c_stop();
	
	if(estado_bot & 0b10000000)
		estado_bot = 1;
		
	else
		estado_bot = 0;
			
	return estado_bot;
}

void estado_led(unsigned int estado_bot)
{
	if(estado_bot == 1)
	{
		i2c_start();
		i2c_write(0x40);     	// Final 0 para escrita
		i2c_write(0b00000001);		
		i2c_stop();
	}
	
	else
	{
		i2c_start();
		i2c_write(0x40);     	// Final 0 para escrita
		i2c_write(0b00000000);		
		i2c_stop();
	}
}

void main()
{	
	setup();
	
	unsigned int est_bot;
	
	while(1)
	{
		est_bot = leitura_bot();
		estado_led(est_bot);
	}
}

#ORG 0x1E80, 0x1EFF{}