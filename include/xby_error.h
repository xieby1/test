#ifndef XBY_ERROR_H
#define XBY_ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define assert_msg(cond, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "\033[31mxby_assert failed\033[m @ %s: %s: %d: \n", \
                    __FILE__, __FUNCTION__, __LINE__); \
            fprintf(stderr, __VA_ARGS__); \
            abort(); \
        } \
    } while (0)

#define assert_msg_perror(cond, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "\033[31mxby_assert failed\033[m @ %s: %s: %d: \n", \
                    __FUNCTION__, __FILE__, __LINE__); \
            fprintf(stderr, __VA_ARGS__); \
            perror(" perror"); \
            abort(); \
        } \
    } while (0)

#endif /* XBY_ERROR_H */
