#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"
#include "triangle.h"
#include "matrix.h"
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
    load_cube_mesh_data();
    //load_obj_file_datas(ASSET_DIR "/cube.obj");
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
    if(event.key.keysym.sym == SDLK_r){
        mesh.rotation.x += 0;
        mesh.rotation.y += 0;
        mesh.rotation.z += 0;
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
     mesh.scale.x += 0.02;
     mesh.scale.y += 0.01;

    mat4_t scale_matrix = mat4_scale_matrix(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    // Loop thhrough triangles faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++ ){
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];


        vec4_t transformed_vertices[3];
        // Loop through vertices and Transform

        for (int j = 0; j < 3; j++) {
            vec4_t transformed_vertex = vec3_to_vec4(face_vertices[j]);

            matrix_multiplication_vec4(scale_matrix, transformed_vertex);

            transformed_vertex = matrix_multiplication_vec4(scale_matrix,transformed_vertex);
                //Translate away from the camera
            transformed_vertex.z += 5;


            transformed_vertices[j] = transformed_vertex;
        }


        //BACKFACE CULLING ALGO  (CLOCK WISE)
        if (cull_method == CULL_BACKFACE) {
            vec3_t vector_a = vec4_to_vec3(transformed_vertices[0]);
            vec3_t vector_b = vec4_to_vec3(transformed_vertices[1]);
            vec3_t vector_c = vec4_to_vec3(transformed_vertices[2]);

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

        vec2_t projected_point[3];
        for (int j = 0; j < 3; j++){
             projected_point[j] = project(vec4_to_vec3(transformed_vertices[j]));


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

        array_push(triangles_to_render, projected_triangle);
    }
        int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        for (int j = i; j < num_triangles; j++) {
            if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
                // Swap the triangles positions in the array
                triangle_t temp = triangles_to_render[i];
                triangles_to_render[i] = triangles_to_render[j];
                triangles_to_render[j] = temp;
            }
        }
    }
}


void render(void) {
SDL_RenderClear(renderer);

draw_grid();
int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];
    if(render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE ){
        draw_filled_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            ORANGE
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

        
    }

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