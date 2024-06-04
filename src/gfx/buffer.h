#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
#include <glad/glad.h>

typedef struct buffer {
  unsigned int id;
  GLenum       type;
  bool         dynamic;
} buffer_t;

void buffer_init(buffer_t *self, GLenum type, bool dynamic);
void buffer_delete(const buffer_t *self);
void buffer_bind(const buffer_t *self);

void buffer_data(const buffer_t *self, size_t size, const void *data);

#endif // BUFFER_H
