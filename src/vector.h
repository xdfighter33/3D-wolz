#pragma once
#include <SDL.h>
typedef struct{
    float x;
    float y;
}vec2_t;

typedef struct{
    float x;
    float y;
    float z;
}vec3_t;

extern float vec_2_legth(vec2_t v);
extern vec2_t vec_2_addition(vec2_t v, vec2_t x);
extern vec2_t vec_2_subtraction(vec2_t v, vec2_t x);
extern vec2_t vec_2_multiply(vec2_t v, float factor);
extern vec2_t vec_2_divide(vec2_t v, float factor);
extern float vec_2_dot(vec2_t a, vec2_t b);
extern void vec_2_normalize(vec2_t* v);

extern float vec_3_legth(vec3_t v);
extern vec3_t vec_3_subtraction(vec3_t v, vec3_t x);
extern vec3_t vec_3_addition(vec3_t v, vec3_t x);
extern vec3_t vec_3_multiply(vec3_t v, float factor);
extern vec3_t vec_3_divide(vec3_t v, float factor);
extern vec3_t vec_3_cross(vec3_t a, vec3_t b);
extern void vec_3_normalize(vec3_t* v);
extern float vec_3_dot(vec3_t a, vec3_t b);
vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

/* Add Vector Math */


