#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "buffer.h"

typedef struct vao {
  unsigned int id;
} vao_t;

void vao_init(vao_t *self);
void vao_delete(const vao_t *self);
void vao_bind(const vao_t *self);

void vao_attribPointer(const vao_t *self, const buffer_t *vbo, GLuint index,
                GLint size, GLenum type, GLsizei stride, size_t offset);

#endif // VAO_H
