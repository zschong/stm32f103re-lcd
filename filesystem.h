#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

int FileSystemErase(int address, int len);
int FileSystemRead(int address, char *buf, int len);
int FileSystemWrite(int address, char *buf, int len);

#endif//__FILE_SYSTEM_H__
