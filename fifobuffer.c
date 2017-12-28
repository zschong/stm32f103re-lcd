#include <stdio.h>
#include "fifobuffer.h"

#ifdef TEST_FIFO_BUFFER
void FifoShowHex(FifoBuffer* buf)
{
	int i = 0;

	printf("buf->beg(%d)\n", buf->beg);
	printf("buf->end(%d)\n", buf->end);
	printf("buf->len(%d)\n", buf->len);
	for(i = 0; i < 100; i++)
	{
		printf("%02X ", FifoBufferGet(*buf));
		if( ((i+1) % 16) == 0 )
		{
			printf("\n");
		}
	}
	printf("\n");
}
int main(void)
{
	int i = 0;
	FifoBuffer buf = {0,0,0};

	for(i = 0; i < 0xAB; i++)
	{
		FifoBufferSet(buf, i);
	}
	FifoShowHex(&buf);
	for(i = 0; i < 0xAB; i++)
	{
		FifoBufferSet(buf, i);
	}
	FifoShowHex(&buf);
	FifoShowHex(&buf);
	FifoShowHex(&buf);
	FifoShowHex(&buf);

	return 0;
}
#endif//TEST_FIFO_BUFFER
