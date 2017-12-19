/* RA8875 */
#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <stdarg.h>
#include "gpio.h"

typedef enum{
	TextMode = 0,
	ImageMode = 1,
}DisplayMode;
typedef enum{
	Layer1 = 0,
	Layer2 = 1,
	LayerGradual = 2,
	LayerTranparent = 3,
	LayerOR = 4,
	LayerAND = 5,
	LayerFloating = 6,
	LayerFloatingBGTR = (1<<5)|6,
}LayerMode;
typedef enum{
	Layer1_8of8 = (0 << 4),
	Layer1_7of8 = (1 << 0),
	Layer1_6of8 = (2 << 0),
	Layer1_5of8 = (3 << 0),
	Layer1_4of8 = (4 << 0),
	Layer1_3of8 = (5 << 0),
	Layer1_2of8 = (6 << 0),
	Layer1_1of8 = (7 << 0),
	Layer1_0of8 = (8 << 0),
}Layer1Transparency;
typedef enum{
	Layer2_8of8 = (0 << 4),
	Layer2_7of8 = (1 << 4),
	Layer2_6of8 = (2 << 4),
	Layer2_5of8 = (3 << 4),
	Layer2_4of8 = (4 << 4),
	Layer2_3of8 = (5 << 4),
	Layer2_2of8 = (6 << 4),
	Layer2_1of8 = (7 << 4),
	Layer2_0of8 = (8 << 4),
}Layer2Transparency;

#define LCD_X		320
#define LCD_Y		240

#define GRB(r,g,b)	( ((0x1F&(r)) << 11) | ((0x3F&((g)*2)) << 5) | (0x1F&(b)) )
#define GRAY(x)		GRB(x, x, x)
#define BLACK		GRB(0, 0, 0)
#define WHITE		GRB(0xff, 0xff, 0xff)
#define RED			GRB(0xff, 0x00, 0x00)
#define GREEN		GRB(0x00, 0xff, 0x00)
#define BLUE		GRB(0x00, 0x00, 0xff)

#define LCD_DB		GPIOA
#define LCD_DB0		PA0
#define LCD_DB1		PA1
#define LCD_DB2		PA2
#define LCD_DB3		PA3
#define LCD_DB4		PA4
#define LCD_DB5		PA5
#define LCD_DB6		PA6
#define LCD_DB7		PA7

#define LCD_RS		PC3
#define LCD_CS		PC2
#define LCD_WR		PC1
#define LCD_RD		PC0

#define LCD_RST		PC6
#define LCD_INT		PC7
#define LCD_RDY		PC8
#define LCD_BL		PC9


#define RS_CS_WR_RD(rs, cs, wr, rd)	\
do{\
	((rs) == 0) ? GpioOff(LCD_RS) : GpioOn(LCD_RS);	\
	((cs) == 0) ? GpioOff(LCD_CS) : GpioOn(LCD_CS);	\
	((wr) == 0) ? GpioOff(LCD_WR) : GpioOn(LCD_WR);	\
	((rd) == 0) ? GpioOff(LCD_RD) : GpioOn(LCD_RD);	\
}while(0)

#define RS_WR_CS_RD(rs, wr, cs, rd)	\
do{\
	((rs) == 0) ? GpioOff(LCD_RS) : GpioOn(LCD_RS);	\
	((wr) == 0) ? GpioOff(LCD_WR) : GpioOn(LCD_WR);	\
	((cs) == 0) ? GpioOff(LCD_CS) : GpioOn(LCD_CS);	\
	((rd) == 0) ? GpioOff(LCD_RD) : GpioOn(LCD_RD);	\
}while(0)

#define CS_RS_RD_WR(cs, rs, rd, wr)	\
do{\
	((cs) == 0) ? GpioOff(LCD_CS) : GpioOn(LCD_CS);	\
	((rs) == 0) ? GpioOff(LCD_RS) : GpioOn(LCD_RS);	\
	((rd) == 0) ? GpioOff(LCD_RD) : GpioOn(LCD_RD);	\
	((wr) == 0) ? GpioOff(LCD_WR) : GpioOn(LCD_WR);	\
}while(0)

#define RS_RD_CS_WR(rs, rd, cs, wr)	\
do{\
	((rs) == 0) ? GpioOff(LCD_RS) : GpioOn(LCD_RS);	\
	((rd) == 0) ? GpioOff(LCD_RD) : GpioOn(LCD_RD);	\
	((cs) == 0) ? GpioOff(LCD_CS) : GpioOn(LCD_CS);	\
	((wr) == 0) ? GpioOff(LCD_WR) : GpioOn(LCD_WR);	\
}while(0)

#define LcdDataBusRead()	(uint8_t)(GPIO_ReadInputData(LCD_DB) & 0x00ff)
#define LcdDataBusWrite(data)	\
do{\
	GPIO_Write(LCD_DB, (GPIO_ReadOutputData(LCD_DB) & 0xff00) | (data) );\
}while(0)

#define LcdDataBusInput() \
do{\
	GpioInit(LCD_DB7, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB6, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB5, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB4, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB2, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB1, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB0, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz); \
}while(0)

#define LcdDataBusOutput() \
do{\
	GpioInit(LCD_DB7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB6, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB5, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB4, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB3, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB2, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
	GpioInit(LCD_DB0, GPIO_Mode_Out_PP, GPIO_Speed_50MHz); \
}while(0)


#define _LcdStatus_	LcdStatus

#define LcdRegWrite(r)\
do{\
	RS_CS_WR_RD(1, 0, 0, 1);\
	LcdDataBusWrite(r);\
	RS_WR_CS_RD(1, 1, 1, 1);\
}while(0)

#define LcdDataWrite(d)\
do{\
	RS_CS_WR_RD(0, 0, 0, 1);\
	LcdDataBusWrite(d);\
	RS_WR_CS_RD(0, 1, 1, 1);\
}while(0)

#define _LcdDataRead_	LcdDataRead

#define LcdMemWriteStart()\
do{\
	RS_CS_WR_RD(0, 0, 0, 1);\
}while(0)

#define LcdMemWrite(d)\
do{\
	GPIOC->ODR &= ~(0xffff&LCD_WR);\
	GPIOA->ODR = (GPIOA->ODR & 0xff00) | (d);\
	GPIOC->ODR |=  (0xffff&LCD_WR);\
}while(0)

#define LcdMemWriteEnd()\
do{\
	RS_CS_WR_RD(0, 1, 1, 1);\
}while(0)

#define LcdMemReadStart()\
do{\
	RS_CS_WR_RD(0, 0, 1, 1);\
	LcdDataBusInput();\
}while(0)

#define _LcdMemRead_	LcdMemRead

#define LcdMemReadEnd()\
do{\
	LcdDataBusOutput();\
	RS_CS_WR_RD(1, 1, 1, 1);\
}while(0)


void LcdInit(void);
void LcdReset(void);
void LcdGpioInit(void);

void LcdBackLight(int level);
uint8_t LcdStatus(void);
uint8_t LcdDataRead(void);
uint8_t LcdMemRead(void);
uint8_t LcdCmdRead(uint8_t cmd);
void LcdCmdWrite(uint8_t cmd, uint8_t value);
void LcdCheckBusy(void);
void LcdMemClear(void);
void LcdWriteBuffer(u16 x, u16 y, char *buf, int len);
/*------------------- Layer function -------------------------*/
void LcdLayer(int layer);
void LcdLayerMode(LayerMode mode);
void LcdTransparency(Layer1Transparency t1, Layer2Transparency t2);
void LcdFloatWindow(u16 x, u16 y, u16 w, u16 h, u16 X, u16 Y);
void LcdFloatWindowColor(u16 x, u16 y, u16 w, u16 h, u16 X, u16 Y, u16 color);
/*------------------- text function -------------------------*/
void LcdText(u16 x, u16 y, char *text, int len);
void LcdTextColor(u16 x, u16 y, u16 color, char *text, int len);
void LcdTextColorZoom(u16 x, u16 y, u16 color, u8 zoom, char *text, int len);
void LcdTextForgeGroundColor(u16 color);
void LcdTextBackGroundColor(u16 color);
void LcdTextAlignEnable(int enable);
void LcdTextBackGroundEnable(int enable);
void LcdTextRotate(int degree);
void LcdTextZoom(int size);
void LcdTextZoomHorizontal(int size);
void LcdTextZoomVertical(int size);
void LcdTextCursor(u16 x, u16 y);
void LcdWindowCursor(u16 x, u16 y);
void LcdWindowActive(u16 x, u16 y, u16 xb, u16 yb);
void LcdWindowClear(void);
void LcdDisplayMode(uint8_t mode);
void LcdColor256(void);
void LcdColor65K(void);
void LcdDrawLine(u16 x, u16 y, u16 xb, u16 yb, u16 color);
void LcdDrawRetangle(u16 x, u16 y, u16 xb, u16 yb, u16 c);
void LcdDrawRetangleFill(u16 x, u16 y, u16 xb, u16 yb, u16 c);
void LcdDrawCircle(u16 x, u16 y, u16 radius, u16 color);
void LcdDrawCircleFill(u16 x, u16 y, u16 radius, u16 color);
void LcdTouchInit(void);
bool LcdTouchXY(u16* x, u16* y);
bool LcdTouch(u16 *x, u16 *y);
void LcdLinePrintf(int i, const char *fmt, ...);

#endif//__LCD_H__
