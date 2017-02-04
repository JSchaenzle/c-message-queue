#include "module_a.h"
#include <stdio.h>

void module_a_init(struct shared_state * p_shared_state, struct module_a_state * p_state) {
  *p_state = (struct module_a_state){
    .foo = 4,
    .bar = 6,
  };
}


void module_a_do_work(struct shared_state * p_shared_state, struct module_a_state * p_state) {
  struct uart_msg next_msg;
  enum dequeue_result result = uart_msg_queue_dequeue(&p_shared_state->uart_msg_queue, &next_msg);
  if (result == DEQUEUE_RESULT_SUCCESS) {
    printf("Dequeued a message!\n");
  } else {
    printf("Queue is empty.\n");
  }

}