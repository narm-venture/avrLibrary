/*
 * EEPROM_2298.cpp
 *
 * Created: 3/15/2014 6:07:16 PM
 *  Author: ARJUN PANSARI
 */ 

void write_EEPROM(unsigned int,unsigned char);
unsigned char read_EEPROM(unsigned int);

void write_EEPROM(unsigned int address,unsigned char data)
{
	while(EECR&(1<<EEWE));
	EEAR=address;
	EEDR=data;
	EECR|=1<<EEMWE;
	EECR|=1<<EEWE;
}
unsigned char read_EEPROM(unsigned int address)
{
	while(EECR&(1<<EEWE));
	EEAR=address;
	EECR|1<<EERE;
	return EEDR;
}
