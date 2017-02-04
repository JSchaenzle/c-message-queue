#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "shared_state.h"
#include "module_a.h"
#include "module_b.h"

struct app_state {
  struct shared_state shared_state;
  struct module_a_state module_a_state;
  struct module_b_state module_b_state;
} app_state; 

int main(void) {
  printf("Starting Queue Test\n");

  shared_state_init(&app_state.shared_state);
  module_a_init(&app_state.shared_state, &app_state.module_a_state);
  module_b_init(&app_state.shared_state, &app_state.module_b_state);

  for(int i=0; i<100; i++) {
    module_a_do_work(&app_state.shared_state, &app_state.module_a_state);
    module_b_do_work(&app_state.shared_state, &app_state.module_b_state);
  }
  printf("Queue Test Complete\n");
}
