#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>
#include <cglm/types.h>

typedef struct {
  vec3 pos;
  vec3 target;
  vec3 up;

  float theta;
  float phi;

  float fov;
  float radius;

  mat4 view;
  mat4 projection;
} camera_t;

void camera_init(camera_t *self, float radius);
void camera_update(camera_t *self);

#endif // CAMERA_H
