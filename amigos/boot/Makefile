
NASM = nasm
CC = gcc
CFLAGS = -I../include -fno-builtin -m32

all:  boot.img

boot.img:boot.bin main.bin
	dd if=boot.bin of=boot.img bs=512 count=1 conv=notrunc
	dd if=main.bin of=boot.img bs=1 seek=512

boot.bin:boot.asm
	$(NASM) $< -o $@

main.bin:main.c
	gcc $^ -c -o main.o $(CFLAGS)
	ld -m elf_i386 -o main.lo -Ttext 0x9000 -e main main.o ../kernel/*.o ../lib/*.o
	objcopy -R .note -R .comment -S -O binary main.lo $@ 

.phony: clean
clean:
	@rm *.img *.bin *.o *.lo -vf

