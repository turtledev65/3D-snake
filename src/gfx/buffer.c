#include "buffer.h"

void buffer_init(buffer_t *self, GLenum type, bool dynamic)
{
  glGenBuffers(1, &self->id);
  self->type    = type;
  self->dynamic = dynamic;
}
void buffer_delete(const buffer_t *self) { glDeleteBuffers(1, &self->id); };
void buffer_bind(const buffer_t *self) { glBindBuffer(self->type, self->id); };

void buffer_data(const buffer_t *self, size_t size, const void *data)
{
  buffer_bind(self);
  glBufferData(self->type, size, data,
               self->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
