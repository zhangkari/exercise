PROJ = test
CC = gcc
CFLAGS = -g -DDEBUG #-m32 
LDFLAGS = -pthread

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(PROJ) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@

.PHONEY:clean
clean:
	@rm -rvf $(PROJ) $(OBJ)
