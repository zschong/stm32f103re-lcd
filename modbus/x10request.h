#ifndef __X10_REQUEST_H__
#define __X10_REQUEST_H__

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned short uint32_t;

typedef enum{
	X10RequestIndexSlave = 0,
	X10RequestIndexFcode = 1,
	X10RequestIndexOffset0 = 2,
	X10RequestIndexOffset1 = 3,
	X10RequestIndexCount0 = 4,
	X10RequestIndexCount1 = 5,
	X10RequestIndexBcount = 6,
	X10RequestIndexData = 7,
}X10RequestIndex;

typedef enum{
	X10RequestCountMin = 1,
	X10RequestCountMax = 123 
}X10RequestCountType;

typedef enum{
	X10RequestBcountMin = X10RequestCountMin * 2,
	X10RequestBcountMax = X10RequestCountMax * 2,
}X10RequestBcountType;

typedef struct {
	uint8_t data[X10RequestIndexData + X10RequestBcountMax + 2];
}X10RequestContext;

uint8_t X10RequestCheck(X10RequestContext*);
uint8_t X10RequestGetSlave(X10RequestContext*);
uint8_t X10RequestGetFcode(X10RequestContext*);
uint16_t X10RequestGetOffset(X10RequestContext*);
uint16_t X10RequestGetCount(X10RequestContext*);
uint8_t  X10RequestGetBcount(X10RequestContext*);
uint16_t X10RequestCalcCrc(X10RequestContext*);
uint16_t X10RequestGetCrc(X10RequestContext*);
uint8_t X10RequestGetLength(X10RequestContext*);

void X10RequestSetSlave(X10RequestContext*, uint8_t);
void X10RequestSetFcode(X10RequestContext*, uint8_t);
void X10RequestSetOffset(X10RequestContext*, uint16_t);
void X10RequestSetCount(X10RequestContext*, uint16_t);
void X10RequestSetBcount(X10RequestContext*, uint8_t);
void X10RequestSetData(X10RequestContext*, uint8_t, uint16_t);
void X10RequestSetCrc(X10RequestContext*, uint16_t);

void X10RequestShowContext(X10RequestContext*);

#endif//__X10_REQUEST_H__
