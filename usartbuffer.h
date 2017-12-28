#ifndef __USART_BUFFER_H__
#define __USART_BUFFER_H__
#include "fifobuffer.h"

typedef struct{
	FifoBuffer rx;
	FifoBuffer tx;
}UsartBuffer;

#define UsartBufferRxInit(_b)	FifoBufferInit(_b.rx)
#define UsartBufferRxLength(_b)	FifoBufferLength(_b.rx)
#define UsartBufferRxFull(_b)	FifoBufferFull(_b.rx)
#define UsartBufferRxGet(_b)	FifoBufferGet(_b.rx)
#define UsartBufferRxSet(_b,_c)	FifoBufferSet(_b.rx, _c)

#define UsartBufferTxInit(_b)	FifoBufferInit(_b.tx)
#define UsartBufferTxLength(_b)	FifoBufferLength(_b.tx)
#define UsartBufferTxFull(_b)	FifoBufferFull(_b.tx)
#define UsartBufferTxGet(_b)	FifoBufferGet(_b.tx)
#define UsartBufferTxSet(_b,_c)	FifoBufferSet(_b.tx, _c)


#endif//__USART_BUFFER_H__
