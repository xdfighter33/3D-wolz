#pragma once
#include <stdlib.h>
#include "vector.h"
typedef struct {
	int a;
	int b;
	int c;
} face_t;

typedef struct {
	vec2_t points[3];
}triangle_t ;

extern void fill_float_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int m2, uint32_t color);
//void fill_float_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int m2, uint32_t color);
extern void draw_filled_traingle(int x0, int y0, int x1, int y1, int y2, uint32_t color);