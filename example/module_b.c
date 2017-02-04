#include "module_b.h"
#include <stdio.h>

void module_b_init(struct shared_state * p_shared_state, struct module_b_state * p_state) {
  *p_state = (struct module_b_state){
    .baz = 17
  };
}

void module_b_do_work(struct shared_state * p_shared_state, struct module_b_state * p_state) {
  printf("Attempting to enqueue msg... ");
  struct uart_msg new_msg = {
    .msg = {1,2,3,4,5,1,2,3,4,5,1,2,3,4,5}
  };
  enum enqueue_result result = uart_msg_queue_enqueue(&p_shared_state->uart_msg_queue, &new_msg);
  if (result == ENQUEUE_RESULT_SUCCESS) {
    printf("Success!\n");
  } else {
    printf("Fail - QUEUE IS FULL!\n");
  }

}
