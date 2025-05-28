#ifndef SIM_H
#define SIM_H

#include "buffer.h"

#include <stdbool.h>

#define STATES 9

typedef struct simulation {
  v_buffer vehicles[4][4];
  bool interim;
  int mode;
  state lights[4][4];
} simulation;

void simulation_init(simulation *sim);

int calculate_state_value(simulation *sim, int n);

int calculate_optimal_state(simulation *sim);

void set_lights(simulation *sim, int mode);

void set_lights_interim(simulation *sim, int prev, int mode);

int sim_step(simulation *sim, vehicle *left);

#endif // SIM_H