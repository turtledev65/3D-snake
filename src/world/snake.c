#include "snake.h"

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <math.h>

#include "cglm/vec3.h"
#include "gfx/buffer.h"
#include "gfx/cube.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "state.h"

static float        vertices[] = CUBE_VERTICES;
static unsigned int indices[]  = CUBE_INDICES;

void snake_init(snake_t *self)
{
  self->capacity = 5;
  self->body     = calloc(self->capacity, sizeof(vec3));

  glm_ivec3_copy((ivec3){0, 0, 0}, self->dir);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, self->body[0]);
  self->length = 1;

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
  shader_setVec3(&self->shader, "uColor", (vec3){0.0f, 1.0f, 0.0f});
}

void snake_update(snake_t *self)
{
  // Calculate Direction
  int dirX = state.window->keyboard.keys[GLFW_KEY_RIGHT].pressed -
             state.window->keyboard.keys[GLFW_KEY_LEFT].pressed;
  int dirZ = state.window->keyboard.keys[GLFW_KEY_UP].pressed -
             state.window->keyboard.keys[GLFW_KEY_DOWN].pressed;
  if (dirX != 0) {
    glm_ivec3_zero(self->dir);
    self->dir[0] = dirX;
  } else if (dirZ != 0) {
    glm_ivec3_zero(self->dir);
    self->dir[2] = -dirZ;
  }

  if (state.window->tick % 15 == 0) {
    for (size_t i = self->length - 1; i > 0; i--)
      glm_vec3_copy(self->body[i - 1], self->body[i]);

    self->body[0][0] += (float)self->dir[0];
    self->body[0][1] += (float)self->dir[1];
    self->body[0][2] += (float)self->dir[2];

    float maxX = floor(state.ground->scale[0] / 2.0f);
    if (self->body[0][0] > maxX)
      self->body[0][0] = -maxX;
    else if (self->body[0][0] < -maxX)
      self->body[0][0] = maxX;

    float maxZ = floor(state.ground->scale[2] / 2.0f);
    if (self->body[0][2] > maxZ)
      self->body[0][2] = -maxZ;
    else if (self->body[0][2] < -maxZ)
      self->body[0][2] = maxZ;
  }
}

void snake_draw(snake_t *self)
{
  shader_use(&self->shader);
  vao_bind(&self->vao);

  shader_setMat4(&self->shader, "uView", state.camera->view);
  shader_setMat4(&self->shader, "uProjection", state.camera->projection);

  for (size_t i = 0; i < self->length; i++) {
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, self->body[i]);
    shader_setMat4(&self->shader, "uModel", model);
    glDrawElements(GL_TRIANGLES, CUBE_INDICES_LENGTH, GL_UNSIGNED_INT, NULL);
  }
}
