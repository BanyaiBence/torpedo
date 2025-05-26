#include <stdio.h>
#include "table.h"
#include <stdlib.h>
#include <time.h>
#include "lib/internal/SDL3Wrapper/SDL3Wrapper.h"
#include <SDL3/SDL.h>

int main(void) {
    // Seeding random generator
    srand(time(NULL));


    table t;
    table_init(&t);
    table_generate_random(&t);
    table_set_ship(&t, 5, 5 ,4, 1);

    SDL3_create_window("Torpedo", 800, 800);
    const COLOR back_color = COLOR {0, 0, 0, 255};

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL3_exit();
                exit(0);
            }
        }
        SDL3_fill_window(back_color);

        for (int i = 0; i < TABLE_SIZE; i++) {
            for (int j = 0; j < TABLE_SIZE; j++) {
                tile val = table_get_tile(&t, i, j);
                COLOR tile_color  {0, 0, 0, 0};
                switch (val) {
                    case EMPTY:
                        tile_color  {0, 0, 255, 255};
                        break;
                    case SHIP:
                        tile_color  {150, 150, 150, 255};
                        break;
                    case HIT:
                        tile_color {0, 255, 0, 255};
                    case MISS:
                        tile_color {255, 0, 0, 255};
                        break;
                }
                SDL3_draw_rect(j*TILE_SIZE, i*TILE_SIZE, TILE_SIZE, TILE_SIZE, tile_color);
            }
        }
        SDL3_update();
    }
    SDL3_exit();


    return 0;
}