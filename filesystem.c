#include "lcd.h"
#include "flash.h"
#include "filesystem.h"

int FileSystemEraseChip(void)
{
	FlashChipErase();
	return FLASH_CHIP_SIZE;
}
int FileSystemEraseSector(int address, int len)
{
	int beg = address & FLASH_SECTOR_ADDR_MASK;
	int end = (address + len + FLASH_SECTOR_SIZE) & FLASH_SECTOR_ADDR_MASK;
	int sectors = (end - beg) / FLASH_SECTOR_SIZE;

	for(int i = 0; i < sectors; i++)
	{
		FlashSectorErase4K(beg + i * FLASH_SECTOR_SIZE);
	}
	return sectors * FLASH_SECTOR_SIZE;
}
int FileSystemEraseBlock32(int address, int blocks)
{
	for( int i = 0; i < blocks; i++)
	{
		FlashBlockErase32K(address + i * FLASH_BLOCK32_SIZE);
	}
	return blocks * FLASH_BLOCK32_SIZE;
}
int FileSystemEraseBlock64(int address, int blocks)
{
	for( int i = 0; i < blocks; i++)
	{
		FlashBlockErase64K(blocks + i * FLASH_BLOCK64_SIZE);
	}
	return blocks * FLASH_BLOCK64_SIZE;
}
int FileSystemErase(int address, int len)
{
	if( len < 0 || len >= FLASH_CHIP_SIZE )
	{
		return FileSystemEraseChip();
	}
	return FileSystemEraseSector(address, len);
}
int FileSystemReadPages(int address, char *buf, int pages)
{
	int ret = 0;

	for(int i = 0; i < pages; i++)
	{
		int len = FlashReadFast(address + ret, buf + ret, FLASH_PAGE_SIZE);
		if( FLASH_PAGE_SIZE == len )
		{
			ret += len;
		}
		else
		{
			return ret;
		}
	}
	return ret;
}
int FileSystemRead(int address, char *buf, int len)
{
	if( address < 0 || 0 == buf || len < 0 )
	{
		return -1;
	}
	int space = FLASH_PAGE_SPACE(address);
	int pages = (len - space) / FLASH_PAGE_SIZE;
	int remain = (len - space) % FLASH_PAGE_SIZE;
	int ret = 0;

	/*[DDDDDDD_space_|pages|_remain_XXXXXX]*/
	ret += FlashReadFast(address + ret, buf + ret, space);
	ret += FileSystemReadPages(address + ret, buf + ret, pages);
	ret += FlashReadFast(address + ret, buf + ret, remain);

	return ret;
}
int FileSystemWritePages(int address, char *buf, int pages)
{
	int ret = 0;

	for(int i = 0; i < pages; i++)
	{
		int len = FlashWritePage(address + ret, buf + ret, FLASH_PAGE_SIZE);
		if( FLASH_PAGE_SIZE == len )
		{
			ret += len;
		}
		else
		{
			return ret;
		}
	}

	return ret;
}
int FileSystemWrite(int address, char *buf, int len)
{
	if( address < 0 || 0 == buf || len < 0 )
	{
		return -1;
	}
	int space = FLASH_PAGE_SPACE(address);
	int pages = (len - space) / FLASH_PAGE_SIZE;
	int remain = (len - space) % FLASH_PAGE_SIZE;
	int ret = 0;

	/*[DDDDDDD_space_|pages|_remain_XXXXXX]*/
	ret += FlashWritePage(address + ret, buf + ret, space);
	ret += FileSystemWritePages(address + ret, buf + ret, pages);
	ret += FlashWritePage(address + ret, buf + ret, remain);

	return ret;
}
