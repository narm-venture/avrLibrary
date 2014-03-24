/******************************  HEADER FILE FOR LCD  *********************************/




/***  FOR LCD FIRST LINE STARTS WITH 80 AND SECOND LINE STARTS FROM C0 > FIRST LINE +THIRDLINE,SECOND LINE+FORTH LINE   */
#include <avr/io.h>
#include <avr/delay.h>

/************************  defining all pins for output *******************************/

#define DB4 PORTB0
#define DB5 PORTB1
#define DB6 PORTB2
#define DB7 PORTB3
#define RS PORTB4
#define E PORTB5

/********************************LCD COMMAND  ***************************************/


#define clrdsp 0x01 //clear display
#define home 0x02 //go to home
#define wshiftcurR 0x06 //move cursur right with putting character
#define wshiftcurL 0x04 //move cursur left with putting character
#define wshiftlcdR 0x05 // moves lcd right with putting character
#define wshiftlcdL 0x07 // moves lcd left with putting character
#define lcdon 0x0C // lcd on
#define lcdoff 0x08 // lcd off
#define curon 0x0E //cursur on
#define curoff 0x0C //cursur off
#define curblinkon 0x0F //cursur blink on
#define curblinkoff 0x0E // cursur blink off
#define shiftcurL 0x10 //shift cursur left whitout writing anything
#define shiftcurR 0x14 // shift cursur right whitout writing anything
#define shiftlcdL 0x18 //shift lcd left whitout writing anything
#define shiftlcdR 0x1C //shift lcd right whitout writing anything
#define s8bitmode 0x30 // initiate 8 bit mode in single line
#define s4bitmode 0x20 //initiate 4bit mode in single line
#define d8bitmode 0x38 //initiate  bit mode in double line
#define d4bitmode 0x28 //initiate 4 bit mode in double line
#define cc PORTB
#define signal PORTB

/*************************  DEFINING FUNCTION FOR LCD OPERATION ***************************/



void rolltext(char*,int,int);
void putcmd(unsigned char);
void putchar(unsigned char);
void putstr(char*);
void busy();
void enable();
void init();
void go(int x,int y);
void enable()
{
	signal|=(1<<E);
	_delay_us(1500);
	signal&=~(1<<E);
}
void busy()
{
	_delay_us(500);
}
void init()
{
	DDRB=0xFF;
	PORTB=0x00;
	putcmd(lcdon);
	putcmd(d4bitmode);
	putcmd(curblinkon);
	putcmd(clrdsp);
	putcmd(wshiftcurR);
	_delay_ms(1000);
}
void putchar(unsigned char a)
{
	busy();
	cc=((a&0xf0)>>4);
	signal|=(1<<RS);
	enable();
	cc=(a&0x0f);
	signal|=(1<<RS);
	enable();
	
	cc=0x00;
}
void putcmd(unsigned char b)
{
	busy();
	cc=((b&0xf0)>>4);
	signal&=~((1<<RS));
	enable();
	cc=(b&0x0f);
	signal&=~((1<<RS));
	enable();
	cc=0x00;
}
void putstr(char *c)
{
	int i;
	for(i=0;c[i]!='\0';i++)
	putchar(c[i]);
}
void go(int x,int y)
{
	putcmd(home);
	
	putcmd(0x80+x+40*y);
	
}
void rolltext(char *a,int time_delay,int line)
{
	char temp,kopo=a[25];
	int gh,lok;
	for (gh=0;a[gh]!='\0';gh++);
	a[25]='\0';
	if(gh>30)
	{
		for(int totot=0;totot<(time_delay*2);totot++)
		{
			_delay_ms(300);
			go(0,(line-1));
			putstr(a);
			a[25]=kopo;
			
			temp=a[0];
			for (gh=0;a[gh+1]!='\0';gh++)
			{
				a[gh]=a[gh+1];
			}
			a[gh]=temp;
			kopo=a[25];
			
			a[25]='\0';
			
		}
	}
	else
	{
		for(int totot=0;totot<(2*time_delay);totot++)
		{
			_delay_ms(300);
			go(0,(line-1));
			putstr(a);
			temp=a[0];
			for (gh=0;a[gh+1]!='\0';gh++)
			{
				a[gh]=a[gh+1];
			}
			a[gh]=temp;
			
		}
	}
}






