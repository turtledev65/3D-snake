#include "apple.h"

#include "gfx/cube.h"
#include "state.h"

static float        vertices[] = CUBE_VERTICES;
static unsigned int indices[]  = CUBE_INDICES;

void apple_init(apple_t *self)
{
  int maxX = floor(state.ground->scale[0] / 2);
  int minX = -floor(state.ground->scale[0] / 2);
  int maxZ = floor(state.ground->scale[2] / 2);
  int minZ = -floor(state.ground->scale[2] / 2);

  glm_vec3_copy((vec3){(float)(rand() % (abs(maxX) + abs(minX)) + minX), 1.0f,
                       (float)(rand() % (abs(maxZ) + abs(minZ)) + minZ)},
                self->pos);

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
  shader_setVec3(&self->shader, "uColor", (vec3){1.0f, 0.0f, 0.0f});
}

void apple_update(apple_t *self, snake_t *snake)
{
  if (!(self->pos[0] == snake->body[0][0] &&
        self->pos[1] == snake->body[0][1] && self->pos[2] == snake->body[0][2]))
    return;

  if (snake->length == snake->capacity) {
    snake->capacity *= 2;
    snake->body = realloc(snake->body, snake->capacity * sizeof(vec3));
  }

  vec3 tail;
  glm_vec3_copy(snake->body[snake->length - 1], tail);
  vec3 newPos = {
      tail[0] - (float)snake->dir[0],
      tail[1] - (float)snake->dir[1],
      tail[2] - (float)snake->dir[2],
  };
  glm_vec3_copy(newPos, snake->body[snake->length++]);

  apple_init(self);
}

void apple_draw(apple_t *self)
{
  shader_use(&self->shader);
  vao_bind(&self->vao);

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, self->pos);

  shader_setMat4(&self->shader, "uModel", model);
  shader_setMat4(&self->shader, "uView", state.camera->view);
  shader_setMat4(&self->shader, "uProjection", state.camera->projection);

  glDrawElements(GL_TRIANGLES, CUBE_INDICES_LENGTH, GL_UNSIGNED_INT, NULL);
}
