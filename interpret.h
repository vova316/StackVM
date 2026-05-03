#ifndef INTERPRET_H
#define INTERPRET_H

#include "vm.h"

void interpret(struct vm_state* state);
// struct vm_state state_create(const union ins* ip);
// void state_destroy(struct vm_state* state);

#endif
