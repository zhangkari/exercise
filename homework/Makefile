PROJ=railway
CC=gcc
CFLAGS = -g -Iinclude #-DDEBUG

SRCS = $(wildcard *.c) $(wildcard src/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

$(PROJ):$(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

clean:
	@rm $(PROJ) $(PROJ).exe *.o src/*.o -rvf
