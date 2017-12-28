#ifndef __X03_REQUEST_H__
#define __X03_REQUEST_H__
#include "typedef.h"

typedef enum{
	X03RequestIndexSlave = 0,
	X03RequestIndexFcode = 1,
	X03RequestIndexOffset0= 2,
	X03RequestIndexOffset1= 3,
	X03RequestIndexCount0 = 4,
	X03RequestIndexCount1 = 5,
	X03RequestIndexCrc0 = 6,
	X03RequestIndexCrc1 = 7,
	X03RequestIndexMax = 8
}X03RequestIndex;

typedef enum{
	X03RequestCountMin = 1,
	X03RequestCountMax = 125 
}X03RequestCountType;

typedef struct {
	uint8_t data[X03RequestIndexMax];
}X03RequestContext;

uint8_t X03RequestCheck(X03RequestContext*);
uint8_t X03RequestGetSlave(X03RequestContext*);
uint8_t X03RequestGetFcode(X03RequestContext*);
uint16_t X03RequestGetOffset(X03RequestContext*);
uint16_t X03RequestGetCount(X03RequestContext*);
uint16_t X03RequestCalcCrc(X03RequestContext*);
uint16_t X03RequestGetCrc(X03RequestContext*);

void X03RequestSetSlave(X03RequestContext*, uint8_t);
void X03RequestSetFcode(X03RequestContext*, uint8_t);
void X03RequestSetOffset(X03RequestContext*, uint16_t);
void X03RequestSetCount(X03RequestContext*, uint16_t);
void X03RequestSetCrc(X03RequestContext*, uint16_t);

void X03RequestShowContext(X03RequestContext*);

#endif//__X03_REQUEST_H__
