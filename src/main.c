﻿#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
/* Declare Variables */

float fov_angle = 640;
// enum { N_points = 9 * 9 * 9 };

#define N_points (9 * 9 * 9)


vec3_t cube_points[N_points]; // 
vec2_t projected_points[N_points];
vec3_t camera_pos = { .x = 0, .y = 0, .z = -5 };
bool is_running = false;




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

    int point_count = 0;

    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t new_point = { .x = x, .y = y, .z = z };
                cube_points[point_count++] = new_point;
            }
        }
    }

    
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
    if(event.key.keysym.sym == SDLK_4){
        //Smiley_face();
    }
    if(event.key.keysym.sym == SDLK_ESCAPE){
        is_running = false;
    }
    break;

}
}


vec2_t project(vec3_t point) {
    vec2_t projected_point = {
    .x = (fov_angle * point.x ) / point.z,
    .y = (fov_angle * point.y ) / point.z
    };
    return projected_point;
}

void update(void){
    for (int i = 0; i < N_points; i++)
    {
        vec3_t point = cube_points[i];


        point.z -= camera_pos.z;

        /* Projecting poitns */
        vec2_t projected_point = project(point);


        projected_points[i] = projected_point;
    }
}


void render(void) {


//draw_grid();
// draw_line(400, 300, 400, 0xFFFF00FF);
//draw_rect(300, 200, 300, 150, 0xFFFF00FF);

for (int i = 0; i < N_points; i++) {
    vec2_t projected_point = projected_points[i];

    draw_rect(
        projected_point.x + (window_width / 2),
        projected_point.y + (window_height / 2),
        4,
        4,
        0xFFFF00FF);

}

    render_color_buffer();
    clear_color_buffer(0xFF000000);


      
    SDL_RenderPresent(renderer);
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