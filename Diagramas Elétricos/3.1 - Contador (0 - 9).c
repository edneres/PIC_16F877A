#include <16F877A.h>
#byte PORTD = 0x08
#byte PORTB = 0x06

void setup()
{
	/*
	set_tris_d(0b00000000); // RD0 à RD7 para o display
	set_tris_c(0b00000001); // RC0 para o Botão de Incremento 
	set_tris_b(0b10000000); // RB7 para o Botão de Reset
	port_b_pullups(TRUE);   // Reset ativado em 0
	PORTD = 0b01100110;  // 
	set_timer1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
 	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER1);
	set_timer1(0);
	*/
	
	set_tris_b(0b00000000);
	set_tris_c(0b00000001);
	setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);
	port_b_pullups(TRUE);
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER1);
	set_timer1(0);
}

void display(unsigned int8 num)
{
   // Tabela de segmentos para exibir os dígitos de 0 à 9
   					                  //  Pgfedcba
   unsigned int8 segmentos[10] = {		0b00111111,  // 0
                                        0b00000110,  // 1
                                        0b01011011,  // 2
                                        0b01001111,  // 3
                                        0b01100110,  // 4
                                        0b01101101,  // 5
                                        0b01111101,  // 6
                                        0b00000111,  // 7
                                        0b01111111,  // 8
                                        0b01101111}; // 9
		
	PORTB = segmentos[num];
}

void main()
{
	setup();
	display(0);
	
	unsigned int8 cont = 0;
	
	while(1)
	{
		if (input(PIN_B7) == 0){
			set_timer1(0);
		}
		if (cont >9){
			set_timer1(0);
		}
		
		display(cont);
		cont = get_timer1();
	}
}

#ORG 0x1E80, 0x1EFF{}

// OK NA PRÁTICA E SÓ FUNCIONA COM O PORTB //