
/*
 * file name: 	gdt.h
 * description:	Global Segment Description Table
 * author:	kari.zhang
 * date:		2013-03-01
 */

#ifndef __GDT__H__
#define __GDT__H__

#include <type.h>
#include <int.h>

struct SegmDesc
{
	word  limit_low;
	word  base_low;
	byte  base_mid;
	byte  access_right;
	byte  limit_high;
	byte  base_high;
}__attribute__((__packed__));
typedef struct SegmDesc SegmDesc;

struct GateDesc
{
	word offset_low;
	word selector;
	byte param_count;
	byte access_right;
	word offset_hight;

}__attribute__((__packed__));
typedef struct GateDesc GateDesc;

void init_gdt(SegmDesc* sd);
void init_idt(GateDesc* gd, IntHandlerPtr handlers[256]);
void set_segmdesc(SegmDesc* sd, uint32 limit, dword base, word ar);
void set_gatedesc(GateDesc* sd, dword offset, word selector, word ar);

#endif

