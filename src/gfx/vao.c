#include "vao.h"

void vao_init(vao_t *self) { glCreateVertexArrays(1, &self->id); }
void vao_delete(const vao_t *self) { glDeleteVertexArrays(1, &self->id); }
void vao_bind(const vao_t *self) { glBindVertexArray(self->id); };

void vao_attribPointer(const vao_t *self, const buffer_t *vbo, GLuint index,
                       GLint size, GLenum type, GLsizei stride, size_t offset)
{
  vao_bind(self);
  buffer_bind(vbo);

  glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
  glEnableVertexAttribArray(index);
}
