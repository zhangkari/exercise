#ifndef __INT8259__H__
#define __INT8259__H__

typedef void(*IntHandlerPtr)(int* esp);

void init_8259A();
void int_handler20(int* esp);
void int_handler21(int* esp);

#endif
