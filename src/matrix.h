#include <stdlib.h>
#include "vector.h"
typedef struct{
float m[4][4];
} mat4_t;

mat4_t matrix_identity(void);

mat4_t mat4_scale_matrix(float sx, float sy, float sz);

mat4_t mat4_translate_matrix(float tx, float ty, float tz);

vec4_t matrix_multiplication_vec4(mat4_t m, vec4_t b);