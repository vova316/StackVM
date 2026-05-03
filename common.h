#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

static inline struct maybe_int64 some_int64(int64_t i) { return (struct maybe_int64){i, true}; }
static inline struct maybe_int64 none_int64() { return (struct maybe_int64){0, false}; }

#endif

