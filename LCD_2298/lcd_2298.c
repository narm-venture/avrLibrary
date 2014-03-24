


/******************************  HEADER FILE FOR LCD  *********************************/


#include <util/delay.h>

                           /*.*\  ARJUNUA2298  /*.*\ 



/************************  defining all pins for output *******************************/
#define BIT4 1
#define BIT8 2 
#if MODE==BIT4
#define DB4 PORTB0
#define DB5 PORTB1
#define DB6 PORTB2
#define DB7 PORTB3
#define RS PORTB4
#define E PORTB5
#define RW PORTB6
#define data_ddr DDRB
#define data_port PORTB
#define signal_ddr DDRB
#define signal_port PORTB
#define data_ddr_input 0xF0
#define data_port_input 0xF0
#define data_pin PINB


#elif MODE==BIT8
#define DB0 PORTB0
#define DB1 PORTB1
#define DB2 PORTB2
#define DB3 PORTB3
#define DB4 PORTB4
#define DB5 PORTB5
#define DB6 PORTB6
#define DB7 PORTB7
#define RS PORTD0
#define E PORTD1
#define RW PORTD2
#define data_ddr DDRB
#define data_port PORTB
#define signal_ddr DDRD
#define signal_port PORTD
#define data_ddr_input 0x00
#define data_port_input 0x00
#define data_pin PINB

#endif

/********************************LCD COMMAND  ***************************************/


#define clrdsp 0x01                    //clear display
#define home 0x02                      //go to home
#define wshiftcurR 0x06                //move cursur right with putting character
#define wshiftcurL 0x04                //move cursur left with putting character
#define wshiftlcdR 0x05                // moves lcd right with putting character
#define wshiftlcdL 0x07                // moves lcd left with putting character
#define lcdon 0x0C                     // lcd on
#define lcdoff 0x08                    // lcd off
#define curon 0x0E                     //cursur on
#define curoff 0x0C                    //cursur off
#define curblinkon 0x0F                //cursur blink on
#define curblinkoff 0x0E               // cursur blink off
#define shiftcurL 0x10                 //shift cursur left whitout writing anything
#define shiftcurR 0x14                 // shift cursur right whitout writing anything
#define shiftlcdL 0x18                 //shift lcd left whitout writing anything
#define shiftlcdR 0x1C                 //shift lcd right whitout writing anything
#define s8bitmode 0x30                 // initiate 8 bit mode in single line
#define s4bitmode 0x20                 //initiate 4bit mode in single line
#define d8bitmode 0x38                 //initiate  bit mode in double line
#define d4bitmode 0x28                 //initiate 4 bit mode in double line
#define DDRAM_START_L1 0x80
#define DDRAM_START_L2 0xC0
#define DDRAM_START_L3 0x94
#define DDRAM_START_L4 0xD4
#define CGRAM_START 0x40


/*************************  DEFINING FUNCTION FOR LCD OPERATION ***************************/



void rolltext(char*,int,int);
void putcmd(unsigned char);
void putchar(unsigned char);
void putstr(char*);
void busy();
void enable();
void LCD_init();
void gotoxy(int x,int y);



/*******************************writing functions***************************************/


void enable()            // Enable the signal for lcd to read
{
	signal_port|=(1<<E);
	_delay_us(1);
	signal_port&=~(1<<E);
	_delay_us(100);
}    
void busy()
{
	
		signal_port|=(1<<RW);
		signal_port&=~(1<<RS);
		data_ddr&=data_ddr_input;
		data_port&=data_port_input;
		enable();
		while(!((data_pin>=0x80)|(data_pin>=0x40)));
		data_ddr=255;
		return ;
	
}
void LCD_init()            //initiate the lcd
{
	
	if(MODE==BIT4)
	{
	
		DDRB|=0x3F;
		PORTB&=0xC0;
		putcmd(lcdon);
		putcmd(d4bitmode);
		putcmd(curblinkon);
		putcmd(clrdsp);
		putcmd(wshiftcurR);
		_delay_ms(1000);
	}
	else if(MODE==BIT8)
	{
		
	
		DDRB|=0xFF;
		PORTB=0;
		DDRD|=0x03;
		PORTD&=0xFC;
		putcmd(lcdon);
		putcmd(d8bitmode);
		putcmd(curblinkon);
		putcmd(clrdsp);
		putcmd(wshiftcurR);
		_delay_ms(1000);
		
	}
	
	
}
void putchar(unsigned char character_data)     //puts character to lcd
{
	if(MODE==BIT4)
	{
		
	busy();
	data_port|=((character_data&0xf0)>>4);
	signal_port|=(1<<RS);
	signal_port&=~(1<<RW);
	enable();
	data_port|=(character_data&0x0f);
	signal_port|=(1<<RS);
	signal_port&=~(1<<RW);
	enable();
	
	data_port=0x00;
	
	}
	
	else if(MODE==BIT8)
	{
		busy();
		data_port=character_data;
		signal_port|=1<<RS;
		signal_port&=~(1<<RW);
		enable();
		data_port=0;
	}
}

void putcmd(unsigned char cmdm)           // puts command to lcd
{
	if(MODE==BIT4)
	{
		
	busy();
	data_port|=((cmdm&0xf0)>>4);
	signal_port&=~((1<<RS)|(1<<RW));

	enable();
	data_port|=(cmdm&0x0f);
	signal_port&=~((1<<RS));
	enable();
	data_port=0x00;
	
	}
	
	else if(MODE==BIT8)
	{
		busy();
		data_port=cmdm;
		signal_port&=~((1<<RS)|(1<<RW));
		enable();
		data_port=0;
	}
}
void putstr(char *cbs)                  //writing any string to lcd
{
	int i;
	for(i=0;cbs[i]!='\0';i++)
	putchar(cbs[i]);
}
void gotoxy(int x,int y)         // go to any position on lcd
{
	if(y==1)
	{
		putcmd(DDRAM_START_L1+(x-1));
		
	}
	else if (y==2)
	{
		putcmd(DDRAM_START_L2+(x-1));
	}
	else if(y==3)
	{
		putcmd(DDRAM_START_L3+(x-1));
	}
	else if(y==4)
	{
		putcmd(DDRAM_START_L4+(x-1));
	}
	
	
	
}
void rolltext(char *a,int time_delay,int line)     //roll up the text
{
	char temp,kopo=a[25];
	int gh;
	for (gh=0;a[gh]!='\0';gh++);
	a[25]='\0';
	if(gh>30)
	{
		for(int totot=0;totot<(time_delay*3);totot++)
		{
			_delay_ms(300);
			gotoxy(1,(line));
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
		for(int totot=0;totot<(3*time_delay);totot++)
		{
			_delay_ms(300);
			gotoxy(1,(line));
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






