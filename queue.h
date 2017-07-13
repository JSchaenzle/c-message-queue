#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

enum enqueue_result {
  ENQUEUE_RESULT_SUCCESS,
  ENQUEUE_RESULT_FULL,
};

enum dequeue_result {
  DEQUEUE_RESULT_SUCCESS,
  DEQUEUE_RESULT_EMPTY,
};

#define ARRAY_LENGTH(A) (sizeof(A)/sizeof((A)[0])) 

#define QUEUE_DECLARATION(NAME, ITEM_TYPE, NUM_ITEMS)                                   \
struct NAME {                                                                           \
  uint16_t read_idx;                                                                    \
  uint16_t write_idx;                                                                   \
  ITEM_TYPE items[NUM_ITEMS];                                                           \
};                                                                                      \
void NAME ## _init(struct NAME * p_queue);                                              \
enum enqueue_result NAME ##_enqueue(struct NAME * p_queue, ITEM_TYPE * p_new_item);     \
enum dequeue_result NAME ##_dequeue(struct NAME * p_queue, ITEM_TYPE * p_item_out);     \
bool NAME ##_is_empty(struct NAME * p_queue);

#define QUEUE_DEFINITION(NAME, ITEM_TYPE)                                               \
void NAME ## _init(struct NAME * p_queue)                                               \
{                                                                                       \
  p_queue->read_idx = 0;                                                                \
  p_queue->write_idx = 0;                                                               \
}                                                                                       \
                                                                                        \
enum enqueue_result NAME ##_enqueue(struct NAME  * p_queue, ITEM_TYPE * p_new_item) {   \
  uint16_t elements_in = p_queue->write_idx - p_queue->read_idx;                        \
                                                                                        \
  size_t const capacity = ARRAY_LENGTH(p_queue->items);                                 \
  if (elements_in == capacity) {                                                        \
    return ENQUEUE_RESULT_FULL;                                                         \
  }                                                                                     \
                                                                                        \
  uint16_t i = (p_queue->write_idx)++ & (capacity - 1);                                 \
  p_queue->items[i] = *p_new_item;                                                      \
  return ENQUEUE_RESULT_SUCCESS;                                                        \
}                                                                                       \
                                                                                        \
enum dequeue_result NAME ##_dequeue(struct NAME * p_queue, ITEM_TYPE * p_item_out) {    \
  uint16_t elements_in = p_queue->write_idx - p_queue->read_idx;                        \
  size_t const capacity = ARRAY_LENGTH(p_queue->items);                                 \
                                                                                        \
  if(elements_in == 0) {                                                                \
    return DEQUEUE_RESULT_EMPTY;                                                        \
  }                                                                                     \
                                                                                        \
  uint16_t i = (p_queue->read_idx)++ & (capacity - 1);                                  \
  *p_item_out = p_queue->items[i];                                                      \
                                                                                        \
  return DEQUEUE_RESULT_SUCCESS;                                                        \
}                                                                                       \
                                                                                        \
bool NAME ##_is_empty(struct NAME * p_queue) {                                          \
  return ((p_queue->write_idx - p_queue->read_idx) == 0);                               \
}


#endif
