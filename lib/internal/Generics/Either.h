//
// Created by bence on 2025. 06. 03..
//

#ifndef EITHER_H
#define EITHER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define BOX_T int
#include "./Box.h"
#define BOX_T double
#include "./Box.h"
#define ARRAY_COMB(pre, word) __ARRAY_COMB(pre, word)
#define __ARRAY_COMB(pre, word) pre##word

#endif //EITHER_H

// NOTE: this section is *not* guarded as it is intended to be included multiple times.
#ifndef EITHER_T_RIGHT_DEFAULT
    #define EITHER_T_RIGHT_DEFAULT 0
#endif

#ifndef EITHER_T_LEFT_DEFAULT
    #define EITHER_T_LEFT_DEFAULT 0
#endif

#ifndef EITHER_T_LEFT
    #define EITHER_T_LEFT int // Default left type is int, can be overridden by defining EITHER_T_LEFT before including this header.
#endif
#ifndef EITHER_T_RIGHT
    #define EITHER_T_RIGHT double // Default right type is double, can be overridden by defining EITHER_T_RIGHT before including this header.
#endif
#ifdef EITHER_T_RIGHT_DEFAULT
    #define EITHER_T_RIGHT_HAS_DEFAULT 1
#endif
#ifdef EITHER_T_LEFT_DEFAULT
    #define EITHER_T_LEFT_HAS_DEFAULT 1
#endif

#define EITHER_NAME ARRAY_COMB(ARRAY_COMB(ARRAY_COMB(ARRAY_COMB(Either, _), EITHER_T_LEFT), _), EITHER_T_RIGHT)

#define EITHER_PREFIX ARRAY_COMB(EITHER_NAME, _)

#define EITHER_IMPL(word) ARRAY_COMB(EITHER_PREFIX, word)

typedef struct EITHER_NAME EITHER_NAME;

struct EITHER_NAME {
    int _is_left; // 1 if left, 0 if right
    union {
        EITHER_T_LEFT left;
        EITHER_T_RIGHT right;
    } value;

    void (*set_left)(EITHER_NAME *e, EITHER_T_LEFT value);
    void (*set_right)(EITHER_NAME *e, EITHER_T_RIGHT value);
    EITHER_T_LEFT (*get_left)(const EITHER_NAME *e);
    EITHER_T_RIGHT (*get_right)(const EITHER_NAME *e);
    void (*unwrap)(const EITHER_NAME *e, EITHER_T_LEFT *left, EITHER_T_RIGHT *right);
    bool (*is_left)(const EITHER_NAME *e);
    bool (*is_right)(const EITHER_NAME *e);
    void (*free)(EITHER_NAME *e);
    void (*clone)(EITHER_NAME *dst, const EITHER_NAME *src);
};

#define EITHER_set_left EITHER_IMPL(set_left)
static void EITHER_set_left(EITHER_NAME *e, EITHER_T_LEFT value) {
    e->_is_left = 1;
    e->value.left = value;
}
#define EITHER_set_right EITHER_IMPL(set_right)
static void EITHER_set_right(EITHER_NAME *e, EITHER_T_RIGHT value) {
    e->_is_left = 0;
    e->value.right = value;
}
#define EITHER_get_left EITHER_IMPL(get_left)
static EITHER_T_LEFT EITHER_get_left(const EITHER_NAME *e) {
    if (e->_is_left) {
        return e->value.left;
    }
    fprintf(stderr, "Error: Attempted to get left value from a right Either.\n");
    exit(EXIT_FAILURE);
}
#define EITHER_get_right EITHER_IMPL(get_right)
static EITHER_T_RIGHT EITHER_get_right(const EITHER_NAME *e) {
    if (!e->_is_left) {
        return e->value.right;
    }
    fprintf(stderr, "Error: Attempted to get right value from a left Either.\n");
    exit(EXIT_FAILURE);
}
#define EITHER_unwrap EITHER_IMPL(unwrap)
static void EITHER_unwrap(const EITHER_NAME *e, EITHER_T_LEFT *left, EITHER_T_RIGHT *right) {
    if (e->_is_left) {
        *left = e->value.left;
        *right = 0; // or some default value for right
    } else {
        *left = 0; // or some default value for left
        *right = e->value.right;
    }
}
#define EITHER_is_left EITHER_IMPL(is_left)
static bool EITHER_is_left(const EITHER_NAME *e) {
    return e->_is_left;
}
#define EITHER_is_right EITHER_IMPL(is_right)
static bool EITHER_is_right(const EITHER_NAME *e) {
    return !e->_is_left;
}
#define EITHER_free EITHER_IMPL(free)
static void EITHER_free(EITHER_NAME *e) {
    if (e->is_left) {
        if () {

        }
    } else {
        free(e->value.right); // assuming right is also a pointer
    }
}
#define EITHER_init EITHER_IMPL(init)
static void EITHER_init(EITHER_NAME *e) {
    e->_is_left = 1; // Default to left
    e->value.left = EITHER_T_LEFT_DEFAULT;
    e->set_left = EITHER_set_left;
    e->set_right = EITHER_set_right;
    e->get_left = EITHER_get_left;
    e->get_right = EITHER_get_right;
    e->unwrap = EITHER_unwrap;
    e->is_left = EITHER_is_left;
    e->is_right = EITHER_is_right;
}

#undef EITHER_T_LEFT
#undef EITHER_T_RIGHT
#undef EITHER_NAME
#undef EITHER_PREFIX
#undef EITHER_IMPL
#undef EITHER_T_LEFT_DEFAULT
#undef EITHER_T_RIGHT_DEFAULT
#undef EITHER_T_LEFT_HAS_DEFAULT
#undef EITHER_T_RIGHT_HAS_DEFAULT

