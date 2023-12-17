#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

/* Declare Variables */
bool is_running = false;
SDL_Window* window;
SDL_Renderer* renderer;

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
800,
800,
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
// To-do
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

void render(void){
SDL_SetRenderDrawColor(renderer, 255,0,0,255);
SDL_RenderClear(renderer);

SDL_RenderPresent(renderer);
}






int main(void){
is_running = initialize_window();

while (is_running){
    process_input();
    update();
    render();
}

}