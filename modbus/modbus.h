#ifndef __MODBUS_H__
#define __MODBUS_H__
#include "x03request.h"
#include "x03response.h"
#include "x10request.h"
#include "x10response.h"

typedef enum {
	ModbusIndexSlave = 0,
	ModbusIndexFcode = 1,
}ModbusIndexType;

typedef enum {
	ModbusFcodeX03 = 0x03,
	ModbusFcodeX10 = 0x10,
}ModbusFcodeType;
typedef struct {
	uint8_t mac;
	uint8_t index;
	uint8_t buffer[256];
}ModbusContext;

void ModbusInit(ModbusContext*);
void ModbusPush(ModbusContext*, uint8_t);
void ModbusSetMac(ModbusContext*, uint8_t);
uint8_t ModbusCheckRequest(ModbusContext*);
uint8_t ModbusCheckResponse(ModbusContext*);
uint8_t ModbusGetLength(ModbusContext*);
uint8_t ModbusGetFcode(ModbusContext*);
X03RequestContext* ModbusGetX03RequestContext(ModbusContext*);
X03ResponseContext* ModbusGetX03ResponseContext(ModbusContext*);
X10RequestContext* ModbusGetX10RequestContext(ModbusContext*);
X10ResponseContext* ModbusGetX10ResponseContext(ModbusContext*);

#endif//__MODBUS_H__
