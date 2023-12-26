#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"
#include "triangle.h"

/* Declare Variables */



// enum { N_points = 9 * 9 * 9 };

#define N_points (9 * 9 * 9)


//vec3_t cube_points[N_points]; /
vec2_t projected_points[N_points];


triangle_t* triangles_to_render = NULL;

vec3_t camera_pos = { 0,0,0};
float fov_factor = 640;
bool is_running = false;
int PREVIOUS_FRAME_TIME = 0;



void setup(void){

    render_method = render_wire;
    cull_method = CULL_BACKFACE;

    //Allocating Memory for buffer 
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
    // Allocating memory for textures
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    //load_cube_mesh_data();
    load_obj_file_datas(ASSET_DIR "/f22.obj");
    // load_pyramid_mesh_data();
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
    if(event.key.keysym.sym == SDLK_1){
        render_method = RENDER_WIRE_VERRTEX;
    }
    if(event.key.keysym.sym == SDLK_2){
        render_method = render_wire;
    }
    if(event.key.keysym.sym == SDLK_3){
        render_method = RENDER_FILL_TRIANGLE;
    }

    if(event.key.keysym.sym == SDLK_4){
     //
     render_method = RENDER_FILL_TRIANGLE_WIRE;
     
    }
    if(event.key.keysym.sym == SDLK_c){
     //
     cull_method = CULL_BACKFACE;
     
    }
    if(event.key.keysym.sym == SDLK_d){
     //
     cull_method = CULL_NONE;
     
    }
    if(event.key.keysym.sym == SDLK_ESCAPE){
        is_running = false;
    }

    break;

}
}

/* Take out the divisin to get Orthographic Projectin */
vec2_t project(vec3_t point) {
    vec2_t projected_point = {
    .x = (fov_factor * point.x )  / point.z,
    .y = (fov_factor * point.y )  / point.z
    };
    return projected_point;
}

void update(void){
/* DELAY TIME TO MATCH FPS */
int time_to_wait = FRAME_TIME_TARGET - (SDL_GetTicks() - PREVIOUS_FRAME_TIME);
if (time_to_wait > 0 && time_to_wait <= FRAME_TIME_TARGET){
    SDL_Delay(time_to_wait);
}
    PREVIOUS_FRAME_TIME = SDL_GetTicks();


    triangles_to_render = NULL;
    ///* MESH ROTATION SPEED *\\\\\\\/
    //
     mesh.rotation.x += 0.01;
     mesh.rotation.y += 0.01;
     mesh.rotation.z += 0.02;

    // Loop thhrough triangles faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++ ){
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];


        vec3_t transformed_vertices[3];
        // Loop through vertices and Transform

        for (int j = 0; j < 3; j++) {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);


            //Translate away from the camera

            transformed_vertex.z += 5;
            // transformed_vertex.x


            transformed_vertices[j] = transformed_vertex;
        }


        //BACKFACE CULLING ALGO  (CLOCK WISE)
        if (cull_method == CULL_BACKFACE) {
            vec3_t vector_a = transformed_vertices[0];
            vec3_t vector_b = transformed_vertices[1];
            vec3_t vector_c = transformed_vertices[2];

            vec3_t vector_ab = vec_3_subtraction(vector_b, vector_a);
            vec3_t vector_ac = vec_3_subtraction(vector_c, vector_a);
            vec_3_normalize(&vector_ab);
            vec_3_normalize(&vector_ac);


            vec3_t normal = vec_3_cross(vector_ab, vector_ac);

            vec_3_normalize(&normal);


            // FIND CAMERA POSITIOn
            vec3_t camera_ray = vec_3_subtraction(camera_pos, vector_a);


            float dot_normal_camera = vec_3_dot(normal, camera_ray);

            if (dot_normal_camera < 0) {
                continue;
            }
        }
        //triangle_t projected_triangle;

        vec2_t projected_point[3];
        for (int j = 0; j < 3; j++){
             projected_point[j] = project(transformed_vertices[j]);


            projected_point[j].x += (window_width / 2);
            projected_point[j].y += (window_height / 2);

        }
        triangle_t projected_triangle = {
            .points = {
                projected_point[0].x, projected_point[0].y,
                projected_point[1].x, projected_point[1].y,
                projected_point[2].x, projected_point[2].y
                },
           .color = mesh_face.color
        };
        //Save to Projected Triange
        //triangles_to_render[i] = projected_triangle;

        array_push(triangles_to_render, projected_triangle);
    }
   /* for (int i = 0; i < N_points; i++)
    {
        vec3_t point = cube_points[i];

        vec3_t rotated_cube = vec3_rotate_x(point, cube_rotation.x);
        rotated_cube = vec3_rotate_y(rotated_cube, cube_rotation.y);
        rotated_cube = vec3_rotate_z(rotated_cube, cube_rotation.z);


        rotated_cube.z -= camera_pos.z;

        /* Projecting poitns ////*
        vec2_t projected_point = project(rotated_cube);


        projected_points[i] = projected_point;


    }
    /*/
}


void render(void) {
SDL_RenderClear(renderer);

draw_grid();
// draw_line(400, 300, 400, 0xFFFF00FF);
//draw_rect(300, 200, 300, 150, 0xFFFF00FF);
/*
for (int i = 0; i < N_points; i++) {
    vec2_t projected_point = projected_points[i];
       /* vec2_t point1 = projected_points[i];
        vec2_t point2 = projected_points[(i + 1) % N_points];

        float start_x = point1.x + (window_width / 2);
        float start_y = point1.y + (window_height / 2);
        float line_length = (float)(point2.x - point1.x);
/*
    draw_rect(
        projected_point.x + (window_width / 2),
        projected_point.y + (window_height / 2),
        4,
        4,
        0xFFFF00FF);
}
*/
int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];
    if(render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE ){

    
        //draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0x0000FF00);
         //draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0x0000FF00);
        //draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0x0000FF00);
        draw_filled_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            BLUE
        );
    }
        if (render_method == render_wire || render_method == RENDER_WIRE_VERRTEX || render_method == RENDER_FILL_TRIANGLE_WIRE){
                
        draw_triangle(
            triangle.points[0].x, triangle.points[0].y,
            triangle.points[1].x, triangle.points[1].y,
            triangle.points[2].x, triangle.points[2].y,
            WHITE
                );
        }
            if(render_method == RENDER_WIRE_VERRTEX){
             draw_rect(triangle.points[0].x , triangle.points[0].y, 6, 6, RED);
             draw_rect(triangle.points[1].x , triangle.points[1].y , 6, 6, RED);
             draw_rect(triangle.points[2].x ,  triangle.points[2].y , 6, 6, RED);
            }

        //draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, RED);
        //draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, RED);
        //draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y, RED);
        //draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[2].x, triangle.points[2].y, RED);
        
    }
    
        //draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, 0xFFFF00FF);
        //draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFF00FF);
        //draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y, 0xFFFF00FF);
        //draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[2].x, triangle.points[2].y, 0xFFFF00FF);

    




    //FREE MEMORY (ARRAY)
    array_free(triangles_to_render);

    render_color_buffer();
    clear_color_buffer(0xFF000000);


      
    SDL_RenderPresent(renderer);
}


void free_data(void) {
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
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
free_data(); // CLEAR UP MEMMORY OF THE ARRAY 

return 0;
}