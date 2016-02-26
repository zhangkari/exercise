ASM = nasm
CC = gcc
CFLAGS = -g -I../include -fno-builtin -fno-stack-protector -m32

SRC = $(wildcard *.asm) $(wildcard *.c)
OBJ = $(patsubst %.asm, %.o, $(SRC)) $(patsubst %.c, %.o, $(SRC))

all:$(OBJ)

%.o:%.asm
	$(ASM) $< -felf -o $@

%.o:%.c
	$(CC) $< -c -o $@ $(CFLAGS)

.phony:clean
clean:
	@rm *.o -rvf
