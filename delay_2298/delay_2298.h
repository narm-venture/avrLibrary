#ifndef DELAY_2298
#define DELAY_2298
//time delay may be in us or in ms
// give clock frequency before using the delay function
//range of _delay_us is 0 to 65535 us
//range of _delay_ms is 0 to 4190 ms
//range of _delay_ms is 0 to any value
//valid only for 1 MHZ clock


void _delay_us(unsigned int);
void _delay_ms(unsigned int);
void _delay_s(unsigned int);
#endif