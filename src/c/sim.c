#include "sim.h"

const bool states[9][4][4] = {
    {
        // all lights are red (waiting for vehicles)
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false},
    },
    {
        // all vehicles from north road can move
        {true, true, true, true},
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false},
    },
    {
        // all vehicles from east road can move
        {false, false, false, false},
        {true, true, true, true},
        {false, false, false, false},
        {false, false, false, false},
    },
    {
        // all vehicles from south road can move
        {false, false, false, false},
        {false, false, false, false},
        {true, true, true, true},
        {false, false, false, false},
    },
    {
        // all vehicles from east road can move
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false},
        {true, true, true, true},
    },
    {
        // vehicles from north and south can go staight and right
        {false, false, true, true},
        {false, false, false, false},
        {true, true, false, false},
        {false, false, false, false},
    },
    {
        // vehicles from east and west can go straight and right
        {false, false, false, false},
        {true, false, false, true},
        {false, false, false, false},
        {false, true, true, false},
    },
    {
        // vehicles from north and south can go left and do a U-turn
        {true, true, false, false},
        {false, false, false, false},
        {false, false, true, true},
        {false, false, false, false},
    },
    {
        // vehicles from east and west can go left and do a U-turn
        {false, false, false, false},
        {false, true, true, false},
        {false, false, false, false},
        {true, false, false, true},
    },
};

void simulation_init(simulation *sim, int min_light_duration) {
  sim->interim = false;
  sim->mode = 0;
  sim->step_n = 0;
  sim->min_light_duration = min_light_duration;
  sim->last_change = -min_light_duration; //Allows for immediate state change at the beggining of the simulation.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      buf_init(&(sim->vehicles[i][j]));
      sim->lights[i][j] = RED;
    }
  }
}

int calculate_state_value(simulation *sim, int n) {
  int v = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (states[n][i][j])
        v += buf_count(&(sim->vehicles[i][j]));
    }
  }
  return v;
}

int calculate_optimal_state(simulation *sim) {
  int opt = 0;

  int opt_val = 0;
  for (int i = 0; i < STATES; i++) {
    int v = calculate_state_value(sim, i);
    if (v > opt_val) {
      opt = i;
      opt_val = v;
    }
  }
  return opt;
}

void set_lights(simulation *sim, int mode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (states[mode][i][j]) {
        sim->lights[i][j] = GREEN;
      } else {
        sim->lights[i][j] = RED;
      }
    }
  }
}

void set_lights_interim(simulation *sim, int prev, int mode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((states[prev][i][j]) && (states[mode][i][j]))
        sim->lights[i][j] = GREEN;
      if ((!states[prev][i][j]) && (states[mode][i][j]))
        sim->lights[i][j] = REDYELLOW;
      if ((states[prev][i][j]) && (!states[mode][i][j]))
        sim->lights[i][j] = YELLOW;
      if ((!states[prev][i][j]) && (!states[mode][i][j]))
        sim->lights[i][j] = RED;
    }
  }
}

int sim_step(simulation *sim, vehicle *left) {
  sim->step_n++;
  if (sim->interim) {
    set_lights(sim, sim->mode);
    sim->interim = false;
    sim->last_change=sim->step_n;
  } else {
    if(sim->step_n-sim->last_change>=sim->min_light_duration){
      int opt_mode = calculate_optimal_state(sim);
      if (opt_mode != sim->mode) {
        set_lights_interim(sim, sim->mode, opt_mode);
        sim->interim = true;
        sim->mode = opt_mode;
        sim->last_change=sim->step_n;
      }
    }
  }

  int n = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((sim->lights[i][j] == GREEN) || (sim->lights[i][j] == YELLOW)) {
        if (buf_pop(&(sim->vehicles[i][j]), &(left[n])))
          n++;
      }
    }
  }
  return n;
}

int sim_add_vehicle(simulation *sim, vehicle v){
  return buf_push(&(sim->vehicles[v.start][v.end]), &v);
}