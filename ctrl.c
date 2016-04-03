#include "include.h"

data unsigned char CardRevBuf[16] = { 0 };

unsigned char req_card_sn( unsigned char card_sn[] )
{
	if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节	
	{
		if( PcdRequest( PICC_REQIDL, &CardRevBuf[0] ) != MI_OK )//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节	
		{
			return FALSE;
		}	
	}
	
	if( PcdAnticoll( &CardRevBuf[2] ) != MI_OK ) //防冲撞，返回卡的序列号 4字节 
	{
		return FALSE;	
	}
	memcpy( &card_sn[0], &CardRevBuf[2], 4 );

	return TRUE;
}
