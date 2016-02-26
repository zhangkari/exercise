#ifndef __EVAL__STRING__H__
#define __EVAL__STRING__H__

#define MAX_INPUT 1024 

typedef struct
{
	int  length;
	char* data;
}buffer_st;

typedef struct
{
	void* base;
	int size;
	int top;
}stack_st;

typedef enum {
	typeChar,
	typeInt,
}eType;

stack_st* init_stack(eType); 
void destroy_stack(stack_st* stack);
int push_stack(eType type, stack_st* stack, void* data);
int pop_stack(eType type, stack_st* stack, void* data);
int peek_stack_top(eType type, stack_st* stack, void* data);

int validate_operator(char ch);
int validate_operand(char ch);
int filter_char(buffer_st*buff, char ch);

int evaluate_string(const buffer_st* buff);
int calc_priority(char ch1, char ch2);

#endif
