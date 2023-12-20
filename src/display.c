#include "display.h"


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

void smiley_face(int x, int y,int length,uint32_t color) {
    for (int i = 0; i < length; i++) {
        int current_x = x + i;
        color_buffer[(window_width * y) + current_x] = color;
    }
}


void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(window_width * current_y) + current_x] = color;
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
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
