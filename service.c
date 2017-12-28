#include "lcd.h"
#include "usart.h"
#include "service.h"

static ModbusContext context;

static void ServiceX03Request(X03RequestContext* x)
{
	LcdLinePrintf(1, "%s", __func__);
}
static void ServiceX10Request(X10RequestContext* x)
{
	LcdLinePrintf(2, "%s", __func__);
}
void ServiceInit(void)
{
	ModbusInit(&context);
}
void ServiceRun(void)
{
	uint8_t c = 0;

	if( UsartRecv(USART1, &c, 1) != 1 )
	{
		return;
	}
	ModbusPush(&context, c);
	if( ModbusCheckRequest(&context) == 0 )
	{
		return;
	}
	switch( ModbusGetFcode(&context) )
	{
		case ModbusFcodeX03:
			ServiceX03Request( ModbusGetX03RequestContext(&context) );
			break;

		case ModbusFcodeX10:
			ServiceX10Request( ModbusGetX10RequestContext(&context) );
			break;
	}
}
