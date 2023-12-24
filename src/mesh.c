#include <stdio.h>
#include "mesh.h"
#include "array.h"


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



void load_obj_file_datas(const char* file_name) {
	FILE* file;
	file = fopen(file_name, "r");


	char line[1024];
	if (file != NULL) {
		printf("Opened model1.obj!\n");
		while (fgets(line, 1024, file)) {
			printf("LINE=%s", line);
		}
		// fclose(file);
	}
	else {
		perror("Unable to open cube.obj");
	}

	return 0;
}

