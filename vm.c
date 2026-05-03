#include "vm.h"
#include <stdlib.h>

const struct ins_descr instructions[] = {
    [BC_PUSH]   = {"push",   ARG_INT64, false, 0, 1},
    [BC_POP]    = {"pop",    ARG_NONE,  false, 1, -1},
    [BC_SWAP]   = {"swap",   ARG_NONE,  false, 2, 0},
    [BC_DUP]    = {"dup",    ARG_NONE,  false, 1, 1},
    [BC_IADD]   = {"iadd",   ARG_NONE,  false, 2, -1},
    [BC_ISUB]   = {"isub",   ARG_NONE,  false, 2, -1},
    [BC_IMUL]   = {"imul",   ARG_NONE,  false, 2, -1},
    [BC_IDIV]   = {"idiv",   ARG_NONE,  false, 2, -1},
    [BC_INEG]   = {"ineg",   ARG_NONE,  false, 1, 0},
    [BC_IPRINT] = {"iprint", ARG_NONE,  false, 1, -1},
    [BC_IREAD]  = {"iread",  ARG_NONE,  false, 0, 1},
    [BC_ICMP]   = {"icmp",   ARG_NONE,  false, 2, -1},
    [BC_STOP]   = {"stop",   ARG_NONE,  true,  0, 0}
};


struct vm_state state_create(const union ins* ip) {
    return (struct vm_state){.ip = ip, .data_stack = stack_create(STACK_CAPACITY)};
}

void state_destroy(struct vm_state* state) {
    stack_destroy(&state->data_stack);
}

void print_int64(int64_t v) { printf("%ld\n", v); }
struct maybe_int64 maybe_read_int64() {
    int64_t val;
    if (scanf("%ld", &val) == 1) return some_int64(val);
    return none_int64();
}
