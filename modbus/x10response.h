#ifndef __X10_RESPONSE_H__
#define __X10_RESPONSE_H__

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned short uint32_t;

typedef enum{
	X10ResponseIndexSlave = 0,
	X10ResponseIndexFcode = 1,
	X10ResponseIndexOffset0 = 2,
	X10ResponseIndexOffset1 = 3,
	X10ResponseIndexCount0 = 4,
	X10ResponseIndexCount1 = 5,
	X10ResponseIndexCrc0 = 6,
	X10ResponseIndexCrc1 = 7,
	X10ResponseIndexMax = 8,
}X10ResponseIndex;

typedef enum{
	X10ResponseCountMin = 1,
	X10ResponseCountMax = 123 
}X10ResponseCountType;

typedef struct {
	uint8_t data[X10ResponseIndexMax];
}X10ResponseContext;

uint8_t X10ResponseCheck(X10ResponseContext*);
uint8_t X10ResponseGetSlave(X10ResponseContext*);
uint8_t X10ResponseGetFcode(X10ResponseContext*);
uint16_t X10ResponseGetOffset(X10ResponseContext*);
uint16_t X10ResponseGetCount(X10ResponseContext*);
uint16_t X10ResponseCalcCrc(X10ResponseContext*);
uint16_t X10ResponseGetCrc(X10ResponseContext*);
uint8_t X10ResponseGetLength(X10ResponseContext*);

void X10ResponseSetSlave(X10ResponseContext*, uint8_t);
void X10ResponseSetFcode(X10ResponseContext*, uint8_t);
void X10ResponseSetOffset(X10ResponseContext*, uint16_t);
void X10ResponseSetCount(X10ResponseContext*, uint16_t);
void X10ResponseSetCrc(X10ResponseContext*, uint16_t);

void X10ResponseShowContext(X10ResponseContext*);

#endif//__X10_RESPONSE_H__
