#include <SDL3/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool isRunning = false;

float radToDeg(float rad) { return rad * (180 / M_PI); }
float degToRad(float deg) { return deg * (M_PI / 180); }

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

typedef struct Vector {
  float x;
  float y;
} Vector;

const SDL_Color RED = {.r = 255, .g = 0, .b = 0, .a = 255};
const SDL_Color BLUE = {.r = 0, .g = 0, .b = 255, .a = 255};

const int TANK_WIDTH = 100;
const int TANK_HEIGHT = 70;
const float TANK_SPEED = 300.0f;
const float TANK_ROTATION_SPEED = 150.0f;

const float tank1InitRot = 0.0f;
const float tank2InitRot = 180.0f;
const Vector tank1InitPos = {.x = 100,
                             .y = SCREEN_HEIGHT / 2.0f - TANK_HEIGHT / 2.0f};
const Vector tank2InitPos = {.x = SCREEN_WIDTH - TANK_WIDTH - 100,
                             .y = SCREEN_HEIGHT / 2.0f - TANK_HEIGHT / 2.0f};

const bool *keys;
Uint64 lastFrameTime = 0;
Uint64 currentTime = 0;
float deltaTime = 0.0f;

typedef struct TankControls {
  SDL_Scancode up;
  SDL_Scancode down;
  SDL_Scancode left;
  SDL_Scancode right;
} TankControls;

typedef struct Tank {
  SDL_FRect rect;
  Uint8 lives, playerID;
  float speed, rotation, rotationSpeed;
  SDL_FPoint origin;
  SDL_Color color;
  TankControls controls;
} Tank;

void UpdateTank(Tank *tank, float deltaTime) {

  float dx = cosf(degToRad(tank->rotation)) * tank->speed * deltaTime;
  float dy = sinf(degToRad(tank->rotation)) * tank->speed * deltaTime;

  if (keys[tank->controls.up]) {
    tank->rect.x += dx;
    tank->rect.y += dy;
  }
  if (keys[tank->controls.down]) {
    tank->rect.x -= dx;
    tank->rect.y -= dy;
  }
  if (keys[tank->controls.left]) {
    tank->rotation -= tank->rotationSpeed * deltaTime;
  }
  if (keys[tank->controls.right]) {
    tank->rotation += tank->rotationSpeed * deltaTime;
  }
}

void DrawTank(Tank *tank, SDL_Renderer *renderer, SDL_Texture *texture) {
  SDL_SetTextureColorMod(texture, tank->color.r, tank->color.g, tank->color.b);
  SDL_RenderTextureRotated(renderer, texture, NULL, &tank->rect, tank->rotation,
                           &tank->origin, SDL_FLIP_NONE);
}

int main(void) {
  Tank tank1 = {
      .playerID = 1,
      .lives = 3,
      .rect = {.x = tank1InitPos.x,
               .y = tank1InitPos.y,
               .w = TANK_WIDTH,
               .h = TANK_HEIGHT},
      .speed = TANK_SPEED,
      .rotation = tank1InitRot,
      .rotationSpeed = TANK_ROTATION_SPEED,
      .color = RED,
      .origin = {.x = TANK_WIDTH / 2.0f, .y = TANK_HEIGHT / 2.0f},
      .controls = {.up = SDL_SCANCODE_W,
                   .down = SDL_SCANCODE_S,
                   .left = SDL_SCANCODE_A,
                   .right = SDL_SCANCODE_D},
  };

  Tank tank2 = {
      .playerID = 2,
      .lives = 3,
      .rect = {.x = tank2InitPos.x,
               .y = tank2InitPos.y,
               .w = TANK_WIDTH,
               .h = TANK_HEIGHT},
      .speed = TANK_SPEED,
      .rotation = tank2InitRot,
      .rotationSpeed = TANK_ROTATION_SPEED,
      .origin = {.x = TANK_WIDTH / 2.0f, .y = TANK_HEIGHT / 2.0f},
      .color = BLUE,
      .controls = {.up = SDL_SCANCODE_UP,
                   .down = SDL_SCANCODE_DOWN,
                   .left = SDL_SCANCODE_LEFT,
                   .right = SDL_SCANCODE_RIGHT},
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
  lastFrameTime = SDL_GetTicks();

  // CPU allocates space for a surface in RAM, it's just a buffer for pixel data
  // Buffer size is 4 bytes because 1 pixel = 4 bytes (RGBA)
  SDL_Surface *surface = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA32);
  if (!surface) {
    printf("%s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // CPU fills the buffer with white color
  SDL_FillSurfaceRect(surface, NULL, 0xFFFFFFFF);

  // GPU pulls the buffer from RAM to VRAM
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    printf("%s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Free the surface from RAM, as it's only needed in VRAM
  SDL_DestroySurface(surface);

  SDL_Event event;
  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
    }

    // --- Input & Timing ---

    keys = SDL_GetKeyboardState(NULL);
    currentTime = SDL_GetTicks();
    deltaTime = (float)(currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    UpdateTank(&tank1, deltaTime);
    UpdateTank(&tank2, deltaTime);

    // --- Drawing ---

    // Set background color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Clear the screen with the background color
    SDL_RenderClear(renderer);
    // Draw Tank 1
    DrawTank(&tank1, renderer, texture);
    // Draw Tank 2
    DrawTank(&tank2, renderer, texture);
    // Update the screen
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}