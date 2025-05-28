#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "buffer.h"
#include "sim.h"

direction stringToDir(char* s);

int dir_string_to_int(char* s);

bool collision(vehicle v1, vehicle v2);

void print_step_result(int fd, int n, vehicle* left);

void print_sim_status(int fd, simulation* sim);

#endif // UTILS_H