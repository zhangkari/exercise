#ifndef __LIBASM__H__
#define __LIBASM__H__
#include <type.h>
void out_byte(word port, byte value);
byte in_byte(word port);
void print(char ch);
void load_gdtr(int limit, int addr);
void load_idtr (int limit, int addr);
void asm_int_handler21();
void asm_sti();
#endif
