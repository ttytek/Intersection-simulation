#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "renderer.h"
#include "sim.h"
#include "utils.h"

int main() {
  char command[16];
  simulation sim;
  simulation_init(&sim, 0);
  print_sim_status(2, &sim);
  bool added_since_last_step = false;
  while (scanf("%s", command) == 1) {
    if (strcmp(command, "addVehicle") == 0) {
      char start[16];
      char end[16];
      vehicle v;
      if (!scanf("%s %s %s", v.id, start, end)) {
        break;
      }
      v.start = stringToDir(start);
      v.end = stringToDir(end);
      sim_add_vehicle(&sim, v);
      dprintf(2, "added %s %d %d\n", v.id, v.start, v.end);
      added_since_last_step = true;
    }
    vehicle left[8];
    if (strcmp(command, "step") == 0) {
      if (added_since_last_step) {
        draw(&sim);
        added_since_last_step = false;
      }
      int n = sim_step(&sim, left);

      print_step_result(1, n, left);
      print_step_result(2, n, left);

      print_sim_status(2, &sim);
      draw(&sim);
    }
  }
}
