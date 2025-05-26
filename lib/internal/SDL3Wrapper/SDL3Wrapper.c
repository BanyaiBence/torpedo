//
// Created by bence on 2025. 05. 26..
//

#include "SDL3Wrapper.h"

inline void SDL3_create_window(const char *title, const int width, const int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL3_WINDOW = SDL_CreateWindow(title,
                                   width,
                                   height,
                                   0);
    if (!SDL3_WINDOW) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL3_RENDERER = SDL_CreateRenderer(SDL3_WINDOW, nullptr);
    if (!SDL3_RENDERER) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(SDL3_WINDOW);
        SDL_Quit();
        exit(1);
    }
}

inline void SDL3_draw_rect(const float x, const float y, const float widht, const float height, const COLOR color) {
    SDL_SetRenderDrawColor(SDL3_RENDERER, color.r, color.g, color.b, color.a);
    const RECT rect = {x, y, widht, height};
    SDL_RenderFillRect(SDL3_RENDERER, &rect);
}

inline void SDL3_fill_window(COLOR color) {
    SDL_SetRenderDrawColor(SDL3_RENDERER, color.r, color.g, color.b, color.a);
}

inline void SDL3_update() {
    SDL_RenderPresent(SDL3_RENDERER);
}

inline void SDL3_exit() {
    SDL_DestroyRenderer(SDL3_RENDERER);
    SDL_DestroyWindow(SDL3_WINDOW);
    SDL_Quit();
}
