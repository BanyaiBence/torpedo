//
// Created by bence on 2025. 05. 24..
//

#ifndef TABLE_H
#define TABLE_H

#define TABLE_SIZE 20
#define TILE_SIZE 20

#include <stdbool.h>

typedef enum {
    EMPTY = '~',
    SHIP = 'O',
    HIT = 'X',
    MISS = '*'
} tile;

typedef struct {
    int size;
    tile tiles[TABLE_SIZE * TABLE_SIZE];
} table;

typedef struct {
    int x;
    int y;
} pos;


bool table_init(table *t);

bool table_print(table *t);

bool table_set_tile(table *t, unsigned int x, unsigned int y, tile value);

tile table_get_tile(table *t, unsigned int x, unsigned int y);

bool table_set_ship(table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal);

bool table_generate_random(table *t);



#endif //TABLE_H
