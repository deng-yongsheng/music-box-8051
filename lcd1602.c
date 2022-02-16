#include<reg51.h>
#include<intrins.h>
#include"lcd1602.h"


#define LCD_CMD_CLEAR 0x01
#define LCD_CMD_CURSOR_RETURN 0x02
#define LCD_CMD_DISPLAY_MODE 0x04

sbit LCD1602_RS = P2^0;
sbit LCD1602_RW = P2^1;
sbit LCD1602_E = P2^2;

/*************************************************
Function: delay
Description: 阻塞延时，在12MHz的时钟下，延时一定时间
Input: 
			z:延时时长，单位为毫秒
Output: None
Return: void
*************************************************/
void delay(int z)
{
	int x,y;
	for(x = z;x > 0;x--)
	for(y = 110;y > 0;y--);
}

/*************************************************
Function: lcd_busy
Description: 返回lcd1602的状态，0为空闲，1为忙
Input: None
Output: None
Return: 0为空闲，1为忙
*************************************************/
unsigned char lcd_busy(void)
{
	unsigned char state;
	LCD1602_E = 0;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	LCD1602_E = 1;
	_nop_();
	state = LCD1602_DATA;
	LCD1602_E = 0;
	if(state & 0x80)
		return 1;
	else
		return 0;
}

/*************************************************
Function: lcd_writecmd
Description: 向lcd1602发送指令
Input: cmd :lcd指令
Output: None
Return: void
*************************************************/
void lcd_writecmd(unsigned char cmd)
{
	wait_while_lcd_busy();
	LCD1602_E = 0;
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DATA = cmd;
	LCD1602_E = 1;
	_nop_();
	LCD1602_E = 0;
	delay(1);
}

/*************************************************
Function: lcd_writedata
Description: 向lcd1602发送数据
Input: lcdcmd :要发送的数据
Output: None
Return: void
*************************************************/
void lcd_writedata(unsigned char lcddata)
{
	wait_while_lcd_busy();
	LCD1602_E = 0;
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DATA = lcddata;
	_nop_();
	LCD1602_E = 1;
	_nop_();
	LCD1602_E = 0;
}

/*************************************************
Function: wait_while_lcd_busy
Description: 等待lcd1602转为空闲状态
Input: 	None
Output: None
Return: void
*************************************************/
void wait_while_lcd_busy(void)
{
	while(lcd_busy());
}


/*************************************************
Function: lcd_clear
Description: lcd1602清屏
Input: void
Output: 清除lcd上的所有字符
Return: void
*************************************************/
void lcd_clear(void)
{
	lcd_writecmd(0x01);
}

/*************************************************
Function: lcd_write_str
Description: 在lcd1602的特定位置显示ascii字符串
Input: 
		str:字符串数据
		row:第一行（0）或者第二行（1）
		col:起始列，从0开始
Output: 在lcd1602上显示str对应的字符串
Return: void
*************************************************/
void lcd_write_str(unsigned char *str,unsigned char row,unsigned char col)
{
	if(row)
		lcd_writecmd(col+0x80+0x40);
	else
		lcd_writecmd(col+0x80);
	while(*str != '\0')
	{

		lcd_writedata(*str);
		str++;
	}
}

/*************************************************
Function: lcd_init
Description: lcd初始化
Input: void
Output: None
Return: void
*************************************************/
void lcd_init(void)
{
	lcd_writecmd(0x38);
	lcd_writecmd(0x0c);
	lcd_writecmd(0x06);
	lcd_writecmd(0x01);
}