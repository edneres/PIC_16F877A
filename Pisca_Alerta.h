void config_timer0()
{
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
	enable_interrupts(INT_TIMER0);
}

int estouro = 0;

#int_timer0
void Pisca_Alerta()
{	
	estouro++;
	
	if(estouro == 8)
	{
		output_toggle(PIN_D1);
		set_timer0(0);
		estouro = 0;
	}
}