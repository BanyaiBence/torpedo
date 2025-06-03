//
// Created by bence on 2025. 05. 24..
//
#include <stdio.h>
#include "Table.h"

#include <string.h>
#include <stdlib.h>
#include "../UtilMacros/UtilMacros.h"

COLOR tile_colors[256] = {
    [EMPTY] = COLOR_RGB(0, 0, 255),
    [SHIP] = COLOR_RGB(150, 150, 150),
    [HIT] = COLOR_RGB(0, 255, 0),
    [MISS] = COLOR_RGB(255, 0, 0),
};

inline bool Table_init(Table *t) {
    t->size = TABLE_SIZE;
    memset(t->tiles, EMPTY, sizeof(t->tiles));
    t->set_tile = Table_set_tile;
    t->get_tile = Table_get_tile;
    t->set_ship = Table_set_ship;
    t->generate_random = Table_generate_random;


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

inline bool Table_row_is_empty(Table *t, unsigned int startX, unsigned int startY, unsigned int endX,
                               unsigned int endY) {
    if (startX >= t->size || startY >= t->size || endX >= t->size || endY >= t->size)
        return false; // Out of bounds

    for (unsigned int y = startY; y <= endY; y++)
        for (unsigned int x = startX; x <= endX; x++)
            if (Table_get_tile(t, x, y) != EMPTY)
                return false; // Found a non-empty tile


    return true; // All tiles in the range are empty
}


inline bool Table_set_ship(Table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal) {
    if (horizontal) {
        if (!Table_row_is_empty(t, x, y, x + ship_size - 1, y))
            return false; // Overlaps with existing ship


        for (size_t i = 0; i < ship_size; i++)
            Table_set_tile(t, x + i, y, SHIP);

        return true;
    }

    // Vertical placement

    if (!Table_row_is_empty(t, x, y, x, y + ship_size - 1))
        return false; // Overlaps with existing ship


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
