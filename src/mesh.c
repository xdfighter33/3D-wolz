#include <stdio.h>
#include "mesh.h"
#include "array.h"
#include <string.h>

mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0,0,0}
};

vec3_t pyramid_vertices[N_PYRAMID_VERTICES] = {
	{.x = -1, .y = -1, .z = -1 }, //1 
	{.x = -1, .y = 1, .z = -1 }, //2 
	{.x = 1, .y = 1, .z = -1 }, //3 
	{.x = 1, .y = -1, .z = -1 }, //4

	//APEX OF THE TRIANGLE 
	{.x = 0, .y = 0, .z = 1}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
	{.x = -1, .y = -1, .z = -1 }, //1 
	{.x = -1, .y = 1, .z = -1 }, //2 
	{.x = 1, .y = 1, .z = -1 }, //3 
	{.x = 1, .y = -1, .z = -1 }, //4
	{.x = 1, .y = 1, .z = 1 }, //5
	{.x = 1, .y = -1, .z = 1 }, //6
	{.x = -1, .y = 1, .z = 1 }, //7 
	{.x = -1, .y = -1, .z = 1 }, //8 


};

face_t cube_faces[N_CUBE_FACES] = {

	// Front
	{.a = 1, .b = 2, .c = 3},
	{.a = 1, .b = 3, .c = 4},

	// Right
	{.a = 4, .b = 3, .c = 5},
	{.a = 4, .b = 5, .c = 6},

	//bac
	{.a = 6, .b = 5, .c = 7},
	{.a = 6, .b = 7, .c = 8},
	//left
	{.a = 8, .b = 7, .c = 2},
	{.a = 8, .b = 2, .c = 1},
	//top
	{.a = 2, .b = 7, .c = 5},
	{.a = 2, .b = 5, .c = 3},
	//bottom
	{.a = 6, .b = 8, .c = 1},
	{.a = 6, .b = 1, .c = 4},

};


face_t pyramid_faces[N_PYRAMID_FACES] = {
	{.a = 1, .b = 2, .c = 5},

	{.a =2, .b = 3, .c = 5},

	{.a =3, .b = 4, .c = 5},

	{.a =4, .b = 1, .c = 5},
};


void load_cube_mesh_data(void) {
	for (int i = 0; i < N_CUBE_VERTICES; i++) {
		vec3_t cube_vertex = cube_vertices[i];
		array_push(mesh.vertices, cube_vertex);
	}
	for (int i = 0; i < N_CUBE_FACES; i++) {
		face_t cube_face = cube_faces[i];
		array_push(mesh.faces, cube_face);
	}
}


void load_pyramid_mesh_data(void) {
	for (int i = 0; i < N_PYRAMID_VERTICES; i++) {
		vec3_t pyramid_vertex = pyramid_vertices[i];
		array_push(mesh.vertices, pyramid_vertex);
	}
	for (int i = 0; i < N_PYRAMID_FACES; i++) {
		face_t pyramid_face = pyramid_faces[i];
		array_push(mesh.faces, pyramid_face);
	}
}



void load_obj_file_datas(char* filename) {
	FILE* file;
	file = fopen(filename, "r");
	char line[1024];

	while (fgets(line, 1024, file)) {
		// Vertex information
		if (strncmp(line, "v ", 2) == 0) {
			vec3_t vertex;
			sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			array_push(mesh.vertices, vertex);
		}
		// Face information
		if (strncmp(line, "f ", 2) == 0) {
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf(
				line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex_indices[0], &texture_indices[0], &normal_indices[0],
				&vertex_indices[1], &texture_indices[1], &normal_indices[1],
				&vertex_indices[2], &texture_indices[2], &normal_indices[2]
			);
			face_t face = {
				.a = vertex_indices[0],
				.b = vertex_indices[1],
				.c = vertex_indices[2]
			};
			array_push(mesh.faces, face);
		}
	}
}
