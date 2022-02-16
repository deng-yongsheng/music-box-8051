#include<reg51.h>



#define LCD1602_DATA P0
 
unsigned char lcd_busy(void);
void lcd_writecmd(unsigned char cmd);
void lcd_writedata(unsigned char lcddata);
void wait_while_lcd_busy(void);
void lcd_write_str(unsigned char *str,unsigned char row,unsigned char col);
void lcd_init(void);
void delay(int z);
void lcd_clear(void);
	