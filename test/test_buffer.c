#include "unity.h"
#include "buffer.h"  // replace with the actual filename
#include <string.h>

// Example config
#define BUFFER_SIZE 4
#define ID_LEN 10

// Sample vehicle factory
vehicle make_vehicle(const char* id, direction start, direction end) {
    vehicle v;
    strncpy(v.id, id, ID_LEN);
    v.id[ID_LEN] = '\0'; // Ensure null-termination
    v.start = start;
    v.end = end;
    return v;
}

void test_buf_init_should_reset_buffer_state(void) {
    v_buffer buf;
    buf.head = 2; buf.tail = 1; buf.count = 3;
    buf_init(&buf);
    TEST_ASSERT_EQUAL_INT(0, buf.head);
    TEST_ASSERT_EQUAL_INT(0, buf.tail);
    TEST_ASSERT_EQUAL_INT(0, buf.count);
}

void test_buf_push_should_add_vehicle_to_buffer(void) {
    v_buffer buf;
    buf_init(&buf);
    vehicle v = make_vehicle("CAR123", NORTH, EAST);

    int result = buf_push(&buf, &v);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(1, buf.count);
    TEST_ASSERT_EQUAL_STRING("CAR123", buf.vs[0].id);
}

void test_buf_pop_should_remove_vehicle_from_buffer(void) {
    v_buffer buf;
    buf_init(&buf);
    vehicle v1 = make_vehicle("CAR123", NORTH, EAST);
    vehicle out;

    buf_push(&buf, &v1);
    int result = buf_pop(&buf, &out);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(0, buf.count);
    TEST_ASSERT_EQUAL_STRING("CAR123", out.id);
}

void test_buf_push_should_fail_when_full(void) {
    v_buffer buf;
    buf_init(&buf);

    for (int i = 0; i < BUFFER_SIZE; i++) {
        char id[ID_LEN+1];
        snprintf(id, sizeof(id), "CAR%d", i);
        vehicle v = make_vehicle(id, NORTH, EAST);
        TEST_ASSERT_EQUAL_INT(1, buf_push(&buf, &v));
    }

    vehicle extra = make_vehicle("EXTRA", SOUTH, WEST);
    TEST_ASSERT_EQUAL_INT(0, buf_push(&buf, &extra)); // should fail
}

void test_buf_pop_should_fail_when_empty(void) {
    v_buffer buf;
    buf_init(&buf);
    vehicle out;
    TEST_ASSERT_EQUAL_INT(0, buf_pop(&buf, &out));
}

void test_buf_first_should_return_first_vehicle(void) {
    v_buffer buf;
    buf_init(&buf);
    vehicle v1 = make_vehicle("FIRST", NORTH, EAST);
    vehicle v2 = make_vehicle("SECOND", SOUTH, WEST);
    vehicle out;

    buf_push(&buf, &v1);
    buf_push(&buf, &v2);

    TEST_ASSERT_EQUAL_INT(1, buf_first(&buf, &out));
    TEST_ASSERT_EQUAL_STRING("FIRST", out.id);
}

void test_buf_nth_v_id_should_return_last_char_of_nth_id(void) {
    v_buffer buf;
    buf_init(&buf);
    buf_push(&buf, &(vehicle){ .id = "ABC123" });
    buf_push(&buf, &(vehicle){ .id = "XYZ789" });

    TEST_ASSERT_EQUAL_CHAR('3', buf_nth_v_id(&buf, 0));
    TEST_ASSERT_EQUAL_CHAR('9', buf_nth_v_id(&buf, 1));
}
