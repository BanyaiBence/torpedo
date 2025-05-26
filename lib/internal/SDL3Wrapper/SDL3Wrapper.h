//
// Created by bence on 2025. 05. 26..
//
#include <SDL3/SDL.h>
#ifndef SDL3WRAPPER_H
#define SDL3WRAPPER_H

#define WINDOW SDL_Window
#define RENDERER SDL_Renderer
#define COLOR SDL_Color
#define RECT SDL_FRect

RENDERER* SDL3_RENDERER;
WINDOW* SDL3_WINDOW;


void SDL3_create_window(char* title, int width, int height);
void SDL3_draw_rect(float x, float y, float widht, float height, COLOR color);
void SDL3_fill_window(COLOR color);
void SDL3_update();
void SDL3_exit();


#endif //SDL3WRAPPER_H





