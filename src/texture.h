#pragma once
#include <stdint.h>
#include <stdlib.h>
typedef struct {
    float u;
    float v;
}tex2_t;

extern int texture_width;
extern int texture_height;

extern uint32_t* mesh_texture;
extern const uint8_t RED_BRICK[];

extern uint32_t* texture;