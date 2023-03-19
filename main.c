#include <regx52.h>
#include <string.h>
#include <rtx51tny.h>

sbit LCD_RS = P2^0;
sbit LCD_EN = P2^1;
sbit LED_NAME1  = P1^0;
sbit LED_NAME2 = P3^0;
sbit LED_NAME3 = P3^1;

#define LCD_DATA P0	 // Khai b�o ch�n dta

void Delay_ms(unsigned int ms) //H�m delay
{
	while(ms--){
		TMOD = 0x01;
		TH0 = 0xfc;
		TL0 = 0x18;
		TR0 = 1;
		while(!TF0);
		TF0 = 0;
		TR0 = 0;
	}
}

void Lcd_cmd(unsigned char cmd)	  //H�m g?i l?nh ra LCD

{ 

  
   LCD_RS =0;// Ch?n ch? d? ghi l?nh
   LCD_DATA =cmd;// cmd l� l?nh c?n g?i ra m�n h�nh
   LCD_EN = 0; 						  
   LCD_EN =1;
   if(cmd<=0x02){
   Delay_ms(2);
   }
   else{
   Delay_ms(1);}

}
void Lcd_Char_Cp(char c)//H�m hi?n th? 1 k� t? t?i v? tr� con tr?
{
   
   LCD_RS =1; //Ch?n ch? d? g?i d? li?u
   LCD_DATA =c;	 //K� t? c?n g?i ra m�n h�nh
   LCD_EN = 0;
   LCD_EN =1;
   Delay_ms(1);

}
void Lcd_Out_Cp(char *str)// H�m g?i chu?i k� t? t?i v? tr� con tr?

{

unsigned char i=0;
while(str[i]!=0)  //G?i t?ng k� t? c?a chu?i d?n khi g?p k� t? null
{
	 Lcd_Char_Cp(str[i]);
	 //Delay_ms(50);
	 i++;
}

}


void Lcd_xy(unsigned char row, unsigned char col)		//H�m Di chuy?n v? tr� con tr? d?n v? tr� b?t k� v� in chu?i ra m�n h�nh
{
 	unsigned char cmd;

	// Di chuy?n con tr? d?n v? tr� c?n thi?t
	cmd = (row==1?0x80:0xC0) + col - 1;
	Lcd_cmd(cmd);

}


void Lcd_Init() //H�m kh?i t?o LCD
{

 Lcd_cmd(0x30);
 Delay_ms(5);
 Lcd_cmd(0x30);
 Delay_ms(1);
 Lcd_cmd(0x30);
 Lcd_cmd(0x38);	  // S? d�ng hi?n th? l� 2, c? ch? 5x8
 Lcd_cmd(0x01);	  // x�a m�n h�nh
 Lcd_cmd(0x0C);	  //B?t hi?n th? v� t?t con tr? c�c b?n c� th? d�ng l?nh 0xE0 d? b?t hi?n th? v� b?t con tr?



}

void Led_Effect1(){
		char i;
		LED_NAME1 = 0; LED_NAME2 = 0; LED_NAME3 = 0;
		Delay_ms(100);
		LED_NAME1 = 1;
		Delay_ms(150);
		LED_NAME2 = 1; 
		Delay_ms(150);
		LED_NAME3 = 1;
		Delay_ms(150);
		LED_NAME1 = 0; LED_NAME2 = 0; //LED_NAME3 = 0;
		Delay_ms(100);
		LED_NAME3 = 1;
		Delay_ms(150);
		LED_NAME2 = 1; 
		Delay_ms(150);
		LED_NAME1 = 1;
		Delay_ms(300);
		LED_NAME1 = 0; LED_NAME2 = 0; LED_NAME3 = 0;
		for( i = 0; i<5; i++){
			LED_NAME1 = !LED_NAME1; 
			LED_NAME2 = !LED_NAME2; 
			LED_NAME3 = !LED_NAME3;
			Delay_ms(200);
		}
		LED_NAME1 = 0; LED_NAME2 = 0; LED_NAME3 = 0;
		Delay_ms(300);
}

void LCD_Shift_Left(char *str, int n){
		int i;
	for(i=0; i<n;i++){
		int j, firstchar;
		firstchar = str[0];   // the first character
		for (j = 0; j < strlen(str) - 1; j++){
			str[j] = str[j+1];
		}
		str[strlen(str)-1] = firstchar;
	}
}
void LCD_Shift_Right(char *str, int n){
		int i;
	for(i=0; i<n;i++){
		int j, lastchar;
		lastchar = str[strlen(str) - 1];   // the last character
		for (j = strlen(str)-1; j > 0; j--){
			str[j] = str[j-1];
		}
		str[0] = lastchar;
	}
}
void display() _task_ 1
	{
		unsigned char line1[] = "NGUYEN TRONG KHOI   ";
    unsigned char line2[] = "DIEM 10             ";
		Lcd_Init();
	
//Lcd_Out(1,1,"DT030223 - DT3B - 2019-2024     ")	; 
//Lcd_Out(2,1,"NGUYEN TRONG KHOI");
while(1)
{
	Lcd_cmd(0x01); //clear screen
	Lcd_xy(1,1);
	Lcd_Out_Cp(line1);
	Lcd_xy(2,1);
	Lcd_Out_Cp(line2);
	LCD_Shift_Right(line2,1);
	LCD_Shift_Left(line1,1);
	Delay_ms(150);
}
}
	
void Led_Effect2(){
	LED_NAME1 = 1; 
	LED_NAME2 = 0; 
	LED_NAME3 = 0;
	Delay_ms(100);
	LED_NAME1 = 0; 
	LED_NAME2 = 1; 
	LED_NAME3 = 0;
	Delay_ms(100);
	LED_NAME1 = 0; 
	LED_NAME2 = 0; 
	LED_NAME3 = 1;
	Delay_ms(100);
	
	
}

void Led_effect() _task_ 2
{
	while(1){
	Led_Effect2();
	}

}

void setup_task() _task_ 0
{
    os_create_task(1);
    os_create_task(2);
    os_delete_task(0);
}
