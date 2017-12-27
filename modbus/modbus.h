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

void ModbusInit(void);
void ModbusPush(uint8_t);
void ModbusSetSelfMac(uint8_t);
uint8_t ModbusCheckRequest(void);
uint8_t ModbusCheckResponse(void);
uint8_t ModbusGetLength(void);
X03RequestContext* ModbusGetX03RequestContext(void);
X03ResponseContext* ModbusGetX03ResponseContext(void);
X10RequestContext* ModbusGetX10RequestContext(void);
X10ResponseContext* ModbusGetX10ResponseContext(void);

#endif//__MODBUS_H__
