//
// Created by User on 2025. 05. 24..
//

#include <stdio.h>
#include "table.h"

#include <string.h>

inline bool table_init(table *t) {
    t->size = TABLE_SIZE;
    memset(t->tiles, EMPTY, sizeof(t->tiles));
    return true;
}

inline bool table_print(table *t) {
    printf("  ");
    for (int i = 0; i < t->size; i++) {
        const int num_of_spaces = (i < 9) ? 2 : 1;

        printf("%d", i + 1);

        for (int j = 0; j < num_of_spaces; j++) {
            printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i < t->size; i++) {
        printf("%c ", 65+i);
        for (int j = 0; j < t->size; j++) {
            printf("%c  ", t->tiles[i * t->size + j]);
        }
        printf("\n");
    }
    return true;
}

inline bool table_set_tile(table *t, int x, int y, tile value) {
    if (x < 0 || x >= t->size || y < 0 || y >= t->size) {
        perror("Error: Coordinates out of bounds");
        return false;
    }
    t->tiles[y * t->size + x] = value;
    return true;
}

inline tile table_get_tile(table *t, int x, int y) {
    if (x < 0 || x >= t->size || y < 0 || y >= t->size) {
        perror("Error: Coordinates out of bounds");
        return EMPTY;
    }
    return t->tiles[y * t->size + x];
}

inline bool table_set_ship(table *t, int x, int y, int ship_size, bool horizontal) {
    if (horizontal) {
        if (x < 0 || x + ship_size > t->size || y < 0 || y >= t->size) {
            perror("Error: Ship placement out of bounds");
            return false; // Out of bounds
        }
        for (int i = 0; i < ship_size; i++)
            if (table_get_tile(t, x + i, y) != EMPTY) {
                perror("Error: Ship placement overlaps with existing ship");
                return false; // Overlaps with existing ship
            }

        for (int i = 0; i < ship_size; i++)
            table_set_tile(t, x + i, y, SHIP);

        return true;
    }
    if (x < 0 || x >= t->size || y < 0 || y + ship_size > t->size) {
        perror("Error: Ship placement out of bounds");
        return false; // Out of bounds
    }
    for (int i = 0; i < ship_size; i++)
        if (table_get_tile(t, x, y + i) != EMPTY) {
            perror("Error: Ship placement overlaps with existing ship");
            return false; // Overlaps with existing ship
        }

    for (int i = 0; i < ship_size; i++)
        table_set_tile(t, x, y + i, SHIP);

    return true;
}
