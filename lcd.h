/* RA8875 */
#ifndef __LCD_H__
#define __LCD_H__
#include "gpio.h"

typedef enum{
	DrawMode = 0,
	TextMode = 1,
}TextModeType_t;

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
/*------------------- text function -------------------------*/
void LcdLayer(int layer);
void LcdText(uint16_t x, uint16_t y, char *text, int len);
void LcdTextColor(uint16_t x, uint16_t y, uint16_t color, char *text, int len);
void LcdTextColorZoom(
uint16_t x, uint16_t y, uint16_t color, uint8_t zoom, char *text, int len);
void LcdTextForgeGroundColor(uint16_t color);
void LcdTextBackGroundColor(uint16_t color);
void LcdTextAlignEnable(int enable);
void LcdTextBackGroundEnable(int enable);
void LcdTextRotate(int degree);
void LcdTextZoom(int size);
void LcdTextZoomHorizontal(int size);
void LcdTextZoomVertical(int size);
void LcdTextCursor(uint16_t x, uint16_t y);
void LcdWindowCursor(uint16_t x, uint16_t y);
void LcdWindowActive(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb);
void LcdWindowClear(void);
void LcdDisplayMode(uint8_t mode);
void LcdColor256(void);
void LcdColor65K(void);
void 
LcdDrawLine(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb, uint16_t c);
void 
LcdDrawRetangle(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb, uint16_t c);
void 
LcdDrawRetangleFill(uint16_t x, uint16_t y, uint16_t xb, uint16_t yb, uint16_t c);
void LcdDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
void LcdDrawCircleFill(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
void LcdTouchInit(void);
bool LcdTouchXY(uint16_t* x, uint16_t* y);
bool LcdTouch(uint16_t *x, uint16_t *y);

#endif//__LCD_H__
