#include "include.h"

sbit BEEP=P1^7;
sbit KEY=P3^3;
sbit LED=P3^5;
sbit LOCK=P1^0;
INT8U card_sn[4]={ 0 };//Use for save the Card ID.
unsigned char card_sn_pre[]={0x12,0x34,0x56,0x78};

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

void openDoor(void){
	LOCK=0;
	delayms(100);
	LOCK=1;
}

int auth(){
	int i;
	for (i=0;i<4;i++){
		if(card_sn[i] != card_sn_pre[i])
			return FALSE;
	}
	return TRUE;
}

void main(void){
	
	init_rc522();
	while(1){
		if(req_card_sn(card_sn)){
			if(auth()){
				beepTime(1);
				openDoor();
			} else {
				beepTime(2);
			}
		}
		if(!KEY)ISP_CONTR = 0x60;
	}
}