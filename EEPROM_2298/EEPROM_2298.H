#ifndef _EEPROM_2298_H
#define _EEPROM_2298_H

#include <avr/io.h>
void write_EEPROM(unsigned int,unsigned char);
unsigned char read_EEPROM(unsigned int);
#endif