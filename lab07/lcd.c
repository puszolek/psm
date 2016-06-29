#include "lcd.h"

void lcd_init(void){
	_delay_ms(100);
	lcd_write4(0b00110000);
	_delay_ms(10);
	lcd_write4(0b00110000);
	_delay_ms(1);
	lcd_write4(0b00110000);
	lcd_write4(0b00100000);

	lcd_write_instr(0b00101000);
	lcd_write_instr(0b00001000);
	lcd_clear();
	lcd_write_instr(0b00001100);
}

void lcd_write4(uint8_t data){
	LCD_PORT |= (1<<LCD_E);
	LCD_PORT &= 0x0F;
	LCD_PORT |= data & 0xF0;
	LCD_PORT &= ~(1<<LCD_E);
	_delay_us(100);
}

void lcd_write_instr(uint8_t data){
	LCD_PORT &= ~(1<<LCD_RS);
	lcd_write4(data & 0xF0);
	lcd_write4(data << 4);
}

void lcd_clear(void){
	lcd_write_instr(1);
	_delay_ms(5);
}

void lcd_write_data(uint8_t data){
	LCD_PORT |= (1<<LCD_RS);
	lcd_write4(data & 0xF0);
	lcd_write4(data << 4);
}

void lcd_set_xy(uint8_t r, uint8_t k){
	uint8_t addr = 0x40*r + k;
	lcd_write_instr((1<<7)|addr);
}

void lcd_write_text_xy(uint8_t r, uint8_t k, char* text){
	lcd_set_xy(r,k);
	while(*text)
		lcd_write_data(*text++);
}
