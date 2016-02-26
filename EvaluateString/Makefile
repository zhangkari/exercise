PROJ  := calc
SRCS  := $(wildcard *.c)
OBJS  := $(patsubst %.c, %.o, $(SRCS))
CC    := gcc
CFLAGS = -g

$(PROJ):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $< -c

clean:
	@rm $(PROJ) $(OBJS) -rvf
