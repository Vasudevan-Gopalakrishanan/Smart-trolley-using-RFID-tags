#include<LPC21XX.H>
#include"delay.c"
#include"lcd_cmd.c"
#include"uart0.c"
#include<string.h>
#define SW1 1<<14
#define SW2 1<<15						   +
#define SW3 1<<16


typedef unsigned char U8;
typedef const char CC;

int PEN=0,BOOK=0,PRICE_PEN=0,PRICE_BOOK=0;
int i=0;
char val[100];
int P=0,B=0;

void del_isr(void) __irq
{
	
 	EXTINT=0X01;
	delay_ms(500);
	
  LCD_COMMAND(0x01);
  LCD_COMMAND(0x80);
	LCD_STR("REMOVE PRODUCT..");
	delay_ms(1000);
 	LCD_COMMAND(0x01);
		
	LCD_COMMAND(0X81);
	LCD_STR("PEN");
	LCD_COMMAND(0XC2);
	LCD_INTEGER(PRICE_PEN);

  LCD_COMMAND(0X86);
  LCD_STR("BOOK");
  LCD_COMMAND(0XC6);
  LCD_INTEGER(PRICE_BOOK);
 
	
	  while(i<=9)
		{
		val[i++]=UART0_RX();
		}
		i=0;
		while(i<=9)
		UART0_TX(val[i++]);
		i=0;

		if(strstr(val,"00307572"))
		{
			PEN--;
	    	if(PEN<=0)
			{
			PEN=0;
			PRICE_PEN=0;
			}
			PRICE_PEN=PEN*5;
			LCD_COMMAND(0XC2);
			LCD_INTEGER(PRICE_PEN);
		
		}
		if(strstr(val,"03108458"))
		{
			BOOK--;
			if(BOOK<=0)
			{
			BOOK=0;
			PRICE_BOOK=0;
			}
			PRICE_BOOK=BOOK*10;
			LCD_COMMAND(0XC6);
			LCD_INTEGER(PRICE_BOOK);
		
		}
 	VICVectAddr=0;
}
void total_isr(void) __irq
{
    
 	EXTINT=0X02;
    delay_ms(500);
	LCD_COMMAND(0x01);
	LCD_COMMAND(0X80);
	LCD_STR("TOTAL");
	
	LCD_COMMAND(0XC0);
	LCD_INTEGER(PRICE_PEN+PRICE_BOOK);
	LCD_COMMAND(0x86);
	LCD_STR("QTY");
	LCD_COMMAND(0xC6);
	LCD_INTEGER(PEN+BOOK);
	LCD_COMMAND(0x8A);
	LCD_STR("P");
	LCD_COMMAND(0xCA);
	LCD_INTEGER(P);
	LCD_COMMAND(0x8D);
	LCD_STR("B");
	LCD_COMMAND(0xCD);
	LCD_INTEGER(B);
	delay_ms(5000);

	 
	
	LCD_COMMAND(0x01);
	LCD_COMMAND(0X81);
	LCD_STR("THANK YOU");
	LCD_COMMAND(0XC4);
	LCD_STR("VISIT AGAIN");
	 delay_ms(400);

	LCD_COMMAND(0x01);
	 
	VICVectAddr=0;
}

int main()
{	
	
	LCD_INIT();
	UART0_INIT();
	LCD_COMMAND(0x81);
	LCD_STR(" SMART TROLLEY ");
	LCD_COMMAND(0xc1);
	LCD_STR(" USING RFID ");
	delay_ms(1000);
	
	
    PINSEL0=0xA0000005;
    PINSEL1=0x00000001;
    VICIntSelect=0;
	  VICVectCntl0=(0x20)|14;
	  VICVectAddr0=(int) del_isr; 
	  VICVectCntl1=(0x20)|15;
	  VICVectAddr1=(int) total_isr;
	 
	 EXTMODE=0x00;
	 EXTPOLAR=0X00;
	 
	 VICIntEnable=1<<14|1<<15;
	 
while(1)
{
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80);
	LCD_STR("ADD PRODUCT...");
	delay_ms(500);
	
 	LCD_COMMAND(0x01);
	LCD_COMMAND(0X81);
	LCD_STR("PEN");
	LCD_COMMAND(0XC2);
	LCD_INTEGER(PRICE_PEN);

  LCD_COMMAND(0X86);
  LCD_STR("BOOK");
  LCD_COMMAND(0XC6);
  LCD_INTEGER(PRICE_BOOK);
  
	  while(i<=9)
		{
		val[i++]=UART0_RX();
		}
	
		i=0;
		
		while(i<=9)
		UART0_TX(val[i++]);
		i=0;

		if(strstr(val,"00307572"))
		{
			PEN++;
			P++;
			if(PEN<=0)
			{
			PEN=0;
			PRICE_PEN=0;
			}
			PRICE_PEN=PEN*5;
		
			LCD_COMMAND(0XC2);
			LCD_INTEGER(PRICE_PEN);
		}
		if(strstr(val,"03108458"))
		{
			BOOK++;
			B++;
			if(BOOK<=0)
			{
			BOOK=0;
			PRICE_BOOK=0;
			}
			PRICE_BOOK=BOOK*10;
		
			LCD_COMMAND(0XC6);
			LCD_INTEGER(PRICE_BOOK);
		}
	}

	
}

