#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

extern void test_buf_init_should_reset_buffer_state(void);
extern void test_buf_push_should_add_vehicle_to_buffer(void);
extern void test_buf_pop_should_remove_vehicle_from_buffer(void);
extern void test_buf_push_should_fail_when_full(void);
extern void test_buf_pop_should_fail_when_empty(void);
extern void test_buf_first_should_return_first_vehicle(void);
extern void test_buf_nth_v_id_should_return_last_char_of_nth_id(void);

extern void test_simulation_init_should_set_defaults(void);
extern void test_calculate_state_value_should_sum_correctly(void);
extern void test_calculate_optimal_state_returns_max_buffer_state(void);
extern void test_set_lights_sets_correctly(void);
extern void test_set_lights_interim_sets_transitional_states(void);
extern void test_sim_step_transitions_and_pops(void);
extern void test_lights_change_often_when_min_light_duration_is_0(void);
extern void test_lights_dont_change_often_when_min_light_duration_is_4(void);

void run_buffer_tests(void){
    RUN_TEST(test_buf_init_should_reset_buffer_state);
    RUN_TEST(test_buf_push_should_add_vehicle_to_buffer);
    RUN_TEST(test_buf_pop_should_remove_vehicle_from_buffer);
    RUN_TEST(test_buf_push_should_fail_when_full);
    RUN_TEST(test_buf_pop_should_fail_when_empty);
    RUN_TEST(test_buf_first_should_return_first_vehicle);
    RUN_TEST(test_buf_nth_v_id_should_return_last_char_of_nth_id);
}

void run_simulation_tests(void){
    RUN_TEST(test_simulation_init_should_set_defaults);
    RUN_TEST(test_calculate_state_value_should_sum_correctly);
    RUN_TEST(test_calculate_optimal_state_returns_max_buffer_state);
    RUN_TEST(test_set_lights_sets_correctly);
    RUN_TEST(test_set_lights_interim_sets_transitional_states);
    RUN_TEST(test_sim_step_transitions_and_pops);
    RUN_TEST(test_lights_change_often_when_min_light_duration_is_0);
    RUN_TEST(test_lights_dont_change_often_when_min_light_duration_is_4);
}

int main(void) {
    UNITY_BEGIN();

    run_buffer_tests();
    run_simulation_tests();

    return UNITY_END();
}