#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Macro helpers
#define ARRAY_COMB(pre, word) __ARRAY_COMB(pre, word)
#define __ARRAY_COMB(pre, word) pre##word

#endif // ARRAY_H

// Configuration defaults
#ifndef ARRAY_T
#define ARRAY_T int
#endif

#ifndef ARRAY_T_PRINT_FORMAT
#define ARRAY_T_PRINT_FORMAT "%d"
#endif

#ifndef ARRAY_T_DEFAULT
#define ARRAY_T_DEFAULT 0
#endif

// Derived settings
#ifndef ARRAY_NAME
#define ARRAY_NAME ARRAY_COMB(Array_, ARRAY_T)
#endif
#define ARRAY_PREFIX ARRAY_COMB(ARRAY_NAME, _)
#define ARRAY_IMPL(word) ARRAY_COMB(ARRAY_PREFIX, word)

// Struct definition
typedef struct ARRAY_NAME ARRAY_NAME;

struct ARRAY_NAME {
    bool is_initialized;
    ARRAY_T *items;
    size_t count;
    size_t capacity;

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

    // New: optional element destructor
    void (*destroy_element)(ARRAY_T item);
};

// Function implementations
#define ARRAY_expand ARRAY_IMPL(expand)
static void ARRAY_expand(ARRAY_NAME *array, size_t new_capacity) {
    if (!array->is_initialized) return;
    size_t old_cap = array->capacity;
    size_t new_cap = new_capacity > old_cap ? new_capacity : old_cap;
    array->items = realloc(array->items, new_cap * sizeof(ARRAY_T));
    array->capacity = new_cap;
}

#define ARRAY_shrink ARRAY_IMPL(shrink)
static void ARRAY_shrink(ARRAY_NAME *array) {
    if (array->count < array->capacity / 4 && array->capacity > 4) {
        size_t new_cap = array->capacity / 2;
        array->items = realloc(array->items, new_cap * sizeof(ARRAY_T));
        array->capacity = new_cap;
    }
}

#define ARRAY_push ARRAY_IMPL(push)
static void ARRAY_push(ARRAY_NAME *array, ARRAY_T item) {
    if (!array->is_initialized) return;
    if (array->count >= array->capacity) {
        size_t new_cap = array->capacity == 0 ? 4 : array->capacity * 2;
        array->expand(array, new_cap);
    }
    array->items[array->count++] = item;
}

#define ARRAY_pop ARRAY_IMPL(pop)
static void ARRAY_pop(ARRAY_NAME *array) {
    if (array->count > 0) {
        if (array->destroy_element) {
            array->destroy_element(array->items[array->count - 1]);
        }
        array->count--;
        array->shrink(array);
    }
}

#define ARRAY_get ARRAY_IMPL(get)
static ARRAY_T ARRAY_get(ARRAY_NAME *array, size_t index) {
    if (!array->is_initialized || index >= array->count)
        return ARRAY_T_DEFAULT;
    return array->items[index];
}

#define ARRAY_set ARRAY_IMPL(set)
static void ARRAY_set(ARRAY_NAME *array, size_t index, ARRAY_T item) {
    if (!array->is_initialized) return;
    if (index < array->count) {
        if (array->destroy_element) array->destroy_element(array->items[index]);
        array->items[index] = item;
    } else if (index == array->count) {
        ARRAY_push(array, item);
    } else {
        fprintf(stderr, "Index out of bounds: %zu\n", index);
    }
}

#define ARRAY_clear ARRAY_IMPL(clear)
static void ARRAY_clear(ARRAY_NAME *array) {
    if (!array->is_initialized) return;
    if (array->destroy_element) {
        for (size_t i = 0; i < array->count; ++i) {
            array->destroy_element(array->items[i]);
        }
    }
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}

#define ARRAY_destroy ARRAY_IMPL(destroy)
static void ARRAY_destroy(ARRAY_NAME *array) {
    if (!array->is_initialized) return;
    if (array->destroy_element) {
        for (size_t i = 0; i < array->count; ++i) {
            array->destroy_element(array->items[i]);
        }
    }
    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
    array->is_initialized = false;
}

#define ARRAY_sort ARRAY_IMPL(sort)
static void ARRAY_sort(ARRAY_NAME *array) {
    if (!array->is_initialized || array->count < 2) return;
    for (size_t i = 0; i < array->count - 1; ++i) {
        for (size_t j = 0; j < array->count - i - 1; ++j) {
            if (array->items[j] > array->items[j + 1]) {
                ARRAY_T tmp = array->items[j];
                array->items[j] = array->items[j + 1];
                array->items[j + 1] = tmp;
            }
        }
    }
}

#define ARRAY_print ARRAY_IMPL(print)
static void ARRAY_print(ARRAY_NAME *array) {
    if (!array->is_initialized) return;
    printf("[");
    for (size_t i = 0; i < array->count; ++i) {
        printf(ARRAY_T_PRINT_FORMAT, array->items[i]);
        if (i + 1 < array->count) printf(", ");
    }
    printf("]\n");
}

#define ARRAY_foreach(array, item) \
    for (size_t i = 0; i < array->count; ++i) { \
        ARRAY_T item = array->items[i]; \
        if (item != ARRAY_T_DEFAULT)

#define ARRAY_init ARRAY_IMPL(init)
static void ARRAY_init(ARRAY_NAME *array) {
    array->is_initialized = true;
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
    array->destroy_element = NULL;

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

#define ARRAY_init_with_destroy ARRAY_IMPL(init_with_destroy)
static void ARRAY_init_with_destroy(ARRAY_NAME *array, void (*destroy_element)(ARRAY_T)) {
    ARRAY_init(array);
    array->destroy_element = destroy_element;
}

// Cleanup macros
#undef ARRAY_T
#undef ARRAY_T_PRINT_FORMAT
#undef ARRAY_T_DEFAULT
#undef ARRAY_NAME
#undef ARRAY_PREFIX
#undef ARRAY_IMPL
#undef ARRAY_push
