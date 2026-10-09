#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool isRunning = false;

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

typedef struct Vector2 {
  float x;
  float y;
} Vector2;

typedef struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

const Color RED = {.r = 255, .g = 0, .b = 0, .a = 255};
const Color BLUE = {.r = 0, .g = 0, .b = 255, .a = 255};

const int TANK_WIDTH = 100;
const int TANK_HEIGHT = 70;
const float TANK_SPEED = 5.0f;
const float TANK_ROTATION_SPEED = 2.0f;

Color tank1Color = RED;
Color tank2Color = BLUE;

int main(void) {
  SDL_FRect tank1 = {
      .x = 100,
      .y = SCREEN_HEIGHT / 2.0f - TANK_HEIGHT / 2.0f,
      .w = TANK_WIDTH,
      .h = TANK_HEIGHT,
  };

  SDL_FRect tank2 = {
      .x = SCREEN_WIDTH - TANK_WIDTH - 100,
      .y = SCREEN_HEIGHT / 2.0f - TANK_HEIGHT / 2.0f,
      .w = TANK_WIDTH,
      .h = TANK_HEIGHT,
  };

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("%s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  isRunning = true;

  SDL_Window *window =
      SDL_CreateWindow("Tank Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (window == NULL) {
    printf("%s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    printf("%s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_SetRenderVSync(renderer, 1);

  SDL_Event event;
  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
    }

    // Set background color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Clear the screen with the background color
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, tank1Color.r, tank1Color.g, tank1Color.b,
                           tank1Color.a);
    SDL_RenderFillRect(renderer, &tank1);
    SDL_SetRenderDrawColor(renderer, tank2Color.r, tank2Color.g, tank2Color.b,
                           tank2Color.a);
    SDL_RenderFillRect(renderer, &tank2);
    // Update the screen
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}