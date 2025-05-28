#include "unity.h"
#include "sim.h" // contains simulation struct and functions
#include <string.h>

// Create a mock simulation for tests
simulation sim;

void test_simulation_init_should_set_defaults(void) {
    simulation_init(&sim, 0);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(0, sim.mode);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            TEST_ASSERT_EQUAL_INT(0, buf_count(&sim.vehicles[i][j]));
            TEST_ASSERT_EQUAL_INT(RED, sim.lights[i][j]);
        }
    }
}

void test_calculate_state_value_should_sum_correctly(void) {
    simulation_init(&sim, 0);
    vehicle v = { .id = "CAR1", .start = NORTH, .end = EAST };
    buf_push(&sim.vehicles[0][0], &v); // depends on state[1][0][0] being true
    buf_push(&sim.vehicles[0][1], &v); // state[1][0][1] true

    int count = calculate_state_value(&sim, 1);
    TEST_ASSERT_EQUAL_INT(2, count);
}

void test_calculate_optimal_state_returns_max_buffer_state(void) {
    simulation_init(&sim, 0);
    vehicle v = { .id = "CAR1", .start = NORTH, .end = EAST };
    for (int i = 0; i < 5; i++) buf_push(&sim.vehicles[2][2], &v); // only active in state 3

    int best = calculate_optimal_state(&sim);
    TEST_ASSERT_EQUAL_INT(3, best); // state 3 activates [2][2]
}

void test_set_lights_sets_correctly(void) {
    simulation_init(&sim, 0);
    set_lights(&sim, 1); // state 1 sets all [0][*] to GREEN
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT_EQUAL(GREEN, sim.lights[0][i]);
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            TEST_ASSERT_EQUAL(RED, sim.lights[i][j]);
        }
    }
}

void test_set_lights_interim_sets_transitional_states(void) {
    simulation_init(&sim, 0);
    set_lights(&sim, 1); // Start with mode 1
    set_lights_interim(&sim, 1, 2); // Transition to mode 2

    // lights[0][0] was green in 1, now false in 2 → should be YELLOW
    TEST_ASSERT_EQUAL(YELLOW, sim.lights[0][0]);

    // lights[1][0] was false in 1, now true in 2 → should be REDYELLOW
    TEST_ASSERT_EQUAL(REDYELLOW, sim.lights[1][0]);

    // lights[2][2] is false in both → should be RED
    TEST_ASSERT_EQUAL(RED, sim.lights[2][2]);

    // lights[0][1] is green in 1, false in 2 → should be YELLOW
    TEST_ASSERT_EQUAL(YELLOW, sim.lights[0][1]);
}

void test_sim_step_transitions_and_pops(void) {
    simulation_init(&sim, 0);
    vehicle v1 = { .id = "V1" };
    buf_push(&sim.vehicles[0][0], &v1); // state 1 allows this
    sim.mode = 1; // active state 1
    set_lights(&sim, 1);

    vehicle popped[4];
    int popped_count = sim_step(&sim, popped);
    TEST_ASSERT_EQUAL_INT(1, popped_count);
    TEST_ASSERT_EQUAL_STRING("V1", popped[0].id);
}

#undef MIN_LIGHT_DURATION
#define MIN_LIGHT_DURATION 0

void test_lights_change_often_when_min_light_duration_is_0(void) {
    vehicle left[10];
    simulation_init(&sim, 0);
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN1", .start = NORTH, .end = EAST });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN2", .start = NORTH, .end = SOUTH });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN3", .start = NORTH, .end = WEST });
    sim_step(&sim, left);
    TEST_ASSERT_TRUE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS1", .start = SOUTH, .end = EAST });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS2", .start = SOUTH, .end = NORTH });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS3", .start = SOUTH, .end = WEST });

    sim_step(&sim, left);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);

    sim_step(&sim, left);
    TEST_ASSERT_TRUE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 3);
}

void test_lights_dont_change_often_when_min_light_duration_is_4(void){
    vehicle left[10];
    simulation_init(&sim, 4);
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN1", .start = NORTH, .end = EAST });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN2", .start = NORTH, .end = SOUTH });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARN3", .start = NORTH, .end = WEST });
    sim_step(&sim, left);
    TEST_ASSERT_TRUE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS1", .start = SOUTH, .end = EAST });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS2", .start = SOUTH, .end = NORTH });
    sim_add_vehicle(&sim, (vehicle){ .id = "CARS3", .start = SOUTH, .end = WEST });

    sim_step(&sim, left);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);

    sim_step(&sim, left);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);

    sim_step(&sim, left);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);

    sim_step(&sim, left);
    TEST_ASSERT_FALSE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 1);

    sim_step(&sim, left);
    TEST_ASSERT_TRUE(sim.interim);
    TEST_ASSERT_EQUAL_INT(sim.mode, 3);

}