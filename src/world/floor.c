#include "floor.h"

#include <cglm/cglm.h>

#include "state.h"
#include "gfx/buffer.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "gfx/cube.h"

static float        vertices[] = CUBE_VERTICES;
static unsigned int indices[]  = CUBE_INDICES;

void floor_init(floor_t *self)
{
  self->scale[0] = 15.0f;
  self->scale[1] = 1.0f;
  self->scale[2] = 15.0f;

  vao_init(&self->vao);
  vao_bind(&self->vao);

  buffer_init(&self->vbo, GL_ARRAY_BUFFER, false);
  buffer_data(&self->vbo, sizeof(vertices), vertices);

  buffer_init(&self->ibo, GL_ELEMENT_ARRAY_BUFFER, false);
  buffer_data(&self->ibo, sizeof(indices), indices);

  vao_attribPointer(&self->vao, &self->vbo, 0, 3, GL_FLOAT, 0, 0);

  shader_initFromFiles(&self->shader, "src/shaders/solid-color.vs",
                       "src/shaders/solid-color.fs");

  shader_use(&self->shader);
  shader_setVec3(&self->shader, "uColor", (vec3){0.82f, 0.82f, 0.82f});

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_scale(model, self->scale);
  shader_setMat4(&self->shader, "uModel", model);
}

void floor_draw(const floor_t *self)
{
  shader_use(&self->shader);
  vao_bind(&self->vao);

  shader_setMat4(&self->shader, "uView", state.camera->view);
  shader_setMat4(&self->shader, "uProjection", state.camera->projection);

  glDrawElements(GL_TRIANGLES, CUBE_INDICES_LENGTH, GL_UNSIGNED_INT, NULL);
}
