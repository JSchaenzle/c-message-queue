#ifndef MODULE_B_H
#define MODULE_B_H
#include <stdint.h>
#include "shared_state.h"

struct module_b_state {
  uint16_t baz;
};

void module_b_init(struct shared_state * p_shared_state, struct module_b_state * p_state);

void module_b_do_work(struct shared_state * p_shared_state, struct module_b_state * p_state);

#endif