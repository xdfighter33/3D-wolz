﻿#include "display.h"

/* Declare Variables */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;


int window_width = 800;
int window_height = 600;

/* Setting up functions */
bool initialize_window(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error Initialzing SDL\n");
        return false; 
    }
window = SDL_CreateWindow(
NULL,
SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED,
window_width,
window_height,
SDL_WINDOW_BORDERLESS);
if (!window){
    fprintf(stderr, "Error creating the window \n");
    return false; 
}

renderer = SDL_CreateRenderer(window, -1, 0);
if(!renderer){
    fprintf(stderr, "Erroe creating the SDL render \n");
    return false; 
}

return true; 
}





void draw_grid(void){
for(int y = 0; y < window_height; y+= 10){
    for(int x = 0; x < window_width; x+= 10){
      
color_buffer[(window_width * y) + x] =  0xFF444444;
        
    }
}
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
        color_buffer[(window_width * y) + x] = color;
    }
}


void draw_line(int x0, int y0, int x1, int y1,uint32_t color) {
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0); 

    int side_length = abs(delta_x) >=  abs(delta_y) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)side_length;
    float y_inc = delta_y / (float)side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= side_length; i++)
    {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

extern void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            draw_pixel(current_x, current_y, color);
        }
    }
}
    

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }

    }
}




void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
