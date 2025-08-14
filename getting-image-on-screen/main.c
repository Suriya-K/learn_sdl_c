
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

bool init();
bool load_media();
void close();

SDL_Window *window = NULL;
SDL_Surface *screen_surface = NULL;
SDL_Surface *helloworld = NULL;

bool init() {
  bool init_success = true;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    init_success = false;
  }

  window =
      SDL_CreateWindow("SDL Create Image", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Cannot Created Windows! %s\n", SDL_GetError());
    init_success = false;
  }

  screen_surface = SDL_GetWindowSurface(window);

  return init_success;
}

bool load_media() {
  bool load_success = true;

  helloworld = SDL_LoadBMP("./cat.bmp");

  if (!helloworld) {
    printf("Unable to load image %s! SDL Error: %s\n", "/cat.bmp",
           SDL_GetError());
    load_success = false;
  }

  return load_success;
}

void close() {
  SDL_FreeSurface(helloworld);
  helloworld = NULL;

  SDL_DestroyWindow(window); // don't worry about free surface of windows
                             // because this function will handle
  window = NULL;

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to Initialize");
  }

  if (!load_media()) {
    printf("Failed to Load media\n");
  }

  SDL_BlitSurface(helloworld, NULL, screen_surface, NULL);

  SDL_UpdateWindowSurface(window);

  SDL_Delay(5000);

  close();

  return 0;
}
