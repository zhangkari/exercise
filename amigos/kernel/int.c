#include <type.h>
#include <int.h>
#include <libasm.h>

void init_8259A()
{
	out_byte(0x21, 0xff);  
	out_byte(0xa1, 0xff); 

	out_byte(0x20, 0x11); // master ICW1
	out_byte(0xa0, 0x11); // slave  ICW1

	out_byte(0x21, 0x20); // master ICW2
	out_byte(0xa1, 0x28); // slave  ICW2

	out_byte(0x21, 0x04); // master ICW3
	out_byte(0xa1, 0x02); // slave  ICW3

	out_byte(0x21, 0x01); // master ICW4
	out_byte(0xa1, 0x01); // slave  ICW4

	out_byte(0x21, 0xfd); // master OCW1 
	out_byte(0xa1, 0xff); // slave  OCW1
}

void int_handler20(int* esp)
{

}

void int_handler21(int* esp)
{
///*
	out_byte(0x20, 0x61);
	char data = in_byte(0x60);
	print(data);
//*/
	print('K');
}
