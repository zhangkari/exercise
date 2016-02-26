PROJ := huff 
CC   := gcc
CFLAGS = -g

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

$(PROJ):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

rebuild:
	@make clean 
	@make

.PHONEY:clean
clean:
	@rm $(PROJ) testbitpool *.o  -rvf
