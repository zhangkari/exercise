PROJ := analyzer
CC := gcc
CFLAGS := -g -ISources

SRCS = $(wildcard *.c)\
       $(wildcard Sources/*.c)\
       $(wildcard Sources/linux/*.c)
INCS = $(wildcard *.h)\
       $(wildcard Sources/*.h)\
       $(wildcard Sources/linux/*.h)

OBJS = $(patsubst %.c, %.o, $(SRCS)) 

$(PROJ) : $(OBJS) $(INCS)
	$(CC) $^ $(CFALGS) -o $@

%.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

.PHONEY: clean all install

clean:
	@rm $(OBJS) $(PROJ) -rvf

