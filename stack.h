#ifndef STACK_H
#define STACK_H
#include "common.h"
#include <stddef.h>

struct stack {
    int64_t* data;
    size_t count;
    size_t capacity;
};

struct stack stack_create(size_t size);
void stack_destroy(struct stack *s);
bool stack_push(struct stack *s, int64_t value);
struct maybe_int64 stack_pop(struct stack *s);
#endif
