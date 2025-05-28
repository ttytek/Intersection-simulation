#ifndef RENDERER_H
#define RENDERER_H

#include "sim.h"


#define WIDTH 33
#define HEIGHT 19

#define RESET   "\x1b[0m"
#define RED_ANSI     "\x1b[31m"
#define GREEN_ANSI   "\x1b[32m"
#define YELLOW_ANSI  "\x1b[33m"

typedef struct pos{
    int col;
	int row;
} Position;

void draw(simulation* sim);

#endif // RENDERER_H