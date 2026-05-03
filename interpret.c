#include "vm.h"
#include <stdbool.h>
#include <inttypes.h>

void lift_unop(struct stack* s, int64_t (f)(int64_t)) {
    int64_t a = stack_pop(s).value;
    stack_push(s, f(a));
}
void lift_binop(struct stack* s, int64_t (f)(int64_t, int64_t)) {
    int64_t a = stack_pop(s).value;
    int64_t b = stack_pop(s).value;
    stack_push(s, f(b, a));
}

bool is_valid_jump(struct vm_state* state, int64_t jump){
    return state->ip + jump <= state->end && state->ip + jump >= state->begin;
}

// Математика
int64_t i64_add(int64_t a, int64_t b) { return a + b; }
int64_t i64_sub(int64_t a, int64_t b) {return a - b; }
int64_t i64_mul(int64_t a, int64_t b) {return a * b; }
int64_t i64_div(int64_t a, int64_t b) {return a / b; }
int64_t i64_neg(int64_t a) { return -a; }

// Обработчики
void interpret_push(struct vm_state* state) { stack_push(&state->data_stack, state->ip->as_arg64.arg); }
void interpret_iadd(struct vm_state* state) { lift_binop(&state->data_stack, i64_add); }
void interpret_isub(struct vm_state* state) { lift_binop(&state->data_stack, i64_sub); }
void interpret_imul(struct vm_state* state) { lift_binop(&state->data_stack, i64_mul); }
void interpret_idiv(struct vm_state* state) { lift_binop(&state->data_stack, i64_div); }
void interpret_ineg(struct vm_state* state) { lift_unop(&state->data_stack, i64_neg); }
void interpret_iprint(struct vm_state* state) { printf("%ld\n", stack_pop(&state->data_stack).value); }
void interpret_iread(struct vm_state* state) { 
    int64_t v; 
    scanf("%ld", &v); 
    stack_push(&state->data_stack, v); 
}

void interpret_dup(struct vm_state* state) {
    int64_t dup = stack_pop(&state->data_stack).value;
    stack_push(&state->data_stack, dup);
    stack_push(&state->data_stack, dup);
}

void interpret_swap(struct vm_state* state) {
    int64_t a = stack_pop(&state->data_stack).value;
    int64_t b = stack_pop(&state->data_stack).value;
    stack_push(&state->data_stack, a);
    stack_push(&state->data_stack, b);
}

void interpret_icmp(struct vm_state* state) {
    int64_t a = stack_pop(&state->data_stack).value;
    int64_t b = stack_pop(&state->data_stack).value;
    if(a == b) stack_push(&state->data_stack, VM_TRUE);
    else stack_push(&state->data_stack, VM_FALSE);
}

void interpret_jmp(struct vm_state* state) {
    int64_t jump = state->ip->as_arg64.arg;
    if(is_valid_jump(state, jump)) state->ip += jump;
    else state->ip++;
}

void interpret_jmz(struct vm_state* state) {
    int64_t jump = state->ip->as_arg64.arg;
    int64_t z = stack_pop(&state->data_stack).value;
    if(is_valid_jump(state, jump) && z == VM_FALSE) state->ip += jump;
    else state->ip++;
}

void interpret_stop(struct vm_state* state) { state->ip = NULL; }

// Таблица переходов
ins_interpreter * const actions[] = {
    [BC_PUSH] = interpret_push,
    [BC_IADD] = interpret_iadd,
    [BC_ISUB] = interpret_isub,
    [BC_IMUL] = interpret_imul,
    [BC_IDIV] = interpret_idiv,
    [BC_INEG] = interpret_ineg,
    [BC_DUP] = interpret_dup,
    [BC_SWAP] = interpret_swap,
    [BC_ICMP] = interpret_icmp,
    [BC_IPRINT] = interpret_iprint,
    [BC_IREAD] = interpret_iread,
    [BC_JMP] = interpret_jmp,
    [BC_JMZ] = interpret_jmz,
    [BC_STOP] = interpret_stop  
};


void interpret(struct vm_state* state) {
    while (state->ip) {
        const union ins* ins = state->ip;
        const struct ins_descr* desc = &instructions[ins->opcode];

        if (state->data_stack.count < desc->stack_min) {
            fprintf(stderr, "Stack underflow\n");
            printf(" %" PRId64 " \n", state->data_stack.count);
            printf("%s \n", desc->mnemonic);
            return;
        }

        if (state->data_stack.count + desc->stack_delta > STACK_CAPACITY) {
            fprintf(stderr, "Stack overflow\n");
            return;
        }

        actions[ins->opcode](state);

        if (state->ip && !desc->affects_ip) {
            state->ip++;
        }
    }
}

