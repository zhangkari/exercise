;
; file name:   libasm.asm
; description: asm function
;

global out_byte	;
global print ;
global load_gdtr ;
global load_idtr;
global in_byte;
global asm_int_handler21; 
global asm_sti ;

extern int_handler21 ;

out_byte:		   ; void out_byte(word port, byte value)	
	mov edx, [esp + 4] ; port
	mov al,  [esp + 8] ; value
	out dx, al
	nop
	nop
	ret

print:		   ; void print(char)
	mov al, [esp +4] 
	mov ah, 0x0f ; white color 
	mov cx, ax
	cmp al, 0x0a; '\n'
  	jnz not_equal
	inc esi  ;	row
	xor edi, edi ;	column
	jmp end
  not_equal:
	mov ax, si    ; base value
	mov bx, 0xa0 ; 160 bytes per row
	mul bx       ; ax = ax * 160
	mov bx, di  ; bx = edi
	add di, ax  ; di = ax + edi, and column
	mov [gs:di], cx
	add bx, 2;   ; next char
	mov di, bx  ; 
  end:
	ret

load_gdtr: 	; void load_gdtr(int limit, int addr)
	mov ax, [esp + 4] ; limit
	mov [esp + 6], ax
	lgdt [esp + 6]
	ret
load_idtr:
	mov ax, [esp + 4]
	mov [esp + 6], ax
	lidt [esp + 6]
	ret 

in_byte:	;int in_byte(int port)
	mov edx, [esp + 4] ; port
	mov eax, 0
	in al, dx
	ret

asm_int_handler21:
	push es
	push ds
	pushad
	mov eax, esp
	push eax
	mov ax, ss
	mov ds, ax
	mov es, ax
	call int_handler21
	pop eax
	popad
	pop ds
	pop es
	iretd

asm_sti:	; STI
	STI
	RET
