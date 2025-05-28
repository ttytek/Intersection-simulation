#ifndef SIM_H
#define SIM_H

#include "buffer.h"

#include <stdbool.h>

#define STATES 9

#ifndef MIN_LIGHT_DURATION
#define MIN_LIGHT_DURATION 4
#endif

/**
 * @brief Represents the state of the traffic intersection simulation.
 */
typedef struct simulation {
    v_buffer vehicles[4][4]; /**< 4x4 matrix of vehicle buffers (per direction/turn). */
    bool interim;            /**< Flag indicating if lights are in an interim state. */
    int mode;                /**< Current active traffic light mode (state index). */
    int last_change;         /**< # of step in which the last mode change occured. */
    int step_n;              /**< Number of steps elapsed since the start of simulation. */
    state lights[4][4];      /**< 4x4 matrix representing the current light colors. */
} simulation;

/**
 * @brief Initializes the simulation structure.
 * 
 * Sets all vehicle buffers to empty, lights to RED, and resets the mode and interim flag.
 * 
 * @param sim Pointer to the simulation object to initialize.
 */

void simulation_init(simulation *sim);

/**
 * @brief Calculates the number of vehicles that could move in a given traffic light state.
 * 
 * Iterates through the vehicle buffers and sums the vehicle count in positions where the
 * given state allows passage.
 * 
 * @param sim Pointer to the simulation object.
 * @param n Index of the traffic light state to evaluate.
 * @return The total number of vehicles eligible to move in this state.
 */

int calculate_state_value(simulation *sim, int n);

/**
 * @brief Determines the optimal traffic light state based on vehicle counts.
 * 
 * Evaluates all possible states and returns the one that would allow the
 * highest number of vehicles to move.
 * 
 * @param sim Pointer to the simulation object.
 * @return Index of the optimal traffic light state.
 */

int calculate_optimal_state(simulation *sim);

/**
 * @brief Sets all traffic lights to match a given state.
 * 
 * Sets lights to GREEN or RED based on whether a movement is allowed in the state.
 * 
 * @param sim Pointer to the simulation object.
 * @param mode Index of the state to apply to the lights.
 */

void set_lights(simulation *sim, int mode);

/**
 * @brief Sets traffic lights to an interim transition state between two modes.
 * 
 * This handles realistic light transitions: REDYELLOW, YELLOW, RED, GREEN.
 * 
 * @param sim Pointer to the simulation object.
 * @param prev Index of the previous light mode.
 * @param mode Index of the new light mode to transition to.
 */

void set_lights_interim(simulation *sim, int prev, int mode);

/**
 * @brief Executes a simulation step.
 * 
 * Updates light states (interim or direct switch) and removes vehicles allowed
 * to move under current light conditions.
 * 
 * @param sim Pointer to the simulation object.
 * @param left Array where popped (leaving the intersection) vehicles will be stored.
 * @return Number of vehicles that moved in this step.
 */

int sim_step(simulation *sim, vehicle *left);

#endif // SIM_H