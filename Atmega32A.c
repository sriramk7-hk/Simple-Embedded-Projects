#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

void command(unsigned char cmd)
{
  PORTC = 0X02;
  PORTD = cmd;
  PORTC = 0X00;
  _delay_ms(15);
}

void lcd_data(unsigned char data)
{
  PORTC = 0X03;
  PORTD = data;
  PORTC = 0X01;
  _delay_ms(15);
}

void lcd_print(char *p)
{
  while (*p)
  {
    lcd_data(*p++);
  }
}

int main(void)
{
  DDRC = 0XFF;
  DDRD = 0XFF;
  command(0X38);
  command(0X0F);
  command(0X01);
  while (1)
  {
    command(0X80);
    lcd_print("First Program");
    _delay_ms(1000);
    command(0XC0);
    lcd_print("Very Happy");
    _delay_ms(1000);
    command(0X01);
    _delay_ms(1000);
  }
}