/***********************
 * file name:   stack.h
 * 
 * ********************/

#ifndef __STACK__H__
#define __STACK__H__

#include <comm.h>

typedef struct stack_s stack_t;

stack_t* new_stack(int size);
void free_stack(stack_t* stack);
int push_stack(stack_t *stack, int elem);
int pop_stack(stack_t *stack, int *elem);
int get_stack_top(const stack_t *stack, int *top);
Bool is_stack_empty(const stack_t *stack);
Bool is_stack_exist(const stack_t *stack, int elem);
int get_stack_height(const stack_t *stack);

#endif

