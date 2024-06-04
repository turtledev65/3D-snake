#ifndef STATE_H
#define STATE_H

#include "gfx/camera.h"
#include "gfx/window.h"
#include "world/floor.h"

typedef struct {
  window_t *window;
  camera_t *camera;
  floor_t *ground;
} state_t;

extern state_t state;

#endif // STATE_H
