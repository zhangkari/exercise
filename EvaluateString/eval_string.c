#include <stdio.h>
#include <stdlib.h>
#include "eval_string.h"

int validate_operator(char ch)
{	
	if( '+' == ch || '-' == ch || '*' == ch || '/' == ch ||
		'(' == ch || ')' == ch || '\n' == ch )
	{
		return 0;
	}

	return -1;
}

int validate_operand(char ch)
{	
	// Just suport 10-decimalism  now
	if(ch >= '0' && ch <= '9')
		return 0;

	return -1;
}

static int calc_result(int opt1, int opt2, char operator)
{
	switch(operator)
	{
		case '+':
			return opt1 + opt2;

		case '-':
			return opt1 - opt2;

		case '*':
			return opt1 * opt2;

		case '/':
			return opt1 / opt2;

		default:
			printf("ERROR: Invalid operator in calc_result.\n");
			exit(1);
	}
}

int evaluate_string(const buffer_st* buff)
{
	int ret = 0;

	int i = 0;
	char charin;

	for(i=0; i<buff->length; ++i)
	{
		charin = buff->data[i];
		if(validate_operand(charin) < 0 && validate_operator(charin) < 0)
		{
			filter_char((buffer_st*)buff, charin);
		}
	}

	stack_st* operand = init_stack(typeInt);
	if(NULL == operand)
	{
		printf("ERROR: Failed init operand stack.\n");
		return -1;
	}

	stack_st* operator = init_stack(typeChar);
	if(NULL == operator)
	{
		printf("ERROR: Failed init operator stack.\n");
		return -1;
	}

	char enter = '\n';
	push_stack(typeChar, operator, &enter);

	int num = 0;

	i = 0;
	charin  = buff->data[i++];
	char charopt;
	peek_stack_top(typeChar, operator, &charopt);

	while(charin != '\n' || charopt != '\n')
	{
		// operand
		if(validate_operator(charin) < 0)
		{
			do
			{
				int n = charin - '0';
				num *= 10;
				num += n;
				charin  = buff->data[i++];
			} while( validate_operator(charin) < 0);

			push_stack(typeInt, operand, &num);
			peek_stack_top(typeChar, operator, &charopt);
			num = 0;

			continue;
		}

		// operator
		char optor;
		peek_stack_top(typeChar, operator, &optor);
		int priority = calc_priority(optor, charin);

		//  ' < '
		if(priority < 0)
		{
			push_stack(typeChar, operator, &charin);
			charin  = buff->data[i++];
			peek_stack_top(typeChar, operator, &charopt);
		}

		// ' = '; ( )  or \n   \n
		else if(0 == priority)
		{
			// ()
			pop_stack(typeChar, operator, &optor);
			charin = buff->data[i++];
			peek_stack_top(typeChar, operator, &charopt);
		}

		// ' > '
		else if(priority > 0)
		{
			int oprnd1, oprnd2;
			pop_stack(typeInt, operand, &oprnd1);
			pop_stack(typeInt, operand, &oprnd2);
			pop_stack(typeChar, operator, &optor);

			int result = calc_result(oprnd2, oprnd1, optor);
			push_stack(typeInt, operand, &result);
			peek_stack_top(typeChar, operator, &charopt);
		}
	}

	printf("%s", buff->data);
	printf("=%d\n", ((int*)operand->base)[0]);
	destroy_stack(operand);
	destroy_stack(operator);

	return ret;
}

int calc_priority(char ch1, char ch2)
{
	if(validate_operator(ch1) || validate_operator(ch2) )
	{
		printf("ERROR: Invalid operator in calc_priority.\n");
		exit(1);
	}

	if('+' == ch1)
	{
		if('+' == ch2 || '-' == ch2 || ')' == ch2 || '\n' == ch2)
			return 1;

		if('*' == ch2 || '/' == ch2 || '(' == ch2)
			return -1;
	}

	else if('-' == ch1)
	{
		if('+' == ch2 || '-' == ch2 || ')' == ch2 || '\n' == ch2)
			return 1;

		if('*' == ch2 || '/' == ch2 || '(' == ch2)
			return -1;

	}

	else if('*' == ch1)
	{
		if('(' == ch2)
			return -1;

		else
			return 1;
	}

	else if('/' == ch1)
	{
		if('(' == ch2)
			return -1;

		else
			return 1;
	}

	else if('(' == ch1)
	{
		if('\n' == ch2)
		{
			printf("ERROR: Invalid string format.\n");
			exit(1);
		}

		else if(')' == ch2)
			return 0;

		else
			return -1;
	}

	else if(')' == ch1)
	{
		if('(' == ch2)
		{
			printf("ERROR: Invalidate string format.\n");
			exit(1);
		}

		else
			return 1;
	}

	else if('\n' == ch1)
	{
		if(')' == ch2)
		{
			printf("ERROR: Invalidate string format.\n");
			exit(1);
		}

		else if('\n' == ch2)
			return 0;

		else 
			return -1;
	}
}

stack_st* init_stack(eType type) 
{
	stack_st* stack = NULL;

	do
	{
		stack = (stack_st*)malloc(sizeof(stack_st));
		if(NULL == stack)
			break;

		if(typeChar == type)
		{
			stack->base = (char*)malloc(MAX_INPUT * sizeof(char));
		}
		else if(typeInt == type)
		{
			stack->base = (int*)malloc(MAX_INPUT * sizeof(int)); 
		}

		if(NULL == stack->base)
			break;

		stack->size = MAX_INPUT;
		stack->top = -1;

		return stack;

	}while(0);

	if(NULL != stack)
	{
		if(NULL != stack->base)
			free(stack->base);

		free(stack);
	}

	return NULL;
}

static int validate_stack(stack_st* stack)
{
	if(NULL == stack)
		return -1;

	if(NULL == stack->base)
		return -1;
}

void destroy_stack(stack_st* stack)
{
	if(NULL != stack)
	{
		if(NULL != stack->base)
		{
			free(stack->base);
			stack->base = NULL;
		}

		free(stack);
		stack = NULL;
	}
}

int push_stack(eType type, stack_st* stack, void* data)
{
	validate_stack(stack);

	if(stack->top + 1 >= stack->size)
	{
		printf("ERROR: stack is overflow.\n");
		exit(1);
	}

	++stack->top;

	if(typeChar == type)
	{
		char ch = *((char*)data);
		char* cp = (char*)(stack->base) + stack->top;
		*cp = ch;
	}
	else if(typeInt == type)
	{
		int n = *((int*)data);
		int* np = (int*)(stack->base) + stack->top;
		*np = n;
	}

	return 0;
}

int pop_stack(eType type, stack_st* stack, void* data)
{
	validate_stack(stack);

	if(stack->top < 0)
	{
		printf("ERROR: stack is empty.\n");
		exit(1);
	}

	if(typeChar == type)
	{
		char* cp1 = (char*)data;
		char* cp2 = (char*)(stack->base) + stack->top;
		*cp1 = *cp2;
	}
	else if(typeInt == type)
	{
		int* np1 = (int*)data;
		int* np2 = (int*)(stack->base) + stack->top;
		*np1 = *np2;
	}

	--stack->top;

	return 0;
}

int peek_stack_top(eType type, stack_st* stack, void* data)
{
	validate_stack(stack);

	if(stack->top + 1 >= stack->size || stack->top < 0)
		return -1;

	if(typeChar == type)
	{
		char* cp1 = (char*)data;
		char* cp2 = (char*)(stack->base + stack->top);
		*cp1 = *cp2;
	}
	else if(typeInt == type)
	{
		int* cp1 = (int*)data;
		int* cp2 = (int*)(stack->base + stack->top);
		*cp1 = *cp2;
	}

	return 0;
}

int filter_char(buffer_st* buff, char ch)
{
	if(NULL == buff || NULL == buff->data || buff->length <= 0)
	{
		printf("ERROR: invalid arguments in filter_char().\n");
		return -1;
	}

	char* p = buff->data;
	int len = buff->length;
	int i, j = -1;

	for(i=0; i<len; ++i)
	{
		if(ch != p[i])
		{
			++j;
			p[j] = p[i];
		}	
	}

	p[j+1] = '\n';
	p[j+2] = 0;
	buff->length -= (i-j-1);

	return 0;
}

