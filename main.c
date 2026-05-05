#include "vm.h"
#include "interpret.h"

// const union ins program[] = {
//     { .as_noarg = {BC_IREAD} },
//     { .as_noarg = {BC_IREAD} },
//     { .as_arg64 = {BC_PUSH, .arg = 10} },
//     { .as_noarg = {BC_IADD} },
//     { .as_noarg = {BC_IADD} },
//     { .as_arg64 = {BC_PUSH, .arg = 20} },
//     { .as_arg64 = {BC_PUSH, .arg = 23} },
//     { BC_ICMP },
//     { .as_noarg = {BC_IPRINT} },
//     { .as_arg64 = {BC_PUSH, .arg = 19} },
//     { BC_SWAP },
//     { BC_DUP },
//     { BC_IPRINT },
//     { .as_noarg = {BC_STOP} }
// };

const union ins program[] = {
    { BC_IREAD },
    { BC_DUP },
    { .as_arg64 = {BC_PUSH, .arg = 42} },
    { BC_ICMP },
    { .as_arg64 = {BC_JMZ, .arg = 2} },
    { BC_STOP },
    { .as_arg64 = {BC_PUSH, .arg = 2} },
    { BC_IADD },
    { BC_DUP },
    { BC_DUP },
    { BC_IPRINT },
    { .as_arg64 = {BC_PUSH, .arg = 42} },
    { BC_ICMP },
    { .as_arg64 = {BC_JMZ, .arg = -7} },
    { BC_STOP }
};

int main() {
    size_t size = sizeof(program) / sizeof(program[0]);
    struct vm_state state = state_create(program, size);
    interpret(&state);
    state_destroy(&state);
    return 0;
}

