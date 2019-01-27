#include "memcheck.h"
#ifndef SPL_STACK_H
#define SPL_STACK_H

typedef struct StackImplementation* Stack;

Stack create_stack();

void delete_stack(Stack stack);

void push_stack(Stack stack, void *data);

int get_count(Stack stack);

void* pop_stack(Stack stack);

void* peek_stack(Stack stack);

#endif //SPL_STACK_H