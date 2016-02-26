CC = gcc
NASM = nasm
INCLUDE = include
CFLAGS = -I$(INCLUDE) -fno-builtin  -fno-stack-protector -m32
OBJDIR = target

SRCS := $(wildcard boot/*.c)\
       $(wildcard lib/*.c)\
       $(wildcard kernel/*.c)\
       $(wildcard lib/*.asm)

SRC := $(notdir $(SRCS))
OBJS := $(patsubst %.c, %.o, $(patsubst %.asm, %.o, $(SRC))) 

$(OBJDIR)/boot.img: $(OBJDIR)/boot.bin $(OBJDIR)/main.bin Makefile
	dd if=target/boot.bin of=target/boot.img bs=512 count=1 conv=notrunc
	dd if=target/main.bin of=target/boot.img bs=1 seek=512

$(OBJDIR)/boot.bin:boot/boot.asm
	$(NASM) $< -o $@

$(OBJDIR)/main.bin : $(OBJDIR)/main.lo
	objcopy -R .note -R .comment -S -O binary target/main.lo $@ 

$(OBJDIR)/main.lo : target/main.o target/libasm.o target/alibc.o target/int.o target/desctbl.o 
	@echo $^
	ld -m elf_i386 -o $@ -Ttext 0x9000 -e main $^

	

$(OBJDIR)/%.o : boot/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : kernel/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : lib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : lib/%.asm
	$(NASM) $< -felf -o $@

.phony: clean
clean:
	@rm $(OBJDIR)/* -vf
