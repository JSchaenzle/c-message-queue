// unit tests
#include "greatest.h"
#include "../queue.h"
#include <stdint.h>

QUEUE_DECLARATION(test_int_queue, uint32_t, 8);
QUEUE_DEFINITION(test_int_queue, uint32_t, 8);

TEST queue_works_with_integers(void) {
  struct test_int_queue q;
  test_int_queue_init(&q);

  ASSERT_EQ(true, test_int_queue_is_empty(&q));

  // Test Enqueue
  for (uint32_t i=0; i<8; i++) {
    enum enqueue_result r = test_int_queue_enqueue(&q, &i);
    ASSERT_EQ(ENQUEUE_RESULT_SUCCESS, r);
    ASSERT_EQ(false, test_int_queue_is_empty(&q));
  }

  // See that we can't enqueue after the queue is full
  uint32_t v = 55;
  enum enqueue_result r = test_int_queue_enqueue(&q, &v);
  ASSERT_EQ(ENQUEUE_RESULT_FULL, r);

  // Test Dequeue
  for (uint32_t i=0; i<8; i++) {
    uint32_t v2;
    ASSERT_EQ(false, test_int_queue_is_empty(&q));
    enum dequeue_result r = test_int_queue_dequeue(&q, &v2);
    ASSERT_EQ(DEQUEUE_RESULT_SUCCESS, r);
    ASSERT_EQ(i, v2);
  }
  // See that we can't dequeue after the queue is empty
  uint32_t v3;
  enum dequeue_result dr = test_int_queue_dequeue(&q, &v3);
  ASSERT_EQ(DEQUEUE_RESULT_EMPTY, dr);
  ASSERT_EQ(true, test_int_queue_is_empty(&q));

  PASS();
}

struct test_struct {
  uint8_t foo[13]; //awkward sized buffer
};
QUEUE_DECLARATION(test_struct_queue, struct test_struct, 16);
QUEUE_DEFINITION(test_struct_queue, struct test_struct, 16);

TEST queue_works_for_structs(void) {
  struct test_struct_queue q;
  test_struct_queue_init(&q);

  ASSERT_EQ(true, test_struct_queue_is_empty(&q));
  // Test Enqueue
  for (uint32_t i=0; i<16; i++) {
    struct test_struct v = {
      .foo = {i,i,i,i,i,i,i,i,i,i,i,i,i}
    };
    enum enqueue_result r = test_struct_queue_enqueue(&q, &v);
    ASSERT_EQ(ENQUEUE_RESULT_SUCCESS, r);
    ASSERT_EQ(false, test_struct_queue_is_empty(&q));
  }

  // See that we can't enqueue after the queue is full
  struct test_struct v;
  enum enqueue_result r = test_struct_queue_enqueue(&q, &v);
  ASSERT_EQ(ENQUEUE_RESULT_FULL, r);

  // Test Dequeue
  for (uint32_t i=0; i<16; i++) {
    struct test_struct v2;
    ASSERT_EQ(false, test_struct_queue_is_empty(&q));
    enum dequeue_result r = test_struct_queue_dequeue(&q, &v2);
    ASSERT_EQ(DEQUEUE_RESULT_SUCCESS, r);
    for (int j=0; j<13; j++) {
      ASSERT_EQ(i, v2.foo[j]);
    }
  }
  // See that we can't dequeue after the queue is empty
  struct test_struct v3;
  enum dequeue_result dr = test_struct_queue_dequeue(&q, &v3);
  ASSERT_EQ(DEQUEUE_RESULT_EMPTY, dr);
  ASSERT_EQ(true, test_struct_queue_is_empty(&q));

  PASS();
}

TEST queue_works_when_read_and_write_pointers_overflow(void) {
  struct test_int_queue q;
  test_int_queue_init(&q);

  ASSERT_EQ(true, test_int_queue_is_empty(&q));
  for (int cycle = 0; cycle<40000; cycle++) {
    // Test Enqueue
    for (uint32_t i=0; i<8; i++) {
      enum enqueue_result r = test_int_queue_enqueue(&q, &i);
      ASSERT_EQ(ENQUEUE_RESULT_SUCCESS, r);
      ASSERT_EQ(false, test_int_queue_is_empty(&q));
    }

    // See that we can't enqueue after the queue is full
    uint32_t v = 55;
    enum enqueue_result r = test_int_queue_enqueue(&q, &v);
    ASSERT_EQ(ENQUEUE_RESULT_FULL, r);

    // Test Dequeue
    for (uint32_t i=0; i<8; i++) {
      uint32_t v2;
      ASSERT_EQ(false, test_int_queue_is_empty(&q));
      enum dequeue_result r = test_int_queue_dequeue(&q, &v2);
      ASSERT_EQ(DEQUEUE_RESULT_SUCCESS, r);
      ASSERT_EQ(i, v2);
    }
    // See that we can't dequeue after the queue is empty
    uint32_t v3;
    enum dequeue_result dr = test_int_queue_dequeue(&q, &v3);
    ASSERT_EQ(DEQUEUE_RESULT_EMPTY, dr);
    ASSERT_EQ(true, test_int_queue_is_empty(&q));
  }
  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite) {
    RUN_TEST(queue_works_with_integers);
    RUN_TEST(queue_works_for_structs);
    RUN_TEST(queue_works_when_read_and_write_pointers_overflow);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */

    RUN_SUITE(the_suite);

    GREATEST_MAIN_END();        /* display results */
}
