#ifndef UTILS_H
#define UTILS_H

#include "buffer.h"
#include "sim.h"
#include <stdbool.h>

/**
 * @brief Converts a string representing a cardinal direction to a `direction` enum value.
 * 
 * Accepted values are "north", "south", "east", and "west".
 * 
 * @param s Pointer to a null-terminated string representing a direction.
 * @return The corresponding `direction` enum value.
 * 
 * @note The function asserts false and terminates the program if the input is invalid.
 */

direction stringToDir(char *s);

/**
 * @brief Converts a string representing a cardinal direction to an integer index.
 * 
 * Maps "north" → 0, "east" → 1, "south" → 2, "west" → 3.
 * 
 * @param s Pointer to a null-terminated string representing a direction.
 * @return An integer in the range [0, 3] corresponding to the direction.
 * 
 * @note The function asserts false and terminates the program if the input is invalid.
 */

int dir_string_to_int(char *s);

/**
 * @brief Prints the result of a simulation step.
 * 
 * Outputs a space-separated list of vehicle IDs to the specified file descriptor,
 * preceded by the keyword "step_result".
 * 
 * Format: `step_result <id1> <id2> ... <idn>\n`
 * 
 * @param fd File descriptor to which the output should be written (e.g., 1 for stdout).
 * @param n Number of vehicles in the `left` array.
 * @param left Array of vehicles that left the intersection during the step.
 */

void print_step_result(int fd, int n, vehicle *left);

/**
 * @brief Prints the current simulation status (interim state and active mode).
 * 
 * Format: `i <interim_flag> m <mode>\n`
 * 
 * Example: `i 0 m 3`
 * 
 * @param fd File descriptor to which the output should be written.
 * @param sim Pointer to the `simulation` structure whose status is to be printed.
 */

void print_sim_status(int fd, simulation *sim);

#endif // UTILS_H