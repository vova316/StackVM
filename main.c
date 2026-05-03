#include "vm.h"
#include "interpret.h"

const union ins program[] = {
    { .as_noarg = {BC_IREAD} },
    { .as_noarg = {BC_IREAD} },
    { .as_arg64 = {BC_PUSH, .arg = 10} },
    { .as_noarg = {BC_IADD} },
    { .as_noarg = {BC_IADD} },
    { .as_arg64 = {BC_PUSH, .arg = 20} },
    { .as_arg64 = {BC_PUSH, .arg = 23} },
    { BC_ICMP },
    { .as_noarg = {BC_IPRINT} },
    { .as_arg64 = {BC_PUSH, .arg = 19} },
    { BC_SWAP },
    { BC_DUP },
    { BC_IPRINT },
    { .as_noarg = {BC_STOP} }
};

int main() {
    struct vm_state state = state_create(program);
    interpret(&state);
    state_destroy(&state);
    return 0;
}

