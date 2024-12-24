

#include "main.h"

void timer2_init(void){
	TCCR2A |=(1<<WGM21);
	TCCR2B |=(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK2 |=(1<<OCIE2A);
	OCR2A = 77;//2*1024*(1+38)/8000000=0.01
}

ISR (TIMER2_COMPA_vect){
	if(cnt1) cnt1--;
	if(cnt2) cnt2--;
	//flagEnc=1;
	//flagKey = 1;
}

//uint8_t e,d,s,ths;
uint16_t a = 0;

int main(void)
{
	timer2_init();
	TM1637_init();
	DDRD |=(1<<LED);
	  TM1637_setSegments(TM1637_0, TM1637_DIGITS_COUNT, 0);
	  TM1637_turnOnAndSetBrightness(1);
	  sei();

    while (1) 
    {
		if(cnt2==0){PORTD ^= (1<<LED);
			flag_dot = !flag_dot;
			cnt2=100;}
		if(cnt1==0){
			a++;
			TM1637_displayNumber(a);
			if(a==9999){a=0;};				
			cnt1=10;
			}

    }
}

