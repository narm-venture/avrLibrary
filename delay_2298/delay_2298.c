//time delay may be in us or in ms
// give clock frequency before using the delay function
//range of _delay_us is 0 to 65535 us
//range of _delay_ms is 0 to 4190 ms
//range of _delay_ms is 0 to any value
//valid only for 1 MHZ clock



void _delay_us(unsigned int);
void _delay_ms(unsigned int);
void _delay_s(unsigned int);
void _delay_us(unsigned int delay)
{
	TCCR1B|=1<<CS10;
	TCNT1=0;
	while(!(TCNT1>=delay));
	return;
}
void _delay_ms(unsigned int delay)
{
	TCCR1B|=1<<CS10|1<<CS11;
	TCNT1=0;
	while(!(TCNT1>=((delay*1000)/64)));
	return;
}
void _delay_s(unsigned int delay)
{
	TCCR1B|=1<<CS12|1<<CS10;
	if(delay<67)
	{
		TCNT1=0;
		while(!(TCNT1>=((delay*1000000)/1024)));
		return;
	}
	else
	{
		int volt=delay/67;
		for (int i=0;i<volt;i++)
		{
			TCNT1=0;
			while(!(TCNT1>=((delay*1000000)/1024)));
		}
		delay=delay%67;
		TCNT1=0;
		while(!(TCNT1>=((delay*1000000)/1024)));
		return;
	}
}
