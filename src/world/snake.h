#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <cglm/types.h>

#include "gfx/vao.h"
#include "gfx/buffer.h"
#include "gfx/shader.h"

typedef struct {
  ivec3 dir;

  vec3  *body;
  size_t length;
  size_t capacity;

  vao_t    vao;
  buffer_t vbo;
  buffer_t ibo;
  shader_t shader;
} snake_t;

void snake_init(snake_t *self);
void snake_update(snake_t *self);
void snake_draw(snake_t *self);

#endif // SNAKE_H
