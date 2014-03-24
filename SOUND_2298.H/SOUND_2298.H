#include <avr/io.h>
#include <avr/interrupt.h>


/*************************HEADER FILE FOR PLAYING SOUND IN ATMEGAxx SERIES AT 8 BIT MODE **********************/


/*                               /*.*\ ARJUNUA2298 /*.*\                  */

#define SAMPLE_RATE 8000
volatile uint16_t sample=0;
int sample_count;
int length;
int cycle;
uint8_t sound_data[10];



/******************************DEFINING FUNCTIONS FOR PLAY AUDIO *****************************/


void audio_wav_init(void);
void play_sound( uint8_t,int);

void audio_wav_init(void)
{
	//use OC1A(PD5) pin as output
	DDRD|=(1<<PIND5);

	
	TCCR1A|=((1<<COM1A1)|(1<<WGM10));                   //FAST PWM MODE
	
	TCCR1B|=((1<<WGM12)|(1<<CS10));
	
	//set initial duty cycle to zero
	OCR1A = 0;
	
	TCCR0|=(1<<CS00);
	TCNT0=0;
	TIMSK|=(1<<TOIE0);
	sample_count = 4;
	
}

void play_sound(uint8_t *sound_data,int cycle)
{
	sei();  //enable intrrupt
	for( length=0;sound_data[length]!='\0';length++);
}
ISR(TIMER0_OVF_vect)
{
	
	sample_count--;
	if (sample_count == 0)
	{
		sample_count = 4;
		OCR1A = sound_data[sample++];
		if(sample>length){sample=0;cycle--;if(cycle==0)cli();}
	}
}






