PROJ = imgutil
CC = gcc
CFLAGS = -g -DDEBUG #-m32 

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(PROJ) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $@



.PHONEY:clean
clean:
	rm -rvf $(PROJ) $(OBJ)
