#pragma once
#include <stdlib.h>
#include "vector.h"
#include "texture.h"
#include <stdlib.h>
typedef struct {
	int a;
	int b;
	int c;
	tex2_t a_uv;
	tex2_t b_uv;
	tex2_t c_uv;
	uint32_t color;

} face_t;

typedef struct {
	vec2_t points[3];
	tex2_t tex_cords[3];
	uint32_t color;
	float avg_depth;
}triangle_t ;

extern void fill_float_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int m2, uint32_t color);
extern void fill_float_top_triangle(int x0, int y0, int x1, int y1, int x2, int m2, uint32_t color);
extern void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_texture_triangle(
	int x0, int y0,float u0, float v0,
	int x1, int y1,float u1, float v1,
	int x2, int y2,float u2, float v2,
	uint32_t color
);