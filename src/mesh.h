// Izix's 3D World.h : Include file for standard system include files,
// or project specific include files.


#include "vector.h"
#include "triangle.h"
#include "array.h"
#pragma once
#define N_PYRAMID_VERTICES 5
#define N_PYRAMID_FACES 4
#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2 )
extern vec3_t cube_vertices[N_CUBE_VERTICES];
extern vec3_t pyramid_vertices[N_PYRAMID_VERTICES];

extern face_t cube_faces[N_CUBE_FACES];
extern face_t pyramid_face[N_PYRAMID_FACES];


typedef struct {
	vec3_t* vertices;
	face_t* faces;
	vec3_t rotation;

}mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_pyramid_mesh_data(void);
// TODO: Reference additional headers your program requires here.
