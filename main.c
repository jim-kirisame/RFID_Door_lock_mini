#include "include.h"

sbit BEEP=P1^7;
sbit KEY=P3^3;
sbit LED=P3^5;
INT8U card_sn[4]={ 0 };//Use for save the Card ID.


void delayms(unsigned char n)		//@32.000MHz
{
	unsigned char i, j;

	i = 32;
	j = 29;
	do{
		do {
			while (--j);
		} while (--i);
	} while(--n);
}

void beepTime(int n){
	unsigned char d = 100 / (2*n);
	do {
		BEEP=0;
		delayms(d);
		BEEP=1;
		delayms(d);
	} while(--n);
}

void main(void){
	
	init_rc522();
	while(1){
		if(req_card_sn(card_sn))beepTime(1);
		if(!KEY)ISP_CONTR = 0x60;
	}
}