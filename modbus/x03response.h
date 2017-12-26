#ifndef __X03_RESPONSE_H__
#define __X03_RESPONSE_H__
#include "x03request.h"


typedef enum{
	X03ResponseIndexSlave = 0,
	X03ResponseIndexFcode = 1,
	X03ResponseIndexBcount= 2,
	X03ResponseIndexData = 3,
}X03ResponseIndex;

typedef enum {
	X03ResponseBcountMin = X03RequestCountMin * 2,
	X03ResponseBcountMax = X03RequestCountMax * 2,
}X03ResponseBcountType;

typedef struct {
	uint8_t data[X03ResponseIndexData + X03ResponseBcountMax + 2];
}X03ResponseContext;

uint8_t X03ResponseCheck(X03ResponseContext*);
uint8_t X03ResponseGetSlave(X03ResponseContext*);
uint8_t X03ResponseGetBcount(X03ResponseContext*);
uint16_t X03ResponseGetData(X03ResponseContext*, uint8_t);
uint16_t X03ResponseCalcCrc(X03ResponseContext*);
uint16_t X03ResponseGetCrc(X03ResponseContext*);
uint8_t  X03ResponseGetLength(X03ResponseContext*);

void X03ResponseSetSlave(X03ResponseContext*, uint8_t);
void X03ResponseSetFcode(X03ResponseContext*, uint8_t);
void X03ResponseSetBcount(X03ResponseContext*, uint8_t);
void X03ResponseSetData(X03ResponseContext*, uint8_t, uint16_t);
void X03ResponseSetCrc(X03ResponseContext*, uint16_t);

void X03ResponseShowContext(X03ResponseContext*);

#endif//__X03_RESPONSE_H__
