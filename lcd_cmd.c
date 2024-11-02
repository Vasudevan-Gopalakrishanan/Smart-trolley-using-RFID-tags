#include<LPC21XX.H>
#include<string.h>


#define LCD_D (0x0f)<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

typedef unsigned char U8;
typedef const char CC;
void LCD_INIT(void);
void LCD_COMMAND(U8);
void LCD_DATA(U8);
void LCD_INTEGER(int );
void LCD_FLOAT(float);
void LCD_STR(U8*);
void LCD_INIT(void)
{
	IODIR1=LCD_D|RS|RW|E;
	IOCLR1=RW;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X28);
	LCD_COMMAND(0X80);
}
void LCD_COMMAND(U8 cmd)
{
	IOCLR1=LCD_D;
	IOSET1=(cmd&0xf0)<<16;
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
	IOCLR1=LCD_D;
  IOSET1=(cmd&0x0f)<<20;
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;	

}
void LCD_DATA(U8 d)
{
	IOCLR1=LCD_D;
	IOSET1=(d&0xf0)<<16;
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
	
	IOCLR1=LCD_D;
  IOSET1=(d&0x0f)<<20;
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}

void LCD_STR(U8*s)
{	   
	while(*s)
	{
		LCD_DATA(*s++);
	}
}

void LCD_INTEGER(int n )
{
	unsigned char arr[20];
	signed char i=0;
	if(n==0)
		LCD_DATA('0');
	else
	{
	if(n<0)
	 {
		 LCD_DATA('-');
		 n=-n;
	 }
	while(n>0)
	{
		arr[i++]=n%10;
		n=n/10;
	}
	for(--i;i>=0;i--)
	LCD_DATA(arr[i]+48);
  }
}
void LCD_FLOAT(float f)
{
	int temp;
	temp=f;
	LCD_INTEGER(temp);
	LCD_DATA('.');
	temp=((f-temp)*100);
	LCD_INTEGER(temp);
}
