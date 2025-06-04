//
// Created by bence on 2025. 06. 03..
//

#ifndef BOX_H
#define BOX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_COMB(pre, word) __ARRAY_COMB(pre, word)
#define __ARRAY_COMB(pre, word) pre##word

#endif //BOX_H


// NOTE: this section is *not* guarded as it is intended to be included multiple times.
#ifndef BOX_T
    #define BOX_T int // Default type is int, can be overridden by defining BOX_T before including this header.
#endif
// I want to store my primitives on the heap, so I need to define a default value for the box type.

#define BOX_NAME ARRAY_COMB(ARRAY_COMB(Box, _), BOX_T)

#define BOX_PREFIX ARRAY_COMB(BOX_NAME, _)

#define BOX_IMPL(word) ARRAY_COMB(BOX_PREFIX, word)

typedef struct BOX_NAME BOX_NAME;

struct BOX_NAME {
    BOX_T *value; // Pointer to the box value
    bool is_initialized; // Flag to check if the value is initialized

    void (*set)(BOX_NAME *b, BOX_T value);
    void (*free)(BOX_NAME *b);
    BOX_T (*unwrap)(const BOX_NAME *b);
    void (*try_unwrap)(const BOX_NAME *b, BOX_T *value);
    void (*clone)(BOX_NAME *dst, const BOX_NAME *src);
};
#define BOX_set BOX_IMPL(set)
static void BOX_set(BOX_NAME *b, BOX_T value) {
    if (!b->is_initialized) {
        b->value = malloc(sizeof(BOX_T));
        if (!b->value) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        b->is_initialized = true;
    }
    *(b->value) = value;
}
#define BOX_free BOX_IMPL(free)
static void BOX_free(BOX_NAME *b) {
    if (b->is_initialized) {
        free(b->value);
        b->is_initialized = false;
    }
}
#define BOX_unwrap BOX_IMPL(unwrap)
static BOX_T BOX_unwrap(const BOX_NAME *b) {
    if (!b->is_initialized) {
        fprintf(stderr, "Error: Attempted to unwrap uninitialized Box.\n");
        exit(EXIT_FAILURE);
    }
    return *(b->value);
}

#define BOX_try_unwrap BOX_IMPL(try_unwrap)
static void BOX_try_unwrap(const BOX_NAME *b, BOX_T *value) {
    if (b->is_initialized && b->value != NULL) {
        *value = *(b->value);
    }
}



#define BOX_init BOX_IMPL(init)
static void BOX_init(BOX_NAME *b) {
    b->value = NULL;
    b->is_initialized = false;
    b->set = BOX_set;
    b->free = BOX_free;
    b->unwrap = BOX_unwrap;
    b->try_unwrap = BOX_try_unwrap;

}

#define BOX_clone BOX_IMPL(clone)
static void BOX_clone(BOX_NAME *dst, const BOX_NAME *src) {
    if (!src->is_initialized) {
        fprintf(stderr, "Error: Attempted to clone uninitialized Box.\n");
        exit(EXIT_FAILURE);
    }
    BOX_init(dst);
    dst->set(dst, src->unwrap(src));
}

#define BOX_init_and_set BOX_IMPL(init_and_set)
static void BOX_init_and_set(BOX_NAME *b, BOX_T value) {
    BOX_init(b);
    b->set(b, value);
}




#undef BOX_T
#undef BOX_NAME
#undef BOX_PREFIX
#undef BOX_IMPL

