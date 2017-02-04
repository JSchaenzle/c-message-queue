#ifndef MODULE_A_H
#define MODULE_A_H
#include <stdint.h>
#include "shared_state.h"

struct module_a_state {
  uint8_t foo;
  uint32_t bar;
};

void module_a_init(struct shared_state * p_shared_state, struct module_a_state * p_state);

void module_a_do_work(struct shared_state * p_shared_state, struct module_a_state * p_state);

#endif