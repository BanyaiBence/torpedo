//
// Created by bence on 2025. 05. 26..
//
#ifndef SDL3WRAPPER_H
#define SDL3WRAPPER_H

#include <SDL3/SDL.h>

#define WINDOW SDL_Window
#define RENDERER SDL_Renderer
#define COLOR SDL_Color
#define RECT SDL_FRect
#define COLOR_RGB(r, g, b) (COLOR){r, g, b, 255}

typedef struct Graphics Graphics;
struct Graphics {
    RENDERER *renderer;
    WINDOW *window;

    void (*create_window)(Graphics *self, const char *title, const int width, const int height);

    void (*fill_rect)(Graphics *self, const float x, const float y, const float width, const float height,
                      const COLOR color);

    void (*draw_rect)(Graphics *self, const float x, const float y, const float width, const float height,
                      const COLOR color);

    void (*fill_window)(Graphics *self, const COLOR color);

    void (*update)(Graphics *self);

    void (*exit)(Graphics *self);

    void (*get_mouse_position)(Graphics *self, float *x, float *y);

    void (*draw_line)(Graphics *self, const float start_x, const float start_y, const float end_x, const float end_y,  const COLOR color);
};

void Graphics_init(Graphics *self);

void Graphics_create_window(Graphics *self, const char *title, const int width, const int height);

void Graphics_fill_rect(Graphics *self, const float x, const float y, const float width, const float height,
                        const COLOR color);
void Graphics_draw_rect(Graphics *self, float x, float y, float width, float height, COLOR color);

void Graphics_fill_window(Graphics *self, const COLOR color);

void Graphics_update(Graphics *self);

void Graphics_get_mouse_position(Graphics *self, float *x, float *y);

void Graphics_exit(Graphics *self);

void Graphics_draw_line(Graphics *self, float start_x, float start_y, float end_x, float end_y, COLOR color);


#endif //SDL3WRAPPER_H
