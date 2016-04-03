#include "include.h"

sbit BEEP = P1^7;
sbit KEY = P3^3;
sbit LED = P3^5;
sbit LOCK = P1^0;
unsigned char card_sn[4] = { 0 };//卡号数据暂存

int n; //卡号数据
int addMode=FALSE;  //添加模式


//延时N毫秒
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

//响N声
void beepTime(int n){
	unsigned char d = 100 / (2*n);
	do {
		BEEP=0;
		delayms(d);
		BEEP=1;
		delayms(d);
	} while(--n);
}

//控制继电器开关
void openDoor(void){
	LOCK=0;
	delayms(100);
	LOCK=1;
}

//认证
int auth(){
	int i,j;
	
	n=IapReadByte(0x0000); //获取数据库已有的卡数目
	
	for (j=0;j<=n;j++){
		for (i=0;i<4;i++){
			if(card_sn[i] != IapReadByte((j*0x0200)+i)) //读取数据
				break;
			else if(i == 3) return 1;
		}
	}
	return 0;
}

//添加卡
void addKey(){
	int i;
	
	n=IapReadByte(0x0000);				//获取数据库已有的卡数目
	
	IapEraseSector((n+1)*0x0200);	//清空第N+1块
	for (i=0;i<4;i++){
			IapProgramByte((n+1)*0x0200+i,card_sn[i]);  //写入数据
	}
	
	IapEraseSector(0x0000);       //清空数目块
	IapProgramByte(0x0000,++n);   //写入新的数目
	addMode=FALSE;
	beepTime(2);
}

void main(void){
	
	init_rc522();
	
	while(1){
		if(req_card_sn(card_sn)){
			if( auth() ){ 		//判断卡是否在数据库中
				if(!addMode){		//通常模式
					beepTime(1);	//响一声
					openDoor();		//开门
				} else {        //卡已经在数据库中
					beepTime(3); 	//响三声
					addMode=FALSE;//退出
				}
			} else {
				if(!addMode)
					beepTime(2);  //卡号错误
				else addKey();  //添加卡
			}
		}
		if(!KEY){
			addMode=TRUE;
			BEEP=0;
		}
	}
}