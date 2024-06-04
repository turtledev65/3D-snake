#include "camera.h"

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "state.h"

#define ROTATION_SPEED 180.0f

void camera_init(camera_t *self, float radius)
{
  glm_vec3_copy((vec3){0.0f, 0.0f, radius}, self->pos);
  glm_vec3_copy((vec3)GLM_VEC3_ZERO_INIT, self->target);
  glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, self->up);

  self->theta = 45.0f;
  self->phi   = 90.0f;

  self->fov    = 45.0f;
  self->radius = radius;

  self->pos[0] =
      cos(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius; // x
  self->pos[1] = sin(glm_rad(self->theta)) * self->radius;                // y
  self->pos[2] =
      sin(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius; // z

  glm_lookat(self->pos, self->target, self->up, self->view);
  glm_perspective(glm_rad(self->fov),
                  (float)state.window->size[0] / (float)state.window[1].size[1],
                  0.1f, 100.0f, self->projection);
}

void camera_update(camera_t *self)
{
  self->fov -= state.window->mouse.scrollDelta;
  self->fov = glm_clamp(self->fov, 1.0f, 55.0f);
  glm_perspective(glm_rad(self->fov),
                  (float)state.window->size[0] / (float)state.window->size[1],
                  0.1f, 100.0f, self->projection);

  if (!state.window->mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down)
    return;

  float dirX = glm_signf(state.window->mouse.delta[0]);
  float dirY = glm_signf(state.window->mouse.delta[1]);

  self->phi += dirX * state.window->deltaTime * ROTATION_SPEED;
  self->theta += dirY * state.window->deltaTime * ROTATION_SPEED;
  self->theta = glm_clamp(self->theta, -89.0f, 89.0f);

  self->pos[0] =
      cos(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius; // x
  self->pos[1] = sin(glm_rad(self->theta)) * self->radius;                // y
  self->pos[2] =
      sin(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius; // z

  glm_lookat(self->pos, self->target, self->up, self->view);
}
