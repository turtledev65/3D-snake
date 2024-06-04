#ifndef FLOOR_H
#define FLOOR_H

#include <cglm/types.h>

#include "gfx/vao.h"
#include "gfx/buffer.h"
#include "gfx/shader.h"

typedef struct {
  buffer_t vbo;
  buffer_t ibo;
  vao_t    vao;
  shader_t shader;

  vec3 pos;
  vec3 scale;
} floor_t;

void floor_init(floor_t *self);
void floor_draw(const floor_t *self);

#endif // FLOOR_H
