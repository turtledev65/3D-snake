#ifndef APPLE_H
#define APPLE_H

#include <cglm/cglm.h>

#include "gfx/vao.h"
#include "gfx/shader.h"
#include "gfx/buffer.h"
#include "world/snake.h"

typedef struct {
  vec3 pos;

  vao_t    vao;
  buffer_t vbo;
  buffer_t ibo;
  shader_t shader;
} apple_t;

void apple_init(apple_t *self);
void apple_update(apple_t *self, snake_t *player);
void apple_draw(apple_t *self);

#endif // APPLE_H
