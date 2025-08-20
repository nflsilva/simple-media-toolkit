#ifndef _SMT_UTILS_H
#define _SMT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 *  Semantic sugar for the number `1`.
 */
#define SMT_TRUE 1
/*
 *  Semantic sugar for the number `0`.
 */
#define SMT_FALSE 0
/*
 *  Semantic sugar for the number `1`.
 */
#define SMT_SUCCESS 1
/*
 *  Semantic sugar for the number `0`.
 */
#define SMT_FAILURE 0

#define ASSERT_MSG(expr, msg) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\nMessage: %s\nFile: %s, Line: %d\n", #expr, msg, __FILE__, __LINE__); \
            assert(expr); \
        } \
    } while (0)
#endif