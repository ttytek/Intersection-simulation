#ifndef RENDERER_H
#define RENDERER_H

#include "sim.h"

#define WIDTH 33
#define HEIGHT 19

#define RESET "\x1b[0m"
#define RED_ANSI "\x1b[31m"
#define GREEN_ANSI "\x1b[32m"
#define YELLOW_ANSI "\x1b[33m"

typedef struct pos {
  int col;
  int row;
} Position;

/**
 * @brief Renders a visual representation of the intersection simulation.
 * 
 * This function prints the current state of the intersection to `stderr`.
 * It draws a static ASCII-art map of the roads, overlayed with:
 * - The last character of each vehicle's ID on its respective lane.
 * - Traffic light positions with their respective colors (RED, YELLOW, GREEN).
 * 
 * Vehicles are displayed based on their direction using data from
 * `lane_position` and `lane_direction`. Each vehicle is drawn on the map
 * at a calculated location, showing only the last character of its ID.
 * 
 * ANSI escape codes are used to control the output color in the terminal.
 * 
 * @param sim Pointer to the simulation object containing vehicle buffers and light states.
 * 
 * @note Output is written to file descriptor 2 (`stderr`) using `dprintf`.
 * @note Vehicles with the same `start == end` are ignored in the rendering.
 */

void draw(simulation *sim);

#endif // RENDERER_H