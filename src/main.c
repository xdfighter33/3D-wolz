﻿#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


/* Declare Variables */
bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;


int window_width = 800;
int window_height = 800;

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

void setup(void){
    //Allocating Memory for buffer 
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    // Allocating memory for textures
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

}

/* Game Loop */
void process_input(void){
SDL_Event event;
SDL_PollEvent(&event);

switch(event.type){
    case SDL_QUIT:
     is_running = false;
     break;
    case SDL_KEYDOWN:
    if(event.key.keysym.sym == SDLK_ESCAPE){
        is_running = false;
    }
    break;
}
}

void update(void){
// To-do
}

void draw_grid(void){
for(int y = 0; y < window_height; y++){
    for(int x = 0; x < window_width; x++){
        if(y % 10 == 0 || x % 10 == 0){
color_buffer[(window_width * y) + x] =  0xFF000000;
        }
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

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    render_color_buffer();
    clear_color_buffer(0xFFFFFFFF);
    draw_grid();
    SDL_RenderPresent(renderer);
}


void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int main(void){
is_running = initialize_window();

setup();

while (is_running){
    process_input();
    update();
    render();
}

destroy_window();

return 0;
}