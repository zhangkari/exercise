/***********************
 * file name:   stack.c
 * 
 * ********************/
#include <assert.h>
#include <stdlib.h>

#include <comm.h>
#include <stack.h>

struct stack_s {
    int size;
    int top;
    int *base;
};

stack_t* new_stack(int size)
{
    if (size <= 0) {
        LogE("size must > 0");
        return NULL;
    }

    stack_t *stack = (stack_t *)calloc(1, sizeof(stack_t));
    if (NULL == stack) {
        return NULL;
    }
    
    stack->base = (int *)calloc(size, sizeof(int));
    if (NULL == stack->base) {
        free (stack);
        stack = NULL;
        return NULL;
    }

    stack->size = size;

    return stack;
}

void free_stack(stack_t* stack)
{
    if (NULL != stack) {
        if (NULL != stack->base) {
            free(stack->base);
            stack->base = NULL;
        }

        free(stack);
    }
}

int push_stack(stack_t *stack, int elem)
{
    VALIDATE_NOT_NULL(stack);
    if (stack->top < stack->size) {
        stack->base[stack->top++] = elem;
        return 0;
    } else {
        LogE("stack top overflow");
        return -1;
    }
}

int pop_stack(stack_t *stack, int *elem)
{
    VALIDATE_NOT_NULL(stack);
    if (!is_stack_empty(stack)) {
        if (NULL != elem) {
            *elem = stack->base[--stack->top];
        } else {
            --stack->top;
        }
        return 0;
    } else {
        LogE("stack bottom overflow");
        return -1;
    }
}

Bool is_stack_empty(const stack_t *stack)
{
    if (NULL == stack) {
        LogE("NULL pointer");
        return False;
    }

    if (stack->top >= 1) {
        return True;
    }

    return False;
}

int get_stack_top(const stack_t *stack, int *top)
{
    VALIDATE_NOT_NULL2(stack, top);

    if (NULL == stack) {
        return -1;
    }

    if (is_stack_empty(stack) ) {
        return -1;
    }

    *top = stack->base[stack->top-1];

    return 0;
}

Bool is_stack_exist(const stack_t *stack, int elem)
{
    assert(NULL != stack);

    int top = stack->top;
    int i;
    for (i = 0; i < top; ++i) {
        if (elem == stack->base[i]) {
            return True;
        }
    }
    return False;
}
int get_stack_height(const stack_t *stack)
{
    return stack->top;
}
