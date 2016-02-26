
[BITS 16]
[ORG 0x7c00]

	jmp main

;数据定义
bootdrive db 0

;-------------------
;GDT定义
gdt:
  gdt_null:
	dd 0
  	dd 0

  gdt_code_addr equ $- gdt
  gdt_code:
	dw 0xffff
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0

  gdt_data_addr equ $-gdt
  gdt_data:
	dw 0xffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0

  video_mem_addr equ $-gdt
  video_mem:
	dw 0xffff
	dw 0x8000
	db 0x0b		; 0xb8000
	db 10010010b
	db 11001111b
	db 0


  gdt_end:
  gdt_addr:
	dw gdt_end -gdt - 1
	dd gdt

main:
	mov [bootdrive], dl
	xor ax,ax
	mov ds,ax
	mov ax,3
	int 0x10

.ResetFloppy:
	mov ax,0
	mov dl,[bootdrive]
	int 0x13
	jc .ResetFloppy

.ReadFloppy:
	xor ax,ax
	mov es,ax
	mov bx,0x9000 ;mov to [0:0x9000]
	mov ah,2
	mov dl,[bootdrive] ;驱动器号
	mov ch,0	
	mov cl,2	;开始扇区
	mov al,20	;读20 * 512 bytes
	int 13h
	jc .ReadFloppy

	;set video mode
;	mov al,0x13
;	mov ah,0x0
;	int 0x10
	
	;load gdtr
	lgdt [gdt_addr]
	;close interrupt
	cli

	; enable A20 address line
	in al, 92h
	or al, 00000010b
	out 92h, al

	;准备切换到保护模式
	mov eax, cr0
	or eax,1 
	mov cr0,eax

	jmp gdt_code_addr:code_32

[BITS 32]
code_32:
	mov ax, gdt_data_addr
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov ax, video_mem_addr
	mov gs, ax ; gs store video mem
	mov esp, 0xffff
	xor esi, esi
	xor edi, edi 
	jmp gdt_code_addr:0x9000

times 510-($-$$) db 0
db 0x55
db 0xaa


