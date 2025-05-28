//
// Created by bence on 2025. 05. 24..
//
#include <stdio.h>
#include "Table.h"

#include <string.h>
#include <stdlib.h>
#include "../common.h"

COLOR tile_colors[256] = {
    [EMPTY] = COLOR_RGB(0, 0, 255),
    [SHIP] = COLOR_RGB(150, 150, 150),
    [HIT] = COLOR_RGB(0, 255, 0),
    [MISS] = COLOR_RGB(255, 0, 0),
};

inline bool Table_init(Table *t) {
    t->size = TABLE_SIZE;
    memset(t->tiles, EMPTY, sizeof(t->tiles));
    t->print = Table_print;
    t->set_tile = Table_set_tile;
    t->get_tile = Table_get_tile;
    t->set_ship = Table_set_ship;
    t->generate_random = Table_generate_random;


    return true;
}

inline bool Table_print(Table *t) {
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

inline bool Table_set_tile(Table *t, unsigned int x, unsigned int y, tile value) {
    if (x >= t->size || y >= t->size) {
        return false; // Out of bounds
    }
    t->tiles[y * t->size + x] = value;
    return true;
}

inline tile Table_get_tile(Table *t, unsigned int x, unsigned int y) {
    if (x >= t->size || y >= t->size) {
        perror("Error: Coordinates out of bounds");
        return EMPTY; // Out of bounds, return default tile
    }
    return t->tiles[y * t->size + x];
}

inline bool Table_set_ship(Table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal) {
    if (horizontal) {
        if (x + ship_size > t->size || y >= t->size) {
            return false; // Out of bounds
        }
        for (size_t i = 0; i < ship_size; i++)
            if ((char) Table_get_tile(t, x + i, y) != (char) EMPTY)
                return false; // Overlaps with existing ship

        for (size_t i = 0; i < ship_size; i++)
            Table_set_tile(t, x + i, y, SHIP);

        return true;
    }
    if (x >= t->size || y + ship_size > t->size) {
        return false; // Out of bounds
    }
    for (size_t i = 0; i < ship_size; i++)
        if ((char) Table_get_tile(t, x, y + i) != (char) EMPTY) {
            return false; // Overlaps with existing ship
        }

    for (size_t i = 0; i < ship_size; i++)
        Table_set_tile(t, x, y + i, SHIP);

    return true;
}

inline bool Table_generate_random(Table *t) {
    const unsigned int ships[] = {5, 4, 4, 3, 3, 2, 2, 1, 1};

    foreach(unsigned int ship_size, ships) {
        unsigned x, y, horizontal;
        do {
            x = rand() % t->size;
            y = rand() % t->size;
            horizontal = (rand() % 2);
        } while (!Table_set_ship(t, x, y, ship_size, horizontal));
    }
    return true;
}


