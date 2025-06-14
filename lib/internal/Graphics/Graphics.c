//
// Created by bence on 2025. 05. 26..
//

#include "Graphics.h"
#include <stdlib.h>

inline void Graphics_create_window(Graphics *self, const char *title, const int width, const int height) {
    self->window = SDL_CreateWindow(title,
                                    width,
                                    height,
                                    0);
    if (!self->window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    self->renderer = SDL_CreateRenderer(self->window, nullptr);
    if (!self->renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(self->window);
        SDL_Quit();
        exit(1);
    }
}

inline void Graphics_draw_rect(Graphics *self, const float x, const float y, const float width, const float height,
                               const COLOR color) {
    SDL_SetRenderDrawColor(self->renderer, color.r, color.g, color.b, color.a);
    const RECT rect = {x, y, width, height};
    SDL_RenderFillRect(self->renderer, &rect);
}

inline void Graphics_fill_window(Graphics *self, const COLOR color) {
    SDL_SetRenderDrawColor(self->renderer, color.r, color.g, color.b, color.a);
}

inline void Graphics_update(Graphics *self) {
    SDL_RenderPresent(self->renderer);
}

inline void Graphics_exit(Graphics *self) {
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    SDL_Quit();
}


inline void Graphics_get_mouse_position(Graphics *self, float *x, float *y) {
    SDL_GetMouseState(x, y);
}

void Graphics_init(Graphics *self) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    self->window = nullptr;
    self->renderer = nullptr;
    self->create_window = Graphics_create_window;
    self->draw_rect = Graphics_draw_rect;
    self->fill_window = Graphics_fill_window;
    self->update = Graphics_update;
    self->exit = Graphics_exit;
    self->get_mouse_position = Graphics_get_mouse_position;
}
