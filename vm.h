#ifndef VM_H
#define VM_H
#define VM_TRUE 1
#define VM_FALSE 0
#define VM_ERROR -1
#define STACK_CAPACITY 128
#include "stack.h"

enum opcode { 
    BC_PUSH, BC_POP, BC_SWAP, BC_DUP,
    BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV, 
    BC_INEG, BC_IPRINT, BC_IREAD, BC_ICMP, 
    BC_STOP 
};

enum ins_arg_type { ARG_NONE, ARG_INT64 };

struct bc_arg64 { enum opcode opcode; int64_t arg; };
struct bc_noarg { enum opcode opcode; };

union ins {
    enum opcode opcode;
    struct bc_arg64 as_arg64;
    struct bc_noarg as_noarg;
};

struct vm_state {
    const union ins* ip;
    struct stack data_stack;
};

struct ins_descr {
  const char*       mnemonic;
  enum ins_arg_type argtype;
  bool              affects_ip;
  size_t            stack_min;
  int64_t           stack_delta;
};

typedef void ins_interpreter(struct vm_state*);

struct vm_state state_create(const union ins* ip);
void state_destroy(struct vm_state* state);

extern const struct ins_descr instructions[];

#endif

