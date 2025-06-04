//
// Created by bence on 2025. 06. 03..
//

#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define ARRAY_COMB(pre, word) __ARRAY_COMB(pre, word)
#define __ARRAY_COMB(pre, word) pre##word

#endif

// NOTE: this section is *not* guarded as it is intended to be included multiple times.
#ifndef ARRAY_T_DEFAULT
#define ARRAY_T_DEFAULT 0
#endif
#ifndef ARRAY_T_PRINT_FORMAT
#define ARRAY_T_PRINT_FORMAT "%d" // Default format for printing, can be overridden by defining ARRAY_T_PRINT_FORMAT before including this header.


#endif

#ifdef ARRAY_T
    #define ARRAY_T_HAS_DEFAULT 0
    #define ARRAY_T_ORDERABLE 0
    #define ARRAY_T_COMPARABLE 0
#else
#define ARRAY_T int // Default type is int, can be overridden by defining ARRAY_T before including this header.

#define ORDER_ARRAY_T(a, b) ((a) > (b))
#define COMPARE_ARRAY_T(a, b) ((a) == (b))
#endif

#ifdef ARRAY_T_DEFAULT
#define ARRAY_T_HAS_DEFAULT 1
#endif

#ifdef ORDER_ARRAY_T
#define ARRAY_T_ORDERABLE 1
#endif

#ifdef COMPARE_ARRAY_T
#define ARRAY_T_COMPARABLE 1
#endif


// The name of the data type to be generated.
#define ARRAY_NAME ARRAY_COMB(ARRAY_COMB(Array,_), ARRAY_T)

// Prefix for generated functions.
#define ARRAY_PREFIX ARRAY_COMB(ARRAY_NAME, _)


#define ARRAY_IMPL(word) ARRAY_COMB(ARRAY_PREFIX, word)

typedef struct ARRAY_NAME ARRAY_NAME;

struct ARRAY_NAME {
    bool is_initialized;
    ARRAY_T *items;
    size_t count;
    size_t capacity;

    // Function pointers for operations on the array
    void (*push)(ARRAY_NAME *array, ARRAY_T item);

    void (*pop)(ARRAY_NAME *array);

    ARRAY_T (*get)(ARRAY_NAME *array, size_t index);

    void (*set)(ARRAY_NAME *array, size_t index, ARRAY_T item);

    void (*clear)(ARRAY_NAME *array);

    void (*destroy)(ARRAY_NAME *array);

    void (*expand)(ARRAY_NAME *array, size_t new_capacity);

    void (*shrink)(ARRAY_NAME *array);

    void (*sort)(ARRAY_NAME *array);

    void (*print)(ARRAY_NAME *array);
};


#define ARRAY_expand ARRAY_IMPL(expand)

static void ARRAY_expand(ARRAY_NAME *array, size_t new_capacity) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    size_t old_cap = array->capacity;
    size_t new_cap = new_capacity > old_cap ? new_capacity : old_cap;
    size_t new_size = new_cap * sizeof(ARRAY_T);
    array->items = realloc(array->items, new_size);
    array->capacity = new_cap;
}

#define ARRAY_shrink ARRAY_IMPL(shrink)

static void ARRAY_shrink(ARRAY_NAME *array) {
    if (array->count < array->capacity / 4 && array->capacity > 4) {
        size_t new_cap = array->capacity / 2;
        size_t new_size = new_cap * sizeof(ARRAY_T);
        array->items = realloc(array->items, new_size);
        array->capacity = new_cap;
    }
}

#define ARRAY_push ARRAY_IMPL(push)

static void ARRAY_push(ARRAY_NAME *array, ARRAY_T item) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    if (array->count >= array->capacity) {
        size_t new_cap = array->capacity == 0 ? 4 : array->capacity * 2; // Start with 4 if empty
        array->expand(array, new_cap);
    }
    array->items[array->count++] = item;
}

#define ARRAY_pop ARRAY_IMPL(pop)

static void ARRAY_pop(ARRAY_NAME *array) {
    if (array->count > 0) {
        array->count--;
    }
    array->shrink(array);
}

#define ARRAY_get ARRAY_IMPL(get)

static ARRAY_T ARRAY_get(ARRAY_NAME *array, size_t index) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return ARRAY_T_DEFAULT; // Return default value if defined
    }
    if (index < array->count) {
        return array->items[index];
    }
    if (ARRAY_T_HAS_DEFAULT) {
        return ARRAY_T_DEFAULT; // Return default value if defined
    }
}

#define ARRAY_set ARRAY_IMPL(set)

static void ARRAY_set(ARRAY_NAME *array, size_t index, ARRAY_T item) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    if (index < array->count) {
        array->items[index] = item;
    } else if (index == array->count) {
        ARRAY_push(array, item);
    } else {
        // Handle out-of-bounds index
        fprintf(stderr, "Index out of bounds: %zu\n", index);
    }
}

#define ARRAY_clear ARRAY_IMPL(clear)

static void ARRAY_clear(ARRAY_NAME *array) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}

#define ARRAY_destroy ARRAY_IMPL(destroy)

static void ARRAY_destroy(ARRAY_NAME *array) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    if (array->items) {
        free(array->items);
        array->items = NULL;
    }
    array->count = 0;
    array->capacity = 0;
}

#define ARRAY_sort ARRAY_IMPL(sort)

static void ARRAY_sort(ARRAY_NAME *array) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    if (array->count == 0) return; // Nothing to sort

    if (ARRAY_T_ORDERABLE) {
        // Simple bubble sort implementation, can be replaced with a more efficient algorithm if needed.
        for (size_t i = 0; i < array->count - 1; i++) {
            for (size_t j = 0; j < array->count - i - 1; j++) {
                if (ORDER_ARRAY_T(array->items[j], array->items[j + 1])) {
                    ARRAY_T temp = array->items[j];
                    array->items[j] = array->items[j + 1];
                    array->items[j + 1] = temp;
                }
            }
        }
    } else {
        fprintf(stderr, "Array type is not orderable.\n");
    }
}

#define ARRAY_print ARRAY_IMPL(print)

static void ARRAY_print(ARRAY_NAME *array) {
    if (!array->is_initialized) {
        fprintf(stderr, "Array not initialized.\n");
        return;
    }
    if (array->count == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (size_t i = 0; i < array->count; i++) {
        printf(ARRAY_T_PRINT_FORMAT, array->items[i]);
        if (i < array->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

#define ARRAY_init ARRAY_IMPL(init)

static void ARRAY_init(ARRAY_NAME *array) {
    array->is_initialized = true;
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
    array->push = ARRAY_push;
    array->pop = ARRAY_pop;
    array->get = ARRAY_get;
    array->set = ARRAY_set;
    array->clear = ARRAY_clear;
    array->destroy = ARRAY_destroy;
    array->expand = ARRAY_expand;
    array->shrink = ARRAY_shrink;
    array->sort = ARRAY_sort;
    array->print = ARRAY_print;
}


// Cleanup
// These need to be undefined so they can be redefined the
// next time you need to instantiate this template.
#undef ARRAY_T
#undef ARRAY_PREFIX
#undef ARRAY_NAME
#undef ARRAY_IMPL

#ifdef ARRAY_T_DEFAULT
#undef ARRAY_T_DEFAULT
#endif

#ifdef ARRAY_T_ORD
    #undef ARRAY_T_ORD
#endif

#ifdef ORDER_ARRAY_T
#undef ORDER_ARRAY_T
#endif

#ifdef COMPARE_ARRAY_T
#undef COMPARE_ARRAY_T
#endif

#ifndef ARRAY_T_ORDERABLE
    #undef ARRAY_T_ORDERABLE
#endif

#ifndef ARRAY_T_COMPARABLE
    #undef ARRAY_T_COMPARABLE
#endif

#undef ARRAY_push
