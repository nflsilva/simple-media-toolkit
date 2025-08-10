#ifndef _SMT_UTILS_H
#define _SMT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ASSERT_MSG(expr, msg) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\nMessage: %s\nFile: %s, Line: %d\n", #expr, msg, __FILE__, __LINE__); \
            assert(expr); \
        } \
    } while (0)
#endif