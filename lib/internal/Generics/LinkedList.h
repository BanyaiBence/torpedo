//
// Created by bence on 2025. 06. 11..
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Objects/Object.h"

#define ARRAY_COMB(pre, word) __ARRAY_COMB(pre, word)
#define __ARRAY_COMB(pre, word) pre##word

#endif //LINKEDLIST_H

#ifndef LINKEDLIST_T
    #define LINKEDLIST_T int // Default type is int, can be overridden by defining LINKEDLIST_T before including this header.
 #endif

#define LINKEDLIST_NAME ARRAY_COMB(ARRAY_COMB(LinkedList, _), LINKEDLIST_T)

#define LINKEDLIST_PREFIX ARRAY_COMB(LINKEDLIST_NAME, _)

#define LINKEDLIST_IMPL(word) ARRAY_COMB(LINKEDLIST_PREFIX, word)

typedef struct LINKEDLIST_NAME LINKEDLIST_NAME;

class (LINKEDLIST_NAME, Object)
    LINKEDLIST_T value;
    struct LINKEDLIST_NAME *next;
    struct LINKEDLIST_NAME *prev;

    void (*insert)(LINKEDLIST_NAME *node, LINKEDLIST_T value, size_t idx);
    void (*remove)(LINKEDLIST_NAME *node, size_t idx);
    void (*add)(LINKEDLIST_NAME *node, LINKEDLIST_T value);
    LINKEDLIST_T (*get_first)(const LINKEDLIST_NAME *node);
    LINKEDLIST_T (*get_last)(const LINKEDLIST_NAME *node);
    LINKEDLIST_T (*get)(const LINKEDLIST_NAME *node, size_t idx);
    void (*set)(LINKEDLIST_NAME *node, LINKEDLIST_T value, size_t idx);
    void (*set_first)(LINKEDLIST_NAME *node, LINKEDLIST_T value);
    void (*set_last)(LINKEDLIST_NAME *node, LINKEDLIST_T value);
    size_t (*size)(const LINKEDLIST_NAME *node);
    bool (*is_empty)(const LINKEDLIST_NAME *node);
    void (*clear)(LINKEDLIST_NAME *node);
    bool (*contains)(const LINKEDLIST_NAME *node, LINKEDLIST_T value);
    size_t(*index_of)(const LINKEDLIST_NAME *node, LINKEDLIST_T value);
    size_t(*count)(const LINKEDLIST_NAME *node, LINKEDLIST_T value);
    void (*destroy)(LINKEDLIST_NAME *node);
    void (*reverse)(LINKEDLIST_NAME *node);
endclass(LINKEDLIST_NAME, Object);

#define LINKEDLIST_insert LINKEDLIST_IMPL(insert)
static void LINKEDLIST_insert(LINKEDLIST_NAME *node, LINKEDLIST_T value, size_t idx) {
    if (idx == 0) {
        node->set_first(node, value);
        return;
    }
    if (idx >= node->size(node)) {
        node->add(node, value);
        return;
    }

    LINKEDLIST_NAME *new_node = malloc(sizeof(LINKEDLIST_NAME));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;

    LINKEDLIST_NAME *current = node;
    for (size_t i = 0; i < idx && current->next != NULL; i++) {
        current = current->next;
    }

    new_node->next = current->next;
    new_node->prev = current;

    if (current->next != NULL) {
        current->next->prev = new_node;
    }

    current->next = new_node;
}

#define LINKEDLIST_remove LINKEDLIST_IMPL(remove)
static void LINKEDLIST_remove(LINKEDLIST_NAME *node, size_t idx) {
    if (idx == 0) {
        node->set_first(node, node->next ? node->next->value : 0);
        return;
    }
    if (idx >= node->size(node)) {
        return; // Out of bounds
    }

    LINKEDLIST_NAME *current = node;
    for (size_t i = 0; i < idx && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return; // Out of bounds
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
}

#define LINKEDLIST_add LINKEDLIST_IMPL(add)
static void LINKEDLIST_add(LINKEDLIST_NAME *node, LINKEDLIST_T value) {
    LINKEDLIST_NAME *new_node = malloc(sizeof(LINKEDLIST_NAME));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;

    if (node->is_empty(node)) {
        node->next = new_node;
        new_node->prev = node;
    } else {
        LINKEDLIST_NAME *last = node;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;
    }
}

#define LINKEDLIST_get_first LINKEDLIST_IMPL(get_first)
static LINKEDLIST_T LINKEDLIST_get_first(const LINKEDLIST_NAME *node) {
    if (node->is_empty(node)) {
        fprintf(stderr, "Error: Attempted to get first element from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    return node->next->value;
}

#define LINKEDLIST_get_last LINKEDLIST_IMPL(get_last)
static LINKEDLIST_T LINKEDLIST_get_last(const LINKEDLIST_NAME *node) {
    if (node->is_empty(node)) {
        fprintf(stderr, "Error: Attempted to get last element from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    LINKEDLIST_NAME *current = node;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->value;
}
#define LINKEDLIST_get LINKEDLIST_IMPL(get)
static LINKEDLIST_T LINKEDLIST_get(const LINKEDLIST_NAME *node, size_t idx) {
    if (idx >= node->size(node)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    LINKEDLIST_NAME *current = node;
    for (size_t i = 0; i < idx && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return current->value;
}

#define LINKEDLIST_set LINKEDLIST_IMPL(set)
static void LINKEDLIST_set(LINKEDLIST_NAME *node, LINKEDLIST_T value, size_t idx) {
    if (idx >= node->size(node)) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    LINKEDLIST_NAME *current = node;
    for (size_t i = 0; i < idx && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    current->value = value;
}

#define LINKEDLIST_set_first LINKEDLIST_IMPL(set_first)
static void LINKEDLIST_set_first(LINKEDLIST_NAME *node, LINKEDLIST_T value) {
    if (node->is_empty(node)) {
        fprintf(stderr, "Error: Attempted to set first element in an empty list.\n");
        exit(EXIT_FAILURE);
    }
    node->next->value = value;
}

#define LINKEDLIST_set_last LINKEDLIST_IMPL(set_last)
static void LINKEDLIST_set_last(LINKEDLIST_NAME *node, LINKEDLIST_T value) {
    if (node->is_empty(node)) {
        fprintf(stderr, "Error: Attempted to set last element in an empty list.\n");
        exit(EXIT_FAILURE);
    }
    LINKEDLIST_NAME *current = node;
    while (current->next != NULL) {
        current = current->next;
    }
    current->value = value;
}

#define LINKEDLIST_size LINKEDLIST_IMPL(size)
static size_t LINKEDLIST_size(const LINKEDLIST_NAME *node) {
    size_t count = 0;
    const LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

#define LINKEDLIST_is_empty LINKEDLIST_IMPL(is_empty)
static bool LINKEDLIST_is_empty(const LINKEDLIST_NAME *node) {
    return node->next == NULL; // If next is NULL, the list is empty
}

#define LINKEDLIST_clear LINKEDLIST_IMPL(clear)
static void LINKEDLIST_clear(LINKEDLIST_NAME *node) {
    LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        LINKEDLIST_NAME *next_node = current->next;
        free(current);
        current = next_node;
    }
    node->next = NULL;
}

#define LINKEDLIST_contains LINKEDLIST_IMPL(contains)
static bool LINKEDLIST_contains(const LINKEDLIST_NAME *node, const LINKEDLIST_T value) {
    const LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        if (current->value == value) {
            return true; // Found the value
        }
        current = current->next;
    }
    return false; // Value not found
}
#define LINKEDLIST_index_of LINKEDLIST_IMPL(index_of)
static size_t LINKEDLIST_index_of(const LINKEDLIST_NAME *node, LINKEDLIST_T value) {
    size_t index = 0;
    const LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        if (current->value == value) {
            return index; // Found the value
        }
        current = current->next;
        index++;
    }
    return -1; // Value not found
}
#define LINKEDLIST_count LINKEDLIST_IMPL(count)
static size_t LINKEDLIST_count(const LINKEDLIST_NAME *node, LINKEDLIST_T value) {
    size_t count = 0;
    const LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        if (current->value == value) {
            count++; // Increment count for each occurrence of the value
        }
        current = current->next;
    }
    return count; // Return the total count of occurrences
}
#define LINKEDLIST_destroy LINKEDLIST_IMPL(destroy)
static void LINKEDLIST_destroy(LINKEDLIST_NAME *node) {
    LINKEDLIST_clear(node); // Clear the list first
    free(node); // Then free the node itself
}

#define LINKEDLIST_reverse LINKEDLIST_IMPL(reverse)
static void LINKEDLIST_reverse(LINKEDLIST_NAME *node) {
    LINKEDLIST_NAME *current = node->next; // Start from the first element
    LINKEDLIST_NAME *prev = NULL;
    LINKEDLIST_NAME *next = NULL;

    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse the link
        current->prev = next; // Set previous link
        prev = current; // Move prev to current
        current = next; // Move to next node
    }
    node->next = prev; // Update head to new first element
}

#define LINKEDLIST_print LINKEDLIST_IMPL(print)
static void LINKEDLIST_print(LINKEDLIST_NAME *node) {
    const LINKEDLIST_NAME *current = node->next; // Start from the first element
    while (current != NULL) {
        printf("[%d]->", current->value); // Assuming LINKEDLIST_T is int
        current = current->next;
    }
    printf("\n");
}

#define LINKEDLIST_init LINKEDLIST_IMPL(init)
static void LINKEDLIST_init(LINKEDLIST_NAME *node) {
    node->next = NULL; // Initialize the list as empty
    node->prev = NULL; // No previous node for the head
    node->insert = LINKEDLIST_insert;
    node->remove = LINKEDLIST_remove;
    node->add = LINKEDLIST_add;
    node->get_first = LINKEDLIST_get_first;
    node->get_last = LINKEDLIST_get_last;
    node->get = LINKEDLIST_get;
    node->set = LINKEDLIST_set;
    node->set_first = LINKEDLIST_set_first;
    node->set_last = LINKEDLIST_set_last;
    node->size = LINKEDLIST_size;
    node->is_empty = LINKEDLIST_is_empty;
    node->clear = LINKEDLIST_clear;
    node->contains = LINKEDLIST_contains;
    node->index_of = LINKEDLIST_index_of;
    node->destroy = LINKEDLIST_destroy;
    node->reverse = LINKEDLIST_reverse;
    node->print = LINKEDLIST_print;
    node->count = LINKEDLIST_count;
}

#undef LINKEDLIST_T
#undef LINKEDLIST_NAME
#undef LINKEDLIST_PREFIX
#undef LINKEDLIST_IMPL