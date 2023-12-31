#include <stdlib.h>
#include "vector.h"

typedef struct {
    float m[4][4];
} mat4_t;

mat4_t matrix_identity(void);

mat4_t mat4_scale_matrix(float sx, float sy, float sz);
mat4_t mat4_translate_matrix(float tx, float ty, float tz);
mat4_t matrix_multiplication_mat4(mat4_t m, mat4_t b);
mat4_t mat4_rotation_matrix_x(float angle);
mat4_t mat4_rotation_matrix_y(float angle);
mat4_t mat4_rotation_matrix_z(float angle); 
mat4_t mat4_make_perspecitve(float fov, float aspect, float znear, float zfar);
vec4_t matrix_multiplication_vec4(mat4_t m, vec4_t b);
vec4_t vec4_multi_mat4_perspect(mat4_t m, vec4_t v);