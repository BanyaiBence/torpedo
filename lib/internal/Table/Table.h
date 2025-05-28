//
// Created by bence on 2025. 05. 24..
//

#ifndef TABLE_H
#define TABLE_H

#include "../Graphics/Graphics.h"


#define TABLE_SIZE 20
#define TILE_SIZE 20

typedef enum {
    EMPTY,
    SHIP,
    HIT,
    MISS
} tile;

extern COLOR tile_colors[256]; // assuming char (1 byte)


typedef struct Table Table;
struct Table {
    int size;
    tile tiles[TABLE_SIZE * TABLE_SIZE];
    bool (*print) (struct Table *t);
    bool (*set_tile) (struct Table *t, unsigned int x, unsigned int y, tile value);
    tile (*get_tile) (struct Table *t, unsigned int x, unsigned int y);
    bool (*set_ship) (struct Table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal);
    bool (*generate_random) (struct Table *t);
};

typedef struct {
    int x;
    int y;
} pos;


bool Table_init(Table *t);

bool Table_print(Table *t);

bool Table_set_tile(Table *t, unsigned int x, unsigned int y, tile value);

tile Table_get_tile(Table *t, unsigned int x, unsigned int y);

bool Table_set_ship(Table *t, unsigned int x, unsigned int y, unsigned int ship_size, bool horizontal);

bool Table_generate_random(Table *t);



#endif //TABLE_H
