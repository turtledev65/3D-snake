#include <stdbool.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdlib.h>
#include <time.h>

#include "gfx/window.h"

#include "world/floor.h"
#include "world/snake.h"
#include "world/apple.h"

#include "state.h"

state_t  state;
camera_t camera;

snake_t snake;
apple_t apple;
floor_t ground;

void init()
{
  state.window = &window;

  floor_init(&ground);
  state.ground = &ground;

  camera_init(&camera, ground.scale[0] + 5);
  state.camera = &camera;

  snake_init(&snake);
  apple_init(&apple);

  srand(time(NULL));
}

void destroy() {}

void update()
{
  camera_update(&camera);
  snake_update(&snake);
  apple_update(&apple, &snake);

  for (size_t i = 1; i < snake.length - 1; i++) {
    if (snake.body[0][0] == snake.body[i][0] &&
        snake.body[0][1] == snake.body[i][1] &&
        snake.body[0][2] == snake.body[i][2])
      init();
  }
}

void draw()
{
  floor_draw(&ground);
  snake_draw(&snake);
  apple_draw(&apple);
}

int main()
{
  window_create(init, destroy, update, draw);
  window_loop();
}
