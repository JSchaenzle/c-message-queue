#ifndef SHARED_STATE_H
#define SHARED_STATE_H
#include <stdint.h>
#include "queue.h"

struct uart_msg {
  uint8_t msg[25];
};

QUEUE_DECLARATION(uart_msg_queue, struct uart_msg, 4);
/*
  The above macro provides declarations of:
   uart_msg_queue_init()
   uart_msg_queue_enqueue()
   uart_msg_queue_dequeue()
*/

struct shared_state {
  struct uart_msg_queue uart_msg_queue;
};

void shared_state_init(struct shared_state * const p_state);

#endif