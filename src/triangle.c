#include "triangle.h"
#include "stdio.h"
#include "display.h"
vec3_t barycentric_weights(vec2_t a, vec2_t b, vec2_t c, vec2_t p) {
    // Find the vectors between the vertices ABC and point p
    vec2_t ac = vec_2_subtraction(c, a);
    vec2_t ab = vec_2_subtraction(b, a);
    vec2_t ap = vec_2_subtraction(p, a);
    vec2_t pc = vec_2_subtraction(c, p);
    vec2_t pb = vec_2_subtraction(b, p);

    // Compute the area of the full parallegram/triangle ABC using 2D cross product
    float area_parallelogram_abc = (ac.x * ab.y - ac.y * ab.x); // || AC x AB ||

    // Alpha is the area of the small parallelogram/triangle PBC divided by the area of the full parallelogram/triangle ABC
    float alpha = (pc.x * pb.y - pc.y * pb.x) / area_parallelogram_abc;

    // Beta is the area of the small parallelogram/triangle APC divided by the area of the full parallelogram/triangle ABC
    float beta = (ac.x * ap.y - ac.y * ap.x) / area_parallelogram_abc;

    // Weight gamma is easily found since barycentric coordinates always add up to 1.0
    float gamma = 1 - alpha - beta;

    vec3_t weights = { alpha, beta, gamma };
    return weights;
}

void draw_texture (int x,int y, uint32_t* texture, vec2_t poiint_a, vec2_t point_b,vec2_t point_c,float u0,float v0, float u1, float v1,float u2, float v2){

	vec2_t point_p = {x,y};
	vec3_t weight = barycentric_weights(poiint_a,point_b,point_c,point_p);

	float alpha = weight.x;
	float beta = weight.y;
	float gamma = weight.z;

	float inter_x = (u0) * alpha + (u1) * beta + (u2) * gamma;

	float inter_y = (v0) * alpha + (v1) * beta + (v2) * gamma;




    int tex_x = abs((int)(inter_x * texture_width));
    int tex_y = abs((int)(inter_y * texture_height));

	draw_pixel(x, y, texture[(texture_width * tex_y) + tex_x]);


}
void fill_float_bottom_triangle(int x0, int y0, int x1,int y1,int x2,int y2, uint32_t color) {
	float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
	float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

	float x_start = x0;
	float x_end = x0;
	for (int y = y0; y <= y2; y++) {
		draw_line(x_start, y, x_end, y, color);
		x_start += inv_slope_1;
		x_end += inv_slope_2;
	}

}

void fill_float_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
	float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

	float x_start = x2;
	float x_end = x2;


	for (int y = y2; y >= y0; y--) {
		draw_line(x_start, y, x_end, y, color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
	}
}


void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void float_swap(float* a, float* b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
}


void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	if (y0 > y1) {
		swap(&y0, &y1);
		swap(&x0, &x1);
	}
	if (y1 > y2){
		swap(&y1, &y2);
		swap(&x1, &x2);
	}
	if (y0 > y1) {
		swap(&y0, &y1);
		swap(&x0, &x1);
	}

	if (y1 == y2) {
		//fill_float_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
	}
	else if (y0 == y1) {
		//fill_float_top_triangle(x0, y0, x1, y1, x2, y2, color);

	}

	int mY = y1;
	int mX = ((float)((x2 - x0) * (y1 - y0)) /(float) (y2 - y0)) + x0;
	
	fill_float_bottom_triangle(x0, y0, x1, y1, mX, mY,color);
	fill_float_top_triangle(x1, y1, mX, mY, x2, y2, color);




	//fill_float_top_triangle(x1,y1, mX,mY, x2,y2,color);


}


void draw_texture_triangle(
	int x0, int y0,float u0, float v0,
	int x1, int y1,float u1, float v1,
	int x2, int y2,float u2, float v2,
	uint32_t* texture
){
	if (y0 > y1) {
		swap(&y0, &y1);
		swap(&x0, &x1);
		float_swap(&u0, &u1);
		float_swap(&v0, &v1);
	}
	if (y1 > y2){
		swap(&y1, &y2);
		swap(&x1, &x2);
		float_swap(&u1, &u2);
		float_swap(&v1, &v2);
	}
	if (y0 > y1) {
		swap(&y0, &y1);
		swap(&x0, &x1);
		float_swap(&u0, &u1);
		float_swap(&v0, &v1);
	}



	vec2_t point_a = {x0,y0};
	vec2_t point_b = {x1,y1};
	vec2_t point_c = {x2,y2};
    float inv_slope_1 = 0;
    float inv_slope_2 = 0;

    if (y1 - y0 != 0) inv_slope_1 = (float)(x1 - x0) / abs(y1 - y0);
    if (y2 - y0 != 0) inv_slope_2 = (float)(x2 - x0) / abs(y2 - y0);

    if (y1 - y0 != 0) {
        for (int y = y0; y <= y1; y++) {
            int x_start = x1 + (y - y1) * inv_slope_1;
            int x_end = x0 + (y - y0) * inv_slope_2;

            if (x_end < x_start) {
                swap(&x_start, &x_end); // swap if x_start is to the right of x_end
            }

            for (int x = x_start; x < x_end; x++) {
                // Draw our pixel with the color that comes from the texture
                draw_texture(x, y, texture, point_a, point_b, point_c, u0, v0, u1, v1, u2, v2);
            }
        }
    }

	inv_slope_1 = 0;
	inv_slope_2 = 0;

	if (y2 - y1 != 0) inv_slope_1 = (float)(x2 - x1) / abs(y2 - y1);
    if (y2 - y0 != 0) inv_slope_2 = (float)(x2 - x0) / abs(y2 - y0);
 		
    if (y2 - y1 != 0) {
        for (int y = y1; y <= y2; y++) {
            int x_start = x1 + (y - y1) * inv_slope_1;
            int x_end = x0 + (y - y0) * inv_slope_2;

            if (x_end < x_start) {
                swap(&x_start, &x_end); // swap if x_start is to the right of x_end
            }

            for (int x = x_start; x < x_end; x++) {
                // Draw our pixel with the color that comes from the texture
                draw_texture(x, y, texture, point_a, point_b, point_c, u0, v0, u1, v1, u2, v2);
            }
        }
    }
}
