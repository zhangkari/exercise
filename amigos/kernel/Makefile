
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CC = gcc
CFLAGS = -g -I../include -m32

all:$(OBJ)

.phony: clean
clean:
	@rm *.o -rvf
