//select refrence voltage mode
//select which adc you want to use
//start conversion
//take result in result_data
  #include <my_utils/delay_2298.h>
  #include <my_utils/adc_2298.h>
void ref_volt_external(void);
void ref_volt_external(void)
{
	ADMUX|=1<<REFS0;
	return;
}
void ref_volt_int_2_56(void);
void ref_volt_int_2_56(void)
{
	ADMUX|=1<<REFS0|1<<REFS1;
	return;
}
void select_adc(unsigned int);
void select_adc(unsigned int adc)
{
	if(adc==0)
	{
		return;
	}
	else if(adc==1)
	{
		ADMUX|=1<<MUX0;
		return;
	}
	else if(adc==2)
	{
		ADMUX|=1<<MUX1;
		return;
	}
	else if(adc==3)
	{
		ADMUX|=1<<MUX1|1<<MUX0;
		return;
	}
	else if (adc==4)
	{
		ADMUX|=1<<MUX2;
		return;
	}
	else if(adc==5)
	{
		ADMUX|=1<<MUX0|1<<MUX2;
		return;
	}
	else if(adc==6)
	{
		ADMUX|=1<<MUX1|1<<MUX2;
		return;
	}
	else if(adc==7)
	{
		ADMUX|=1<<MUX0|1<<MUX1|1<<MUX2;
		return;
	}
}
void start_conversion(void);
void start_conversion(void)
{
	ADCSRA|=1<<ADPS2|1<<ADEN;
	ADCSRA|=1<<ADSC;
    _delay_ms(2);
	return;
}
void result_data_mode(unsigned int);
void result_data_mode(unsigned int BITE)
{
	if(BITE==10)
	{
		ADCSRA|=1<<ADLAR;
		uint16_t result_data=(ADCH<<2)|(6>>ADCL);
		return;
	}
	else
	{
	uint8_t result_data=ADCL;
	return;
	}
}
