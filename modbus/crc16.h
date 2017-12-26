#ifndef __CRC16_H__
#define __CRC16_H__

#ifdef cplusplus
extern "C"
#endif//cplusplus

#define CRC16(data, len)		__crc_modbus((unsigned char*)data, (int)len)
#define crc_modbus(data, len)	__crc_modbus((unsigned char*)data, (int)len)

unsigned short __crc_modbus(unsigned char *data, int len);

#endif//__CRC_H__
