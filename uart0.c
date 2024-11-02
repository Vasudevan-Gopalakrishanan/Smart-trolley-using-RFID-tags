#include<LPC21XX.H>
typedef unsigned char U8;
void UART0_INIT(void);
void UART0_TX(U8);
U8 UART0_RX(void);
// int main()
// {
// 	U8 p[50],i=0;
// 	UART0_INIT();
// 		//UART0_TX('s');
// 	
// 	while(1)
// 	{
// 	  while(i<=9)
// 		{
// 		p[i]=UART0_RX();
// 			i++;
// 		}
// 		i=0;
// 		while(i<=9)
// 		UART0_TX(p[i++]);
// 		i=0;

// 	}
// 	}
void UART0_INIT(void)
{
	PINSEL0=0X05;
	U0LCR=0X83;
	U0DLL=97;
	U0LCR=0X03;
}
void UART0_TX(U8 c)
{
  while((U0LSR>>5&1)==0);
       U0THR=c;
}
U8 UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
