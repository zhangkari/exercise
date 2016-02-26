OBJDIR = target
SERVER = RelaySrvr
MASTER = master
SLAVE  = slave
PROJ = $(SERVER) $(MASTER) $(SLAVE) 
CC = gcc
CFLAGS =  -Iinclude \
		  -g \
		  -pthread\
	      -DDEBUG #-m32

LDFLAGS = -pthread
                     
SRC = $(wildcard src/lib/*.c)
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst %.c,$(OBJDIR)/%.d,$(SRC))

MAIN_SRC= $(wildcard src/*.c)
MAIN_OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(MAIN_SRC))

VPATH = src:include

all : $(OBJDIR) $(DEP) $(OBJ) $(MAIN_OBJ) $(PROJ)
	@echo "Build OK"

$(SERVER) : $(OBJ) $(OBJDIR)/src/server.o
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compile $(SERVER) OK"

$(MASTER) : $(OBJ) $(OBJDIR)/src/master.o
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compile $(MASTER) OK"

$(SLAVE) : $(OBJ) $(OBJDIR)/src/slave.o
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compile $(SLAVE) OK"


ifeq ($(wildcard target/src/lib), )
	@mkdir -p target/src/lib
endif

$(OBJDIR)/%.o:%.c $(OBJDIR)/%.d
	@echo "Compiling $@ "
	@$(CC) -c  $(CFLAGS) -o $@ $<

$(OBJDIR)/%.d:%.c
	@echo "Generating $@ "
	@$(CC) -MM  $(CFLAGS) $< > $@ 
	@sed -i 's/$(patsubst %.d,%.o,$(notdir $@))/$(patsubst %.d,%.o,$(notdir $@)) $(notdir $@)/' $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src/lib

.PHONEY:clean
clean:
	@rm -rf $(OBJDIR) $(PROJ)
