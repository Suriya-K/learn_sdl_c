#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool init();
bool load_image();
void close();
SDL_Surface *load_surface(char *path);

SDL_Window *windows = NULL;
SDL_Surface *wins_surface = NULL;
SDL_Surface *cat_img = NULL;
bool quit = false;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Initialize Failed! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  windows = SDL_CreateWindow("Optimize surface", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 640, 489, 0);

  if (!windows) {
    printf("Failed to Created Windows: SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  wins_surface = SDL_GetWindowSurface(windows);
  if (!wins_surface) {
    printf("Failed to Get Windows Surface! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

bool load_image() {
  bool success = true;

  cat_img = SDL_LoadBMP("./cat.bmp");

  if (!cat_img) {
    printf("Unable to load image %s! SDL_Error: %s\n", "./cat.bmp",
           SDL_GetError());
  }

  return success;
}

SDL_Surface *load_surface(char *path) {
  SDL_Surface *optimize_surface = NULL;

  optimize_surface = SDL_ConvertSurface(cat_img, wins_surface->format, 0);
  if (!optimize_surface) {
    printf("Unable to optimize image %s! SDL_Error %s\n", path, SDL_GetError());
  }

  SDL_FreeSurface(cat_img);

  return optimize_surface;
}

void close() {
  SDL_DestroyWindow(windows);
  windows = NULL;

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to Initialize");
  }

  if (!load_image()) {
    printf("Failed to Loadimage");
  }

  SDL_Event event;
  SDL_Surface *optimize_image = load_surface("./cat.bmp");

  while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.h = 480;
    stretchRect.w = 640;
    SDL_BlitScaled(optimize_image, NULL, wins_surface, &stretchRect);
    SDL_UpdateWindowSurface(windows);
  }

  close();

  return EXIT_SUCCESS;
}
