#include "window.h"

#include <stdlib.h>
#include <stdio.h>

#include "GLFW/glfw3.h"
#include "cglm/vec2.h"
#include "glad/glad.h"

#include "../settings.h"

window_t window;

static void _resizeCallback(GLFWwindow *handle, int width, int height);
static void _keyCallback(GLFWwindow *handle, int key, int scancode, int action,
                         int mods);
static void _cursorCallback(GLFWwindow *handle, double xPos, double yPos);
static void _mouseBtnCallback(GLFWwindow *handle, int button, int action,
                              int mods);
static void _scrollCallback(GLFWwindow *handle, double xOffset, double yOffset);

static void _draw();
static void _update();
static void _destroy();

void window_create(FWindow init, FWindow destory, FWindow update, FWindow draw)
{
  window.init    = init;
  window.destroy = destory;
  window.update  = update;
  window.draw    = draw;

  window.size[0] = WINDOW_WIDTH;
  window.size[1] = WINDOW_HEIGHT;

  window.deltaTime = 0.0f;
  window.lastTime  = 0.0f;

  window.tick = 0;

  window.mouse.scroll      = 0.0f;
  window.mouse.scrollDelta = 0.0f;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifdef __linux__
  glfwWindowHintString(GLFW_X11_CLASS_NAME, "float");
  glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "float");
#endif

  window.handle =
      glfwCreateWindow(window.size[0], window.size[1], "3D Snake", NULL, NULL);

  if (window.handle == NULL) {
    fprintf(stderr, "ERROR: Failed to create GLFW window!\n");
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window.handle);

  if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) {
    fprintf(stderr, "ERROR: Failed to initialize GLAD\n");
    exit(EXIT_FAILURE);
  }

  glViewport(0, 0, window.size[0], window.size[1]);
  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(window.handle, _resizeCallback);
  glfwSetKeyCallback(window.handle, _keyCallback);
  glfwSetCursorPosCallback(window.handle, _cursorCallback);
  glfwSetScrollCallback(window.handle, _scrollCallback);
  glfwSetMouseButtonCallback(window.handle, _mouseBtnCallback);
}

void window_loop()
{
  window.init();

  while (!glfwWindowShouldClose(window.handle)) {
    // Calculate Delta Time
    float currTime   = glfwGetTime();
    window.deltaTime = currTime - window.lastTime;
    window.lastTime  = currTime;

    // Input
    if (window.keyboard.keys[GLFW_KEY_ESCAPE].pressed ||
        window.keyboard.keys[GLFW_KEY_Q].pressed)
      glfwSetWindowShouldClose(window.handle, true);

    _update();
    _draw();

    glfwPollEvents();
    glfwSwapBuffers(window.handle);
  }

  _destroy();
}

static void _updateButtons(button_t *buttons, size_t n)
{
  for (size_t i = 0; i < n; i++) {
    buttons[i].pressed  = buttons[i].down && !buttons[i].lastDown;
    buttons[i].lastDown = buttons[i].down;
  }
}

static void _update()
{
  _updateButtons(window.keyboard.keys, GLFW_KEY_LAST);
  _updateButtons(window.mouse.buttons, GLFW_MOUSE_BUTTON_LAST);
  window.update();

  window.mouse.scrollDelta = 0.0f;
  glm_vec2_zero(window.mouse.delta);
}

static void _draw()
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.4f, 0.9f, 1.0f);
  window.tick ++;
  window.draw();
}

static void _destroy()
{
  glfwTerminate();
  window.destroy();
}

static void _resizeCallback(GLFWwindow *handle, int width, int height)
{
  glViewport(0, 0, width, height);
  window.size[0] = width;
  window.size[1] = height;
}

static void _keyCallback(GLFWwindow *handle, int key, int scancode, int action,
                         int mods)
{
  if (key < 0)
    return;

  switch (action) {
  case GLFW_PRESS:
    window.keyboard.keys[key].down = true;
    break;
  case GLFW_RELEASE:
    window.keyboard.keys[key].down = false;
    break;
  default:
    break;
  }
}

static void _cursorCallback(GLFWwindow *handle, double xPos, double yPos)
{
  vec2 newPos = {xPos, yPos};
  glm_vec2_sub(newPos, window.mouse.pos, window.mouse.delta);
  glm_vec2_copy(newPos, window.mouse.pos);
}

static void _mouseBtnCallback(GLFWwindow *handle, int button, int action,
                              int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    switch (action) {
    case GLFW_PRESS:
      window.mouse.buttons[button].down = true;
      break;
    case GLFW_RELEASE:
      window.mouse.buttons[button].down = false;
      break;
    default:
      break;
    }
  }
}

static void _scrollCallback(GLFWwindow *handle, double xOffset, double yOffset)
{
  float newScroll          = window.mouse.scroll + yOffset;
  window.mouse.scrollDelta = newScroll - window.mouse.scroll;
  window.mouse.scroll      = newScroll;
}
