#ifndef  __main_h__
#define  __main_h__

typedef	unsigned char	BOOLEAN;
typedef	unsigned char	INT8U;
typedef	signed char		INT8S;
typedef	unsigned int	INT16U;
typedef	signed int		INT16S;
typedef	unsigned long  	INT32U;
typedef	signed long    	INT32S;

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

#define	FALSE	0
#define	TRUE	1

#define	WR		0
#define	RD		1

#define nop() _nop_()

#define	BIT(n)	( 1 << n )

#define PASSWORD_MASK 1

#define	LED_NONE	0
#define	LED_LONG	1
#define	LED_200MS	2
#define	LED_80MS	3

//enum
//{
//	LED_NONE  = 0,
//	LED_LONG  = 1,
//	LED_200MS = 2,
//	LED_80MS  = 3,
//};

extern void delay_ms( INT16U tms );

#endif
