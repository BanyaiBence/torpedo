#include <stdio.h>
#include "lib/internal/Table/Table.h"
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "lib/internal/Common.h"

Table t;
Table t_enemy;
Graphics g;
const COLOR back_color = {.r = 0, .g = 0, .b = 0, .a = 255};
bool mouse_over_window = false;

struct Ship {
    size_t length;
    int x;
    int y;
    bool horizontal;
};

typedef struct Ship Ship;

void init(void) {
    // Seeding random generator
    srand(time(nullptr));


    Table_init(&t);
    Table_init(&t_enemy);
    t_enemy.generate_random(&t_enemy);

    Graphics_init(&g);
    g.create_window(&g, "Battleship", TABLE_SIZE * 2 * TILE_SIZE, TABLE_SIZE * TILE_SIZE);
}

void redraw_table(void) {
    g.fill_window(&g, back_color);
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            tile val = t.get_tile(&t, i, j);
            COLOR tile_color = tile_colors[val];
            g.fill_rect(&g, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE-1, TILE_SIZE-1, tile_color);
            g.draw_rect(&g, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, COLOR_RGB(0, 0, 0));
            val = t_enemy.get_tile(&t_enemy, i, j);
            tile_color = tile_colors[val];
            g.fill_rect(&g, i * TILE_SIZE + (TABLE_SIZE*TILE_SIZE), j * TILE_SIZE, TILE_SIZE-1, TILE_SIZE-1, tile_color);
            g.draw_rect(&g, i * TILE_SIZE + (TABLE_SIZE*TILE_SIZE), j * TILE_SIZE, TILE_SIZE, TILE_SIZE, COLOR_RGB(0, 0, 0));
             
        }
    }
    g.draw_line(&g, TABLE_SIZE*TILE_SIZE, 0, TABLE_SIZE*TILE_SIZE, TABLE_SIZE*TILE_SIZE, COLOR_RGB(255, 255, 255));
}

void draw_ship(const Ship* ship) {
    for (size_t i = 0; i < ship->length; i++) {
        int x = ship->x;
        int y = ship->y;

        if (ship->horizontal) {
            x += i;
        } else {
            y += i;
        }

        g.draw_rect(&g, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE-1, TILE_SIZE-1, COLOR_RGB(255, 255, 0));
    }
}

void place_ships(void){
    
    Ship ships[] = {
        {5, 0, 0, true},   
        {4, 0, 0, true},   
        {4, 0, 0, true},   
        {3, 0, 0, true},   
        {3, 0, 0, true},   
        {2, 0, 0, true},   
        {2, 0, 0, true}    
    };
    size_t current_ship = 0;

    
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    g.exit(&g);
                    exit(0);
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch(event.key.scancode) {
                    case SDL_SCANCODE_R:
                        ships[current_ship].horizontal = !ships[current_ship].horizontal;
                    }
                    break;
                case SDL_EVENT_WINDOW_MOUSE_ENTER:
                    mouse_over_window = true;
                    SDL_HideCursor();
                    break;
                case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                    mouse_over_window = false;
                    SDL_ShowCursor();
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        float mouse_x, mouse_y;
                        g.get_mouse_position(&g, &mouse_x, &mouse_y);
                        const int tile_x = (int) (mouse_x / TILE_SIZE);
                        const int tile_y = (int) (mouse_y / TILE_SIZE);
                        
                        bool placed = t.set_ship(&t, tile_x, tile_y, ships[current_ship].length, ships[current_ship].horizontal);
                        if (placed) {
                            current_ship++;
                            ships[current_ship].x = tile_x;
                            ships[current_ship].y = tile_y;
                            ships[current_ship].horizontal = ships[current_ship - 1].horizontal; 
                            if (current_ship >= sizeof(ships) / sizeof(ships[0])) {
                                return; 
                            }
                        } else {
                            printf("Cannot place ship at (%d, %d)\n", tile_x, tile_y);
                        }
                    }
                    break;
                default: 
                    break;
            }
        }
        redraw_table();
        if (mouse_over_window){
            draw_ship(&ships[current_ship]);
        }

        if (mouse_over_window) {
            float mouse_x, mouse_y;
            g.get_mouse_position(&g, &mouse_x, &mouse_y);
            const int tile_x = (int) (mouse_x / TILE_SIZE);
            const int tile_y = (int) (mouse_y / TILE_SIZE);

            const COLOR highlight_color = {.r = 255, .g = 255, .b = 255, .a = 128};
            ships[current_ship].x = tile_x;
            ships[current_ship].y = tile_y;
        }

        g.update(&g);
    }

}

void battle(void){

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    g.exit(&g);
                    exit(0);
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch(event.key.scancode) {
                    
                    }
                    break;
                case SDL_EVENT_WINDOW_MOUSE_ENTER:
                    mouse_over_window = true;
                    SDL_HideCursor();
                    break;
                case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                    mouse_over_window = false;
                    SDL_ShowCursor();
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        float mouse_x, mouse_y;
                        g.get_mouse_position(&g, &mouse_x, &mouse_y);
                        mouse_x -=  (TABLE_SIZE*TILE_SIZE);

                        if (mouse_x < 0 || mouse_x >= TABLE_SIZE * TILE_SIZE || mouse_y < 0 || mouse_y >= TABLE_SIZE * TILE_SIZE) {
                            continue; // Click outside the enemy table
                        }

                        const int tile_x = (int) (mouse_x / TILE_SIZE);
                        const int tile_y = (int) (mouse_y / TILE_SIZE);

                        
                        tile target = t_enemy.get_tile(&t_enemy, tile_x, tile_y);

                        switch(target){
                            case SHIP:
                                t_enemy.set_tile(&t_enemy, tile_x, tile_y, HIT);
                                break;
                            case EMPTY:
                                t_enemy.set_tile(&t_enemy, tile_x, tile_y, MISS);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                default: 
                    break;
            }
        }
        redraw_table();

        if (mouse_over_window) {
            float mouse_x, mouse_y;
            g.get_mouse_position(&g, &mouse_x, &mouse_y);
            const int tile_x = (int) (mouse_x / TILE_SIZE);
            const int tile_y = (int) (mouse_y / TILE_SIZE);

            const COLOR highlight_color = {.r = 255, .g = 255, .b = 255, .a = 128};

            g.draw_rect(&g, tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE-1, TILE_SIZE-1, highlight_color);
        }

        g.update(&g);
    }
}




int main(void) {

    init();
    place_ships();
    battle();

    return 0;
}

