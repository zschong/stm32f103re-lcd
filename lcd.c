#include "pwm.h"
#include "lcd.h"
#include "delay.h"


void LcdInit(void)
{
	LcdGpioInit();
	LcdReset();

	//PLL
	LcdCmdWrite(0x88, 0x1F);
	LcdCmdWrite(0x89, 0x04);
	USleep(100);

	//Soft Reset
	LcdCmdWrite(0x01, 0x01);
	LcdCmdWrite(0x01, 0x80);

	//System set
	LcdCmdWrite(0x10, 0x00);//system config parallel data output 65K
	USleep(100);

	LcdCmdWrite(0x04, 0x01);
	//LcdCmdWrite(0x11, 0x00);//data bus of parallel panel 000=RGB

	//horizontal setting
	LcdCmdWrite(0x14, 0x27);//horizontal display width(pixel)=(HDWR+1)*8
	LcdCmdWrite(0x15, 0x86);
	LcdCmdWrite(0x16, 0x03);//horizontal non-display period(pixel)=(HNDR+1)*8
	LcdCmdWrite(0x17, 0x02);//hsync start position(PLCK)=(HSTR+1)*8

	//vertical setting
	LcdCmdWrite(0x19, 0xef);//vertical pixel=VHDR0+1
	LcdCmdWrite(0x1A, 0x00);//vertical pixel=VHDR1+1
	LcdCmdWrite(0x1B, 0x0e);//vertical non-display area=(VNDR0+1)
	LcdCmdWrite(0x1C, 0x00);//vertical non-display area=(VHDR1+1)
	LcdCmdWrite(0x1D, 0x03);//start position(PCLK)=(VSTR0+1)
	LcdCmdWrite(0x1E, 0x00);//start position(PCLK)=VSTR1+1
	LcdCmdWrite(0x1F, 0x82);//pulse width(PCLK)=VPWR+1

	LcdColor65K();
	LcdWindowClear();
	LcdWindowActive(0, 0, 319, 239);
	LcdTouchInit();
}
void LcdReset(void)
{
	GpioOff(LCD_RST);
	MSleep(50);
	GpioOn(LCD_RST);
	MSleep(50);
}
void LcdGpioInit(void)
{
	//DB[7-0]
	GpioInit(LCD_DB7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB6, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB5, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB4, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB3, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_DB0, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	
	//RS, CS, WR, RD
	GpioInit(LCD_RS, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_CS, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_WR, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_RD, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

	//Reset=RST, Ready=RDY, Interrupt=INT
	GpioInit(LCD_RST, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_RDY, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(LCD_INT, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	//Backlight=BL
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	GpioInit(LCD_BL, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	LcdBackLight(50);
}

void LcdBackLight(int level)
{
	Pwm(PWM34, level%101);
}
/*-------------------binary access----------------------*/
uint8_t LcdStatus(void)
{
	uint8_t data = 0;

	LcdDataBusInput();
	RS_CS_WR_RD(1, 0, 1, 0);
	data =LcdDataBusRead();
	RS_RD_CS_WR(1, 1, 1, 1);
	LcdDataBusOutput();

	return data;
}
uint8_t LcdDataRead(void)
{
	uint8_t data = 0;

	LcdDataBusInput();
	RS_CS_WR_RD(0, 0, 1, 0);
	data =LcdDataBusRead();
	RS_RD_CS_WR(0, 1, 1, 1);
	LcdDataBusOutput();

	return data;
}
uint8_t LcdMemRead(void)
{
	uint8_t data = 0;

	GPIOC->ODR &= ~(0xffff&LCD_RD);
	data = (GPIOA->ODR & 0x00ff);
	GPIOC->ODR |=  (0xffff&LCD_RD);

	return data;
}
uint8_t LcdCmdRead(uint8_t cmd)
{
	LcdRegWrite(cmd);
	return LcdDataRead();
}
void LcdCmdWrite(uint8_t cmd, uint8_t value)
{
	LcdRegWrite(cmd);
	LcdDataWrite(value);
}
void LcdCheckBusy(void)
{
	while( LcdStatus() & 0x80 );
}
void LcdMemClear(void)
{
	uint8_t tmp = LcdCmdRead(0x8E);
	LcdCmdWrite(0x8E, tmp | 0x80);
	LcdCheckBusy();
}
/*------------------- text function -------------------------*/
void LcdLayer(int layer)
{
	uint8_t tmp = LcdCmdRead(0x20);

	switch(layer)
	{
	case 1:
		LcdCmdWrite(0x20, tmp & 0x7F);
		break;
	case 2:
		LcdCmdWrite(0x20, tmp | 0x80);
		break;
	}
}
void LcdText(uint16_t x, uint16_t y, char *text, int len)
{
	LcdWindowActive(0, 0, 319, 239);
	LcdDisplayMode(TextMode);
	LcdTextBackGroundEnable(0);
	LcdTextCursor(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; text && i < len; i++)
	{
		LcdMemWrite(text[i]);
		USleep(100);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextColor(uint16_t x, uint16_t y, uint16_t color, char *text, int len)
{
	LcdWindowActive(0, 0, 319, 239);
	LcdDisplayMode(TextMode);
	LcdTextBackGroundEnable(0);
	LcdTextForgeGroundColor(color);
	LcdTextCursor(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; text && i < len; i++)
	{
		LcdMemWrite(text[i]);
		USleep(100);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextColorZoom(
uint16_t x, uint16_t y, uint16_t color, uint8_t zoom, char *text, int len)
{
	LcdTextZoom(zoom);
	LcdTextForgeGroundColor(color);
	LcdWindowActive(0, 0, 319, 239);
	LcdDisplayMode(TextMode);
	LcdTextBackGroundEnable(0);
	LcdTextCursor(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; text && i < len; i++)
	{
		LcdMemWrite(text[i]);
		USleep(100);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextForgeGroundColor(uint16_t color)
{
	LcdCmdWrite(0x63, 0x1F & (color>>11));
	LcdCmdWrite(0x64, 0x3F & (color>>5));
	LcdCmdWrite(0x65, 0x1F & (color>>0));
}
void LcdTextBackGroundColor(uint16_t color)
{
	LcdCmdWrite(0x60, 0x1F & (color>>11));
	LcdCmdWrite(0x61, 0x3F & (color>>5));
	LcdCmdWrite(0x62, 0x1F & (color>>0));
}
void LcdTextAlignEnable(int enable)
{
	uint8_t tmp = LcdCmdRead(0x22);
	if( enable )
	{
		LcdCmdWrite(0x22, tmp & ~(1 << 7));
	}
	else
	{
		LcdCmdWrite(0x22, tmp | (1 << 7));
	}
}
void LcdTextBackGroundEnable(int enable)
{
	uint8_t tmp = LcdCmdRead(0x22);
	if( enable )
	{
		LcdCmdWrite(0x22, tmp & ~(1<<6));
	}
	else
	{
		LcdCmdWrite(0x22, tmp | (1<<6));
	}
}
void LcdTextRotate(int degree)
{
	uint8_t tmp = LcdCmdRead(0x23);
	switch(degree)
	{
	case 0:
		LcdCmdWrite(0x22, tmp & ~(1<<4));
		break;
	case 90:
		LcdCmdWrite(0x22, tmp | (1<<4));
		break;
	}
}
void LcdTextZoom(int size)
{
	LcdTextZoomHorizontal(size);
	LcdTextZoomVertical(size);
}
void LcdTextZoomHorizontal(int size)
{
	uint8_t tmp = LcdCmdRead(0x22) & ~(3<<2);
	switch(size)
	{
	case 1:
		LcdCmdWrite(0x22, tmp | (0<<2));
		break;
	case 2:
		LcdCmdWrite(0x22, tmp | (1<<2));
		break;
	case 3:
		LcdCmdWrite(0x22, tmp | (2<<2));
		break;
	case 4:
		LcdCmdWrite(0x22, tmp | (3<<2));
		break;
	}
}
void LcdTextZoomVertical(int size)
{
	uint8_t tmp = LcdCmdRead(0x22) & ~(3<<0);
	switch(size)
	{
	case 1:
		LcdCmdWrite(0x22, tmp | (0<<0));
		break;
	case 2:
		LcdCmdWrite(0x22, tmp | (1<<0));
		break;
	case 3:
		LcdCmdWrite(0x22, tmp | (2<<0));
		break;
	case 4:
		LcdCmdWrite(0x22, tmp | (3<<0));
		break;
	}
}
void LcdTextCursor(uint16_t x, uint16_t y)
{
	LcdCmdWrite(0x2A, x);
	LcdCmdWrite(0x2B, x>>8);
	LcdCmdWrite(0x2C, y);
	LcdCmdWrite(0x2D, y>>8);
}
/*-----------------------draw function----------------------------*/
void LcdDrawRetangle(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb, uint16_t c)
{
	LcdCmdWrite(0x91, x);
	LcdCmdWrite(0x92, x>>8);
	LcdCmdWrite(0x93, y);
	LcdCmdWrite(0x94, y>>8);
	LcdCmdWrite(0x95, xb);
	LcdCmdWrite(0x96, xb>>8);
	LcdCmdWrite(0x97, yb);
	LcdCmdWrite(0x98, yb>>8);
	LcdTextForgeGroundColor(c);
	LcdCmdWrite(0x90, (1<<7)|(1<<4)|(0<<0));
	LcdCheckBusy();
}
void LcdDrawRetangleFill(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb, uint16_t c)
{
	LcdCmdWrite(0x91, x);
	LcdCmdWrite(0x92, x>>8);
	LcdCmdWrite(0x93, y);
	LcdCmdWrite(0x94, y>>8);
	LcdCmdWrite(0x95, xb);
	LcdCmdWrite(0x96, xb>>8);
	LcdCmdWrite(0x97, yb);
	LcdCmdWrite(0x98, yb>>8);
	LcdTextForgeGroundColor(c);
	LcdCmdWrite(0x90, (1<<7)|(1<<5)|(1<<4)|(0<<0));
	LcdCheckBusy();
}
void LcdDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
	LcdCmdWrite(0x99, x);
	LcdCmdWrite(0x9A, x>>8);
	LcdCmdWrite(0x9B, y);
	LcdCmdWrite(0x9C, y>>8);
	LcdCmdWrite(0x9D, radius);
	LcdTextForgeGroundColor(color);
	LcdCmdWrite(0x90, (0<<7)|(1<<6));
	LcdCmdWrite(0xA0, (1<<7)|(1<<0)|(0<<5));
	LcdCheckBusy();
}
void LcdDrawCircleFill(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
	LcdCmdWrite(0x99, x);
	LcdCmdWrite(0x9A, x>>8);
	LcdCmdWrite(0x9B, y);
	LcdCmdWrite(0x9C, y>>8);
	LcdCmdWrite(0x9D, radius);
	LcdTextForgeGroundColor(color);
	LcdCmdWrite(0x90, (0<<7)|(1<<6)|(1<<5));
	LcdCmdWrite(0xA0, (1<<7)|(1<<6)|(0<<5));
	LcdCheckBusy();
}
/*-----------------window function-----------------------*/
void LcdWindowCursor(uint16_t x, uint16_t y)
{
	LcdCmdWrite(0x46, x);
	LcdCmdWrite(0x47, x>>8);
	LcdCmdWrite(0x48, y);
	LcdCmdWrite(0x49, y>>8);
}
void LcdWindowActive(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb)
{
	LcdCmdWrite(0x30, x);
	LcdCmdWrite(0x31, x>>8);
	LcdCmdWrite(0x32, y);
	LcdCmdWrite(0x33, y>>8);
	LcdCmdWrite(0x34, xb);
	LcdCmdWrite(0x35, xb>>8);
	LcdCmdWrite(0x36, yb);
	LcdCmdWrite(0x37, yb>>8);
}
void LcdWindowClear(void)
{
	LcdMemClear();
}
/*------------------------misc function--------------------*/
void LcdDisplayMode(uint8_t mode)
{
	if( mode )
	{
		LcdCmdWrite(0x40, LcdCmdRead(0x40) | (1<<7));
	}
	else
	{
		LcdCmdWrite(0x40, LcdCmdRead(0x40) & ~(1<<7));
	}
}
void LcdColor256(void)
{
	LcdCmdWrite(0x20, LcdCmdRead(0x10) & ~(3<<2));
}
void LcdColor65K(void)
{
	LcdCmdWrite(0x10, LcdCmdRead(0x10) | (3<<2));
}
/*------------------------touch screen function------------------*/
void LcdTouchInit(void)
{
	LcdCmdWrite(0x70, (1<<7)|(3<<4)|(1<<3)|(1<<2));//0xB4:Enable, clk=4096, 16clk
	LcdCmdWrite(0x71, (0<<6)|(1<<1));
}
uint8_t LcdTouch(uint16_t *xp, uint16_t *yp)
{
	if( (LcdCmdRead(0xF1) & (1<<2)) == 0 )
	{
		return 0;
	}
	uint16_t x = LcdCmdRead(0x72);
	uint16_t y = LcdCmdRead(0x73);
	uint16_t z = LcdCmdRead(0x74);
	LcdCmdWrite(0xF1, (1<<2));
	x <<= 2;
	x |= 3 & (z >> 0);

	y <<= 2;
	y |= 3 & (z >> 2);

	*xp = x;
	*yp = y;

	return 1;
}
