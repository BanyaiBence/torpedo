//
// Created by bence on 2025. 05. 24..
//
#include <stdio.h>
#include "table.h"

#include <string.h>
#include <stdlib.h>
#include "common.h"


inline bool table_init(table *t) {
    t->size = TABLE_SIZE;
    memset(t->tiles, EMPTY, sizeof(t->tiles));

    return true;
}

inline bool table_print(table *t) {
    // Header
    printf("  ");
    for (int i = 0; i < t->size; i++) {
        const int num_of_spaces = (i < 9) ? 2 : 1; // For single digit numbers

        printf("%d", i + 1);

        for (int j = 0; j < num_of_spaces; j++)
            printf(" ");
    }
    printf("\n");

    // Tiles
    for (int i = 0; i < t->size; i++) {
        printf("%c  ", 65 + i); // Row numbers
        for (int j = 0; j < t->size; j++) {
            printf("%c  ", t->tiles[i * t->size + j]);
        }
        printf("\n");
    }
    return true;
}

inline bool table_set_tile(table *t, unsigned int x, unsigned int y, tile value) {
    if (x >= t->size || y >= t->size) {
        return false; // Out of bounds
    }
    t->tiles[y * t->size + x] = value;
    return true;
}

inline tile table_get_tile(table *t, unsigned int x, unsigned int y) {
    if (x >= t->size || y >= t->size) {
        perror("Error: Coordinates out of bounds");
        return EMPTY; // Out of bounds, return default tile
    }
    return t->tiles[y * t->size + x];
}

inline bool table_set_ship(table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal) {
    if (horizontal) {
        if (x + ship_size > t->size || y >= t->size) {
            return false; // Out of bounds
        }
        for (size_t i = 0; i < ship_size; i++)
            if ((char)table_get_tile(t, x + i, y) != (char)EMPTY)
                return false; // Overlaps with existing ship

        for (size_t i = 0; i < ship_size; i++)
            table_set_tile(t, x + i, y, SHIP);

        return true;
    }
    if (x >= t->size || y + ship_size > t->size) {
        return false; // Out of bounds
    }
    for (size_t i = 0; i < ship_size; i++)
        if ((char)table_get_tile(t, x, y + i) != (char)EMPTY) {
            return false; // Overlaps with existing ship
        }

    for (size_t i = 0; i < ship_size; i++)
        table_set_tile(t, x, y + i, SHIP);

    return true;
}

inline bool table_generate_random(table *t) {
    const unsigned int ships[] = {5, 4, 4, 3, 3, 2, 2, 1, 1};

    FOREACH(unsigned int ship_size, ships) {
        unsigned x, y, horizontal;
        do {
            x = rand() % t->size;
            y = rand() % t->size;
            horizontal = (rand() % 2);
        } while (!table_set_ship(t, x, y, ship_size, horizontal));
    }
    return true;
}
