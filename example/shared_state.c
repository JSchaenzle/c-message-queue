#include "shared_state.h"

QUEUE_DEFINITION(uart_msg_queue, struct uart_msg);
/*
  The above macro provides implementations of:
   uart_msg_queue_init()
   uart_msg_queue_enqueue()
   uart_msg_queue_dequeue()
*/

void shared_state_init(struct shared_state * const p_state) {
  uart_msg_queue_init(&p_state->uart_msg_queue);
}
