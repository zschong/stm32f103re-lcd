#ifndef __FIFO_BUFFER_H__
#define __FIFO_BUFFER_H__
#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef struct{
	uint8_t beg;
	uint8_t end;
	uint16_t len;
	uint8_t data[256];
}FifoBuffer;

#define FifoBufferInit(__xb)	((_xb).beg = (_xb).end = (_xb).len = 0)
#define FifoBufferLength(_xb)	((_xb).len)
#define FifoBufferFull(_xb)		((_xb).len == sizeof((_xb).data))
#define FifoBufferGet(_xb)		(((_xb).len!=0)?FifoBufferGetC(_xb):0)
#define FifoBufferGetC(_xb)		((_xb).len--,(_xb).data[(_xb).beg++])
#define FifoBufferSet(_xb, _xc)	(FifoBufferFull(_xb)?0:FifoBufferSetC(_xb, _xc))
#define FifoBufferSetC(_xb,_xc)	((_xb).len++,(_xb).data[(_xb).end++]= (_xc))

#endif//__FIFO_BUFFER_H__
