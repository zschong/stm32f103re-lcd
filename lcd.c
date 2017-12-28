#include <string.h>
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
	msleep(1);

	//Soft Reset
	LcdCmdWrite(0x01, 0x01);
	LcdCmdWrite(0x01, 0x80);

	//System set
	LcdCmdWrite(0x10, 0x00);//system config parallel data output 65K
	msleep(1);

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

	LcdLayer(1);
	LcdColor65K();
	LcdWindowClear();
	LcdWindowActive(0, 0, 319, 239);
}
void LcdReset(void)
{
	GpioOff(LCD_RST);
	msleep(1);
	GpioOn(LCD_RST);
	msleep(1);
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
void LcdWriteBuffer(u16 x, u16 y, char *buf, int len)
{
	LcdDisplayMode(ImageMode);
	LcdWindowCursor(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; buf && i < len; i++)
	{
		LcdMemWrite(buf[i]);
		msleep(1);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
/*------------------- layer function -------------------------*/
void LcdLayer(int layer)
{
	LcdCheckBusy();
	uint8_t tmp = LcdCmdRead(0x41) & 0xF0;
	switch(layer)
	{
	case 1:
		LcdCmdWrite(0x20, LcdCmdRead(0x20) | 0x80);
		LcdCmdWrite(0x41, tmp | (0 << 2) | (0 << 0));
		break;
	case 2:
		LcdCmdWrite(0x20, LcdCmdRead(0x20) | 0x80);
		LcdCmdWrite(0x41, tmp | (0 << 2) | (1 << 0));
		break;
	}
}
void LcdLayerMode(LayerMode mode)
{
	switch( mode )
	{
	case Layer1:
	case Layer2:
	case LayerGradual:
	case LayerTranparent:
	case LayerOR:
	case LayerAND:
	case LayerFloating:
	case LayerFloatingBGTR:
		LcdCmdWrite(0x52, (LcdCmdRead(0x52)&0x0F)|mode);
		break;
	}
}
void LcdTransparency(Layer1Transparency t1, Layer2Transparency t2)
{
	switch(t1)
	{
		case Layer1_8of8:
		case Layer1_7of8:
		case Layer1_6of8:
		case Layer1_5of8:
		case Layer1_4of8:
		case Layer1_3of8:
		case Layer1_2of8:
		case Layer1_1of8:
		case Layer1_0of8:
			break;
		default:
			return;
	}
	switch(t2)
	{
		case Layer2_8of8:
		case Layer2_7of8:
		case Layer2_6of8:
		case Layer2_5of8:
		case Layer2_4of8:
		case Layer2_3of8:
		case Layer2_2of8:
		case Layer2_1of8:
		case Layer2_0of8:
			LcdCmdWrite(0x53, t1|t2);
	}
}
void LcdFloatWindow(u16 x, u16 y, u16 w, u16 h, u16 X, u16 Y)
{
	LcdCmdWrite(0xD0, x);
	LcdCmdWrite(0xD1, x>>8);
	LcdCmdWrite(0xD2, y);
	LcdCmdWrite(0xD3, y>>8);
	LcdCmdWrite(0xD4, w);
	LcdCmdWrite(0xD5, w>>8);
	LcdCmdWrite(0xD6, h);
	LcdCmdWrite(0xD7, h>>8);
	LcdCmdWrite(0xD8, X);
	LcdCmdWrite(0xD9, X>>8);
	LcdCmdWrite(0xDA, Y);
	LcdCmdWrite(0xDB, Y>>8);
}
void LcdFloatWindowColor(u16 x, u16 y, u16 w, u16 h, u16 X, u16 Y, u16 color)
{
	LcdFloatWindow(x, y, w, h, X, Y);
	LcdCmdWrite(0x67, 0x1F & (color >> 11));
	LcdCmdWrite(0x68, 0x3F & (color >> 5));
	LcdCmdWrite(0x69, 0x1F & (color >> 0));
	LcdCheckBusy();
}
/*------------------- text function -------------------------*/
void LcdText(u16 x, u16 y, char *text, int len)
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
		msleep(1);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextColor(u16 x, u16 y, u16 color, char *text, int len)
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
		msleep(1);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextColorZoom(u16 x, u16 y, u16 color, u8 zoom, char *text, int len)
{
	LcdTextZoom(zoom);
	LcdTextForgeGroundColor(color);
	//LcdWindowActive(0, 0, 319, 239);
	LcdDisplayMode(TextMode);
	LcdTextBackGroundEnable(0);
	LcdTextCursor(x, y);
	LcdRegWrite(0x02);
	LcdMemWriteStart();
	for(int i = 0; text && i < len; i++)
	{
		LcdMemWrite(text[i]);
		msleep(1);
	}
	LcdMemWriteEnd();
	LcdCheckBusy();
}
void LcdTextForgeGroundColor(u16 color)
{
	LcdCmdWrite(0x63, 0x1F & (color>>11));
	LcdCmdWrite(0x64, 0x3F & (color>>5));
	LcdCmdWrite(0x65, 0x1F & (color>>0));
}
void LcdTextBackGroundColor(u16 color)
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
void LcdTextCursor(u16 x, u16 y)
{
	LcdCmdWrite(0x2A, x);
	LcdCmdWrite(0x2B, x>>8);
	LcdCmdWrite(0x2C, y);
	LcdCmdWrite(0x2D, y>>8);
}
/*-----------------------draw function----------------------------*/
void LcdDrawLine(u16 x, u16 y, u16 xb, u16 yb, u16 c)
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
	LcdCmdWrite(0x90, (1<<7)|(0<<4)|(0<<0));
	LcdCheckBusy();
}
void LcdDrawRetangle(u16 x, u16 y, u16 xb, u16 yb, u16 c)
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
void LcdDrawRetangleFill(u16 x, u16 y, u16 xb, u16 yb, u16 c)
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
void LcdDrawCircle(u16 x, u16 y, u16 radius, u16 color)
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
void LcdDrawCircleFill(u16 x, u16 y, u16 radius, u16 color)
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
void LcdWindowCursor(u16 x, u16 y)
{
	LcdCmdWrite(0x46, x);
	LcdCmdWrite(0x47, x>>8);
	LcdCmdWrite(0x48, y);
	LcdCmdWrite(0x49, y>>8);
}
void LcdWindowActive(u16 x, u16 y, u16 xb, u16 yb)
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
	switch(mode)
	{
	case ImageMode:
		LcdCmdWrite(0x40, LcdCmdRead(0x40) & ~(1<<7));
		break;
	case TextMode:
		LcdCmdWrite(0x40, LcdCmdRead(0x40) | (1<<7));
		break;
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
	LcdCmdWrite(0x71, (0<<6)|(1<<2)|(1<<1));
}
bool LcdTouchXY(u16 *xp, u16 *yp)
{
	if( (LcdCmdRead(0xF1) & (1<<2)) == 0 )
	{
		return false;
	}
	u16 x = LcdCmdRead(0x72);
	u16 y = LcdCmdRead(0x73);
	u16 z = LcdCmdRead(0x74);
	LcdCmdWrite(0xF1, (1<<2));
	x <<= 2;
	x |= 3 & (z >> 0);

	y <<= 2;
	y |= 3 & (z >> 2);

	*xp = LCD_X - ((x * LCD_X / 999)) % LCD_X;
	*yp = LCD_Y - ((y * LCD_Y / 999)) % LCD_Y;

	return true;
}
bool LcdTouch(u16 *xx, u16 *yy)
{
	u16 x = 0;
	u16 y = 0;
	static struct{
		u16 x;
		u16 y;
		uint32_t time;
	}p = {0, 0, 0};

	if( LcdTouchXY(&x, &y) )
	{
		int t = Msecond() - p.time;

		if( t > 30 )
		{
			p.x = x;
			p.y = y;
			p.time = Msecond();
		}
		int a = x - p.x;
		int b = y - p.y;
		int l = a*a + b*b;
		if( l > 3 && t < l )
		{
			p.x = x;
			p.y = y;
			p.time = Msecond();
			return false;
		}
		*xx = p.x = x;
		*yy = p.y = y;
		p.time = Msecond();
		return true;
	}
	return false;
}
void LcdLinePrintf(int ln, const char *fmt,...)
{
	va_list ap;
	char buf[40];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	LcdDrawRetangleFill(0, ln*20, 319, ln*20+19, GRAY(28));
	LcdTextColorZoom(0, ln*20+2, BLACK, 1, buf, strlen(buf));
}
void LcdLinePrintHex(int ln, uint8_t *data, int len)
{
	char buf[40], *p = buf;

	for(int i = 0; buf && i < len; i++)
	{
		snprintf(p, 4, "%02X ", data[i]);
		p += 3;
		if( p - buf >=  sizeof(buf) )
		{
			break;
		}
	}
	if( p - buf > 0 )
	{
		LcdLinePrintf(ln, buf);
	}
}
