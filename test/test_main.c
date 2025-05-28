#include "unity.h"

extern void test_buf_init_should_reset_buffer_state(void);
extern void test_buf_push_should_add_vehicle_to_buffer(void);
extern void test_buf_pop_should_remove_vehicle_from_buffer(void);
extern void test_buf_push_should_fail_when_full(void);
extern void test_buf_pop_should_fail_when_empty(void);
extern void test_buf_first_should_return_first_vehicle(void);
extern void test_buf_nth_v_id_should_return_last_char_of_nth_id(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_buf_init_should_reset_buffer_state);
    RUN_TEST(test_buf_push_should_add_vehicle_to_buffer);
    RUN_TEST(test_buf_pop_should_remove_vehicle_from_buffer);
    RUN_TEST(test_buf_push_should_fail_when_full);
    RUN_TEST(test_buf_pop_should_fail_when_empty);
    RUN_TEST(test_buf_first_should_return_first_vehicle);
    RUN_TEST(test_buf_nth_v_id_should_return_last_char_of_nth_id);

    return UNITY_END();
}