#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#pragma once 
#ifndef DISPLAY_H 
#define DISPLAY_HG



extern SDL_Window* window;
extern SDL_Renderer* renderer;


extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;


extern int window_width;
extern int window_height;

extern bool initialize_window(void);


extern void draw_grid(void);

extern void draw_rect(int x, int y, int width, int height, uint32_t color);

extern void smiley_face();

extern void render_color_buffer(void);


extern void clear_color_buffer(uint32_t color);


extern void destroy_window(void);


#endif 

