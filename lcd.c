#include "pwm.h"
#include "lcd.h"
#include "delay.h"


void LcdInit(void)
{
	LcdGpioInit();
	LcdReset();

	//PLL
	LcdCmdWrite(0x88, 0x1f);
	LcdCmdWrite(0x89, 0x04);
	USleep(100);

	//Soft Reset
	LcdCmdWrite(0x01, 0x01);
	LcdCmdWrite(0x01, 0x80);

	//System set
	LcdCmdWrite(0x10, 0x08);//system config parallel data output 65K
	USleep(100);

	LcdCmdWrite(0x21, 0x10);//lay set, scan dot, enxternal cgrom, bigs
	USleep(100);

	LcdCmdWrite(0x04, 0x01);
	LcdCmdWrite(0x11, 0x00);//data bus of parallel panel 000=RGB

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

	//BackLight=BL, Reset=RST, Ready=RDY, Interrupt=INT
	//GpioInit(LCD_BL, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_BL, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_RST, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	GpioInit(LCD_RDY, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	GpioInit(LCD_INT, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);

	//
	//LcdBackLight(100);
	GpioOn(LCD_BL);
}

void LcdBackLight(int level)
{
	Pwm(PWM34, level);
}
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
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x8E);
	tmp |= 0x80;
	LcdCmdWrite(0x8E, tmp);
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
	LcdDisplayModeSet(TextMode);
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
	LcdCmdWrite(0x90, (1<<7)|(1<<6)|(0<<0));
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
	LcdCmdWrite(0x90, (1<<7)|(1<<6)|(1<<5)|(0<<0));
	LcdCheckBusy();
}
void LcdMemCursor(uint16_t x, uint16_t y)
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
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x8E);
	tmp |= 0xc0;
	LcdCmdWrite(0x8E, tmp);
	LcdCheckBusy();
}
void LcdLayerSet(uint8_t layer)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x41);
	if(layer)
	{
		tmp |= 0x01;
	}
	else
	{
		tmp &= 0xfe;
	}
	LcdCmdWrite(0x41, tmp);
}
void LcdDisplayModeSet(uint8_t mode)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x40);
	if( mode )
	{
		tmp |= 0x80;
	}
	else
	{
		tmp &= 0x7f;
	}
	LcdCmdWrite(0x40, tmp);
}
void LcdColor4K(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x10) & 0xf3;
	tmp |= 0x04;
	LcdCmdWrite(0x10, tmp);
	tmp = LcdCmdRead(0x20);
	tmp |= 0x80;
	LcdCmdWrite(0x20, tmp);
}
void LcdColor65K(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x10) & 0xf3;
	tmp |= 0x08;
	LcdCmdWrite(0x10, tmp);
	tmp = LcdCmdRead(0x20);
}
void LcdFontZoomSet(uint8_t size)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x22) & 0xf0;
	switch( size )
	{
		case 1:
			tmp |= 0x00;
			break;
		case 2:
			tmp |= 0x05;
			break;
		case 3:
			tmp |= 0x0A;
			break;
		case 4:
			tmp |= 0x0F;
			break;
	}
	LcdCmdWrite(0x22, tmp);
}
void LcdFontBoldfacedSet(uint8_t bold)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x22) & 0xdf;

	if(bold == 0x00)
	{
		tmp |= 0x00;
	}
	else if(bold == 0x01)
	{
		tmp |= 0x20;
	}
	LcdCmdWrite(0x22, tmp);
}
void LcdFontTransparency(uint8_t cmd)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x22) & 0xbf;

	if(cmd == 0x00)
	{
		tmp |= 0x00;
	}
	else if(cmd == 0x01)
	{
		tmp |= 0x10;
	}
	LcdCmdWrite(0x22, tmp);
}
void LcdFontRotateZero(void)
{
	uint8_t tmp = 0;
	tmp = LcdCmdRead(0x22) & 0xef;
	LcdCmdWrite(0x22, tmp);
}
void LcdFontRotateNinety(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x22) & 0xef;
	tmp |= 0x10;
	LcdCmdWrite(0x22, tmp);
}

void LcdCursorSet(uint16_t x, uint16_t y)
{
	LcdCmdWrite(0x46, x);
	LcdCmdWrite(0x47, x >> 8);
	LcdCmdWrite(0x48, y);
	LcdCmdWrite(0x49, y >> 8);
}
void LcdSegNormalScan(void)
{
	uint8_t tmp = 0;
	tmp = LcdCmdRead(0x20) & 0xf7;
	LcdCmdWrite(0x20, tmp);
}
void LcdSegReverseScan(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x20) & 0xf7;
	tmp |= 0x08;
	LcdCmdWrite(0x20, tmp);
}
void LcdConNormalScan(void)
{
	uint8_t tmp = 0;
	tmp = LcdCmdRead(0x20) & 0xf7;
	LcdCmdWrite(0x20, tmp);
}
void LcdComReverseScan(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x20) & 0xf7;
	tmp |= 0x08;
	LcdCmdWrite(0x20, tmp);
}
void LcdScrollOffsetSet(uint16_t x, uint16_t y)
{
	uint8_t tmp = 0;

	tmp = x;
	LcdCmdWrite(0x24, tmp);
	tmp = x >> 8;
	LcdCmdWrite(0x25, tmp);
	tmp = y;
	LcdCmdWrite(0x26, tmp);
	tmp = y >> 8;
	LcdCmdWrite(0x27, tmp);
}
void LcdScrollLayerSet(uint8_t layer)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0x3f;
	if(layer == 0x00)
		tmp |= 0x40;
	else if(layer == 0x01)
		tmp |= 0x80;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollLayer1Display(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollLayer2Display(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	tmp |= 0x01;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollOverLayerDisplay(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	tmp |= 0x02;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollTransparentDisplay(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	tmp |= 0x03;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollBoolOrDisplay(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	tmp |= 0x04;
	LcdCmdWrite(0x52, tmp);
}
void LcdScrollBoolAndDisplay(void)
{
	uint8_t tmp = 0;

	tmp = LcdCmdRead(0x52) & 0xf8;
	tmp |= 0x05;
	LcdCmdWrite(0x52, tmp);
}
void LcdTouchInit(void)
{
	LcdCmdWrite(0x70, 0xb4);//adc clk div4, adc 4096clk, enable touch
	LcdCmdWrite(0x71, 0x85);//touch 4line, Vref internal, external int
	LcdCmdWrite(0x8F, 0x40);//touch int enable
}
uint8_t LcdTouchDataRead(uint16_t* x, uint16_t* y)
{
	uint8_t xh = 0;
	uint8_t val = 0;
	uint8_t yh = 0;
	uint8_t xl = 0;
	uint8_t yl = 0;
	uint16_t tmp = 0;

	if((LcdCmdRead(0x8F) & 0x04) == 0)
	{
		return 0;
	}
	xh = LcdCmdRead(0x72);
	yh = LcdCmdRead(0x73);
	val = LcdCmdRead(0x74);
	xl = val & 0x03;
	yl = val & 0x0c;
	yl >>= 2;
	tmp = xh;
	tmp <<= 8;
	*x = tmp | xl;
	tmp = 0;
	tmp = yh;
	tmp <<= 8;
	*y = tmp | yl;
	LcdCmdWrite(0x8F, 0x44);

	return 1;
}

void LcdFillColor(uint16_t x, uint16_t y, uint16_t size, uint16_t color)
{
	LcdDisplayModeSet(DrawMode);
	LcdCursorSet(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; i < size; i++)
	{
		LcdMemWrite(color);
		LcdMemWrite(color >> 8);
	}
	LcdMemWriteEnd();
}
