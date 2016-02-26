PROJECT := dkserver
COMPILE := erlc -v
SRCS := $(wildcard src/*.erl)
TEMPOBJS = $(patsubst %.erl, %.beam, $(SRCS))
TARGET = target
OBJS = $(TARGET)/$(notdir $(TEMPOBJS))

$(PROJECT) : $(OBJS)
	@echo "Comple complete"
	@echo "Leaving: $$PWD"

$(TARGET)/%.beam : src/%.erl
	$(COMPILE) -o $(TARGET) $<

clean:
	@rm $(OBJS) target/*.dump -rvf
