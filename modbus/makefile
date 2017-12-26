ARCH:=
CC:=$(ARCH)gcc
TARGET:= X03Request.exe X03Response.exe
TARGET+= X10Request.exe X10Response.exe

test: $(TARGET)
	@./X03Request.exe
	@./X03Response.exe
	@./X10Request.exe
	@./X10Response.exe
X03Request.exe: x03request.c crc16.c
	$(CC) $+ -DTEST_X03REQUEST -o $@
X03Response.exe: x03response.c crc16.c
	$(CC) $+ -DTEST_X03RESPONSE -o $@
X10Request.exe: x10request.c crc16.c
	$(CC) $+ -DTEST_X10REQUEST -o $@
X10Response.exe: x10response.c crc16.c
	$(CC) $+ -DTEST_X10RESPONSE -o $@
clean:
	@rm -rvf *.exe *.o
