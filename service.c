#include "lcd.h"
#include "usart.h"
#include "service.h"

static ModbusContext context;

static void ServiceX03Request(X03RequestContext* x)
{
	UsartSend(USART1, x->data, X03RequestGetLength(x));
	LcdLinePrintf(1, "%s", __func__);
	LcdLinePrintHex(2, x->data, X03RequestGetLength(x));
}
static void ServiceX10Request(X10RequestContext* x)
{
	UsartSend(USART1, x->data, X10RequestGetLength(x));
	LcdLinePrintf(3, "%s", __func__);
	LcdLinePrintHex(4, x->data, X10RequestGetLength(x));
}
void ServiceInit(void)
{
	ModbusInit(&context);
	ModbusSetMac(&context, 0x01);
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
	ServiceInit();
}
