#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#ifndef LCD_PORT
#define LCD_PORT PORTA
#endif

#ifndef LCD_RS
#define LCD_RS 2
#endif

#ifndef LCD_E
#define LCD_E 3
#endif

void lcd_init(void);
void lcd_write4(uint8_t data);
void lcd_write_instr(uint8_t data);
void lcd_clear(void);
void lcd_write_data(uint8_t data);
void lcd_set_xy(uint8_t r, uint8_t k);
void lcd_write_text_xy(uint8_t r, uint8_t k, char* text);

#endif
