#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "gpio.h"

#define KEY1	PB5
#define KEY2	PB4
#define KEY3	PB3
#define KEY4	PD2

void KeyboardInit(void);
uint8_t KeyChange(void);
uint8_t Key1(void);
uint8_t Key2(void);
uint8_t Key3(void);
uint8_t Key4(void);

#endif//__KEYBOARD_H__
