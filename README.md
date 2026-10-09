# Tank Game (SDL3)

A 2-player local tank combat game written in C using SDL3.

This project is a rebuild of the original [Tank-Game-RayLib](https://github.com/r1hix/Tank-Game-RayLib), created to explore low-level game programming in C with SDL3—handling windowing, rendering, input, timing, audio, and text directly by hand without relying on high-level game framework wrappers.

## Features

- **2-Player Local Combat**: Head-to-head tank battles on a shared screen.
- **Ballistics & Ricochet**: Bullets bounce off walls before detonating.
- **Health & Lives System**: Player destruction, round tracking, and life counts.
- **Scenes & Flow**: Intro, gameplay, and game over scenes.
- **Audio Effects**: Sound effects for shooting, bouncing, explosions, and scene transitions.

## Controls

| Action | Player 1 (Red Tank) | Player 2 (Blue Tank) |
| :--- | :--- | :--- |
| Move Up | `W` | `Up Arrow` |
| Move Down | `S` | `Down Arrow` |
| Move Left | `A` | `Left Arrow` |
| Move Right | `D` | `Right Arrow` |

## Prerequisites

- **C Compiler**: `clang` (recommended on macOS) or `gcc` (with C17 support)
- **Make**: Standard build tool
- **pkg-config**: For resolving compiler and linker flags
- **SDL3**: [libsdl-org/SDL](https://github.com/libsdl-org/SDL) (v3.1+)

### Installing Prerequisites (macOS)

```bash
brew install sdl3 pkg-config
```

## Building and Running

Compile the game using the included `Makefile`:

```bash
# Build the executable
make

# Build and run directly
make run

# Clean build artifacts
make clean
```

Alternatively, compile directly with Clang:

```bash
clang -std=c17 -Wall -Wextra -g $(pkg-config --cflags --libs sdl3) main.c -o game
./game
```

In VS Code, you can also press `Cmd+Shift+B` to build using the configured build task.

## Status

Work in progress rebuild from the RayLib original.

- [x] SDL3 windowing and hardware-accelerated 2D renderer
- [x] Frame timing with delta time (`SDL_GetTicks`) & VSync
- [x] 2-player input handling (`SDL_GetKeyboardState`)
- [ ] Tank rotation and orientation
- [ ] Obstacle and boundary collision detection
- [ ] Bullet firing and ricochet bounce physics
- [ ] Sound playback via SDL3 audio streams
- [ ] Scene management (Menu, Playing, Game Over)
