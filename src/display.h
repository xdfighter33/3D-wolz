#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#pragma once 
#ifndef DISPLAY_H 
#define DISPLAY_HG
#define FPS 30
#define FRAME_TIME_TARGET (1000/ FPS)

/*enum colors {
	RED,
	GREEN,
	BLUE,
	WHITE,
	BLACK
};
ADDD HASHMAP TO PROGRAM
*/
extern SDL_Window* window;
extern SDL_Renderer* renderer;


extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;


extern int window_width;
extern int window_height;

extern bool initialize_window(void);


extern void draw_grid(void);

extern void draw_rect(int x, int y, int width, int height, uint32_t color);

extern void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

extern void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

extern void draw_pixel(int x, int y, uint32_t color);

extern void render_color_buffer(void);

extern void clear_color_buffer(uint32_t color);


extern void destroy_window(void);


#endif 

