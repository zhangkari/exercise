#include <desctbl.h>
#include <libasm.h>
#include <alibc.h>

void main()
{
	puts("Amigos load ok\n");

	GateDesc* idt = (GateDesc*)0x10000;
	IntHandlerPtr handlers[] = {asm_int_handler21};
	init_idt(idt, handlers);
	init_8259A();
	asm_sti();

	puts("----\n");
	putInt(341);
	putInt(0x210);

	for(; ;);
}
