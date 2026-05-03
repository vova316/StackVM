#include "stack.h"
#include <stdlib.h>

struct stack stack_create(size_t size) {
    return (struct stack){ .data = malloc(sizeof(int64_t) * size), .count = 0, .capacity = size };
}

void stack_destroy(struct stack *s) {
    free(s->data);
    s->data = NULL;
}

bool stack_push(struct stack *s, int64_t value) {
    if (s->count >= s->capacity) return false;
    s->data[s->count++] = value;
    return true;
}

struct maybe_int64 stack_pop(struct stack *s) {
    if (s->count == 0) return none_int64();
    return some_int64(s->data[--s->count]);
}
