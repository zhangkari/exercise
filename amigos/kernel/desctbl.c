
/*
* file name: 	gdt.c
* description:	init Global Segment Description Table
* author:	kari.zhang
* date:		2013-03-01
*/

#include <type.h>
#include <desctbl.h>
#include <libasm.h>

void init_idt(struct GateDesc* idt, IntHandlerPtr handler[256])
{
	int i;
	for(i=0; i<256; ++i)
	{
		set_gatedesc(idt+i, 0, 0, 0x8e00);
	}
	load_idtr(0x7ff, 0x10000);

	set_gatedesc(idt+0x21, (uint32)handler[0], 16, 0x8e00);
}


void init_gdt(SegmDesc* gdt)
{
	int i;
	for(i=0; i<8192; ++i)
	{
	set_segmdesc(gdt+i, 0, 0, 0);
	}
	
	set_segmdesc(gdt+1, 0x0, 0x0, 0x0);
	set_segmdesc(gdt+2, 0x0, 0x0, 0x0);
	load_gdtr(0x00, 0x00);
}

void set_segmdesc(SegmDesc* sd, uint32 limit, dword base, word ar)
{
	if(limit > 0xfffff)
	{
		ar |= 0x8000;  // G_bit = 1
		limit /= 0x1000;
	}
	sd->limit_low  = limit & 0xffff;
	sd->base_low     = base & 0xffff;
	sd->base_mid     = (base >> 16) & 0xff;
	sd->access_right = ar & 0xff;
	sd->limit_high   = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
	sd->base_high    = (base >> 24) & 0xff;	
}

void set_gatedesc(GateDesc* gd, dword offset, word selector, word ar)
{
	gd->offset_low   = offset & 0xffff;
	gd->selector     = selector;
	gd->param_count  = ar & 0x1f;
	gd->access_right =  (ar >> 8) & 0xff;
	gd->offset_hight = (offset >> 16) & 0xffff;
}


