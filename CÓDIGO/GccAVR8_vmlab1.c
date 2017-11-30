/*
 * Created: 12/26/2015 3:59:15 PM
 *  Author: Juan Manuel Mendoza Jacinto
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void configura_com(void)
{	
	UBRR0H = (unsigned char)(12>>8);
	UBRR0L = (unsigned char) 12;
	//Velocidad doble
	UCSR0A = 1<<U2X0;
	//Comunicación Asíncrona, sin paridad, 1 bit de parada, 8 bits de datos
	UCSR0C = (0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	// Tx y Rx habilitadas
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02);

}


void w4exit(void)
{
int cent=0;
int dato=0;	
while(cent==0)
{
 if(((UCSR0A&(1<<RXC0))==0x80))
 {
	 dato = UDR0;
	 if(dato==10)////////////////////////////////////0A
	 {cent=1;
	 }
 } 
}
cent=0;
}

int w4success(void){	
	int cent=0;
	int cent3=0;
	int dato=0;
	int e=0;
	
	while(cent==0)
	{
		if((UCSR0A&(1<<RXC0))==0x80)
		{
			dato = UDR0;
			if(dato==70)
			{
				while((cent3==0)&&(e==0))
				{	if((UCSR0A&(1<<RXC0))==0x80){
					dato = UDR0;
					if(dato==97){cent3=1;}else{e=1;}
					}
				}
						
			if(cent3==1){cent=1;return 0;}
			cent3=0;
			e=0;
			}
			
			if(dato==99)
			{
				while((cent3==0)&&(e==0))
				{	if((UCSR0A&(1<<RXC0))==0x80){
					dato = UDR0;
					if(dato==99){cent3=1;}else{e=1;}
					}
				}
			
			if(cent3==1){cent=1;return 1;}
			cent3=0;
			e=0;
			}
		}}}

void configura_puertos(void)
{
	DDRC |= 0x0F; //SALIDA PARA LOS LEDS
	DDRB |= 0x00; //ENTRADA DE LOS SWITCHES
	_delay_ms(1000); //ESPERA 1S
	//charge();
	//w4exit();
}

int main(void)
{
	configura_com();
	configura_puertos();
	int cent2=0;
	int dato = 0;
	int counter=0;
	int val=0;
	int aux=0;
	int minu=0;
	int clock=0;
	PORTC |=0x07;
	//while(1==(PINB&0x01))
	//while(0==(PINB&0x01))
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 170;	//AA
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 4;//04
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 48;//30
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 64;//40
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 65;//41
	while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
	UDR0 = 10;//0A
	w4exit();
	PORTC&=~0x07;
	while(1)
	{
		while(cent2==0)
		{
			if(((UCSR0A&(1<<RXC0))==0x80))
			{
				dato = UDR0;
				if(dato==64)
				{
					switch(counter)
					{	case 0:
						PORTC |=0x01;
						counter++;
						w4exit();
						clock=1; //activado el reloj
						break;
						case 1:
						PORTC |=0x02;
						counter++;
						w4exit();
						break;
						case 2:
						PORTC |=0x04;
						counter++;
						w4exit();
						break;
						case 3:
						w4exit();
						break;
					}
				}
				
				if(dato==65)
				{
					switch(counter)
					{	case 0:
						w4exit();
						break;
						case 1:
						PORTC &=~0x01;
						counter--;
						w4exit();
						break;
						case 2:
						PORTC &=~0x02;
						counter--;
						w4exit();
						break;
						case 3:
						PORTC &=~0x04;
						counter--;
						w4exit();
						break;
					}
				}
			}
			while(0==(PINB&0x01)){cent2=1;}
			
			 if(clock==1){
				 val++;
				 if(val==32000){val=0;aux++;}//cuarto sec
				 if(aux==212){aux=0;minu++;}
				 if(minu==1){minu=0;PORTC&=~0x07;counter=0;clock=0;}
			 }
			
		}
		
		cent2=0;
		PORTC&=~0x07;
		_delay_ms(3000);
		PORTC |=0x05;
		_delay_ms(3000);
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 170;
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 3;
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 32;
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 64;
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 10;
		if(1==w4success())
		{	w4exit();
			PORTC&=~0x07;
			_delay_ms(3000);
			PORTC |=0x05;
			_delay_ms(3000);
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
			UDR0 = 170;
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
			UDR0 = 3;
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
			UDR0 = 32;
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
			UDR0 = 65;
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
			UDR0 = 10;
				if(1==w4success())
				{
					w4exit();
					PORTC&=~0x07;
					_delay_ms(3000);
					PORTC |=0x05;
					_delay_ms(3000);
										
				}
		}
		PORTC&=~0x07;
		counter=0;
		_delay_ms(2000);
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 170;	//AA
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 4;//04
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 48;//30
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 64;//40
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 65;//41
		while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		UDR0 = 10;//0A
		w4exit();
		cent2=0;	
	}
	/*
	while(1)
	{
		if((UCSR0A&(1<<RXC0))==0x80)
		{
			dato = UDR0;
			while((UCSR0A&(1<<UDRE0))==0);//mientras no reciba//
		//if(dato==10){dato=42;}
		UDR0 = dato;}
	}*/
	
		
	}