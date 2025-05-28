#include "buffer.h"
#include <string.h>

void buf_init(v_buffer *buf) { buf->head = buf->tail = buf->count = 0; }

int buf_push(v_buffer *buf, const vehicle *v) {
  if (buf->count == BUFFER_SIZE)
    return 0;              // bufor pełny
  buf->vs[buf->head] = *v; // struktura kopiowana
  buf->head = (buf->head + 1) % BUFFER_SIZE;
  buf->count++;
  return 1;
}

int buf_pop(v_buffer *buf, vehicle *out) {
  if (buf->count == 0)
    return 0; // bufor pusty
  *out = buf->vs[buf->tail];
  buf->tail = (buf->tail + 1) % BUFFER_SIZE;
  buf->count--;
  return 1;
}

int buf_count(v_buffer *buf) { return buf->count; }

int buf_first(v_buffer *buf, vehicle *out) {
  if (buf->count == 0)
    return 0; // bufor pusty
  *out = buf->vs[buf->tail];
  return 1;
}

char buf_nth_v_id(v_buffer *buf, int n) {
  char *id = buf->vs[(buf->tail + n) % BUFFER_SIZE].id;
  return id[strlen(id) - 1];
}