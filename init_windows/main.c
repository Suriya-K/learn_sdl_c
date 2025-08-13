#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("Error Initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Initialize Windows", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, 0);

  if (!window) {
    printf("Error Creating Windows: %s\n", SDL_GetError());
  }

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);

  if (!renderer) {
    printf("Error Creating Renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Delay(3000);

  // clean up resource before it closing
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
