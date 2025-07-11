#include <stdio.h>
#include "lib/internal/Table/Table.h"
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <stdbool.h>


int main(void) {
    // Seeding random generator
    srand(time(nullptr));


    Table t;
    Table_init(&t);
    t.generate_random(&t);
    t.set_tile(&t, 5, 5, HIT);
    t.set_tile(&t, 3, 3, MISS);

    Graphics g;
    Graphics_init(&g);
    g.create_window(&g, "Battleship", TABLE_SIZE * 2 * TILE_SIZE, TABLE_SIZE * TILE_SIZE);
    const COLOR back_color = {.r = 0, .g = 0, .b = 0, .a = 255};

    bool mouse_over_window = false;

    int ship_to_place[3][2] = {
        {0, 0},
        {0, 1},
        {0, 2}
    };
    int ship_to_place_length = sizeof(ship_to_place) / sizeof(ship_to_place[0]);

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    g.exit(&g);
                    exit(0);
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

                        const tile current_tile = t.get_tile(&t, tile_x, tile_y);
                        switch (current_tile) {
                            case EMPTY:
                                t.set_tile(&t, tile_x, tile_y, MISS);
                                break;
                            case SHIP:
                                t.set_tile(&t, tile_x, tile_y, HIT);
                                break;
                            case HIT:
                            case MISS:
                                // Do nothing if already hit or missed
                                break;
                            default:
                                // Handle unexpected cases
                                fprintf(stderr, "Unexpected tile value: %c\n", current_tile);
                                break;
                        }
                    }
                    break;
                default: ;
            }
        }
        g.fill_window(&g, back_color);

        for (int i = 0; i < TABLE_SIZE; i++) {
            for (int j = 0; j < TABLE_SIZE; j++) {
                const tile val = t.get_tile(&t, i, j);
                const COLOR tile_color = tile_colors[val];
                g.fill_rect(&g, i * TILE_SIZE+2, j * TILE_SIZE+2, TILE_SIZE-1, TILE_SIZE-1, tile_color);
                g.draw_rect(&g, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, COLOR_RGB(0, 0, 0));
            }
        }


        if (mouse_over_window) {
            float mouse_x, mouse_y;
            g.get_mouse_position(&g, &mouse_x, &mouse_y);
            const int tile_x = (int) (mouse_x / TILE_SIZE);
            const int tile_y = (int) (mouse_y / TILE_SIZE);

            const COLOR highlight_color = {.r = 255, .g = 255, .b = 255, .a = 128};

            for(int i = 0; i < ship_to_place_length; i++) {
                int ship_x = ship_to_place[i][0] + tile_x;
                int ship_y = ship_to_place[i][1] + tile_y;

                g.draw_rect(&g, ship_x * TILE_SIZE, ship_y * TILE_SIZE, TILE_SIZE-1, TILE_SIZE-1, COLOR_RGB(255, 255, 0));
            }
        }

        g.update(&g);
    }
    return 0;
}
