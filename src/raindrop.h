#pragma once 
#include "vector.h"
#include "triangle.h"
#include "display.h"

#define NUM_RAIN_DROPS 100

typedef struct {
	vec2_t pos;
	float speed;
	float symbol;
} Raindrop;

void initialize_raindrops(void);
void update_raindrops(void);
void render_raindrops(void);