PROJECT = ice_client

CC = g++
CFLAGS = -I include/core -I include/lib -I include/external/sqlite \
	 -I include/lib/math -I include/lib/mem -I include/lib/security\
         -I include/sys -I include/util -g


OBJDIR = ./target
SRCS = $(wildcard src/*.cpp)\
       $(wildcard src/core/*.cpp)\
       $(wildcard src/lib/*.cpp)\
       $(wildcard src/sys/*.cpp)\
       $(wildcard src/lib/math/*.cpp)\
       $(wildcard src/lib/mem/*.cpp)\
       $(wildcard src/lib/security/*.cpp)

SRC = $(notdir $(SRCS))
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

all:  $(OBJDIR)/ice_shell \
      $(OBJDIR)/ice_server \
      $(OBJDIR)/$(PROJECT) \
      $(OBJDIR)/sqlite_shell \
      include/sys/*.h \
      include/util/*.h \
      Makefile


client:$(OBJDIR)/$(PROJECT)

$(OBJDIR)/$(PROJECT): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 

$(OBJDIR)/%.o:src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:src/core/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:src/lib/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:src/lib/mem/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:src/lib/math/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:src/lib/security/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(OBJDIR)/%.o:src/sys/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

#$(PROJECT): client.cpp libCMath.so 
#	$(CC) $^ -o $@

libCMath.so: CMath.cpp CMath.h
	#$(CC) -fPIC -shared $< -o $@
	$(CC) $< -c -o $@

ice_shell: $(OBJDIR)/ice_shell

ice_server:$(OBJDIR)/ice_server

$(OBJDIR)/ice_shell: src/core/IceShell.c
	$(CC) $< -o $@ $(CFLAGS)

$(OBJDIR)/ice_server: src/core/IceServer.c
	$(CC) $< -o $@ $(CFLAGS)

$(OBJDIR)/sqlite_shell:src/external/sqlite/shell.c\
		       src/external/sqlite/sqlite3.c
	gcc  $^ -o $@ $(CFLAGS) -lpthread -ldl

ptree:$(OBJDIR)/ptree

$(OBJDIR)/ptree: src/util/drawTree.cpp
	g++ $^ -o $@ $(CFLAGS) -lncurses

clean:
	@touch src/main.cpp

rm:
	@rm -v $(OBJDIR)/*
