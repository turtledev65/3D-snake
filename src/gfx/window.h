#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include <GLFW/glfw3.h>
#include <cglm/types.h>

typedef struct {
  bool down, lastDown, pressed;
} button_t;

typedef struct {
  vec2 pos;
  vec2 delta;

  button_t buttons[GLFW_MOUSE_BUTTON_LAST];
  float    scroll;
  float    scrollDelta;
} mouse_t;

typedef struct {
  button_t keys[GLFW_KEY_LAST];
} keyboard_t;

typedef void (*FWindow)();

typedef struct {
  GLFWwindow *handle;
  mouse_t     mouse;
  keyboard_t  keyboard;

  ivec2 size;

  FWindow init, destroy, update, draw;

  float deltaTime, lastTime;
  size_t tick;
} window_t;

extern window_t window;

void window_create(FWindow init, FWindow destory, FWindow update, FWindow draw);
void window_loop();

#endif // WINDOW_H
