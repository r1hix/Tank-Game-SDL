#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

bool isRunning = false;

int main(void) {
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
    // Update the screen
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}