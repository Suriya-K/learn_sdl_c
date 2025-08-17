#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Texture *load_texture(char *path);
bool load_media();
bool init();
void close();
void debug_log(char *msg, const char *err);

SDL_Window *windows = NULL;
SDL_Renderer *win_render = NULL;
SDL_Texture *win_texture = NULL;

bool init() {
  bool success = true;

  windows =
      SDL_CreateWindow("Texture loading and rendering", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
  if (!windows) {
    debug_log("Can't Create Windows", SDL_GetError());
    success = false;
  }

  win_render = SDL_CreateRenderer(windows, -1, SDL_RENDERER_ACCELERATED);
  if (!win_render) {
    debug_log("Failed to create Renderer", SDL_GetError());
    success = false;
  }

  SDL_SetRenderDrawColor(win_render, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG) {
    debug_log("SDL_Image could not init", IMG_GetError());
  }

  return success;
}

SDL_Texture *load_texture(char *path) {
  SDL_Texture *new_texture = NULL;

  SDL_Surface *loaded_surface = IMG_Load(path);
  if (!loaded_surface) {
    debug_log("Unable to load image", IMG_GetError());
  }

  new_texture = SDL_CreateTextureFromSurface(win_render, loaded_surface);
  if (!new_texture) {
    debug_log("Unable to Create texture", SDL_GetError());
  }

  SDL_FreeSurface(loaded_surface);

  return new_texture;
}

bool load_media() {
  bool success = true;

  win_texture = load_texture("./boo.jpg");
  if (!win_texture) {
    printf("Failed to load texture image \n");
    success = false;
  }

  return success;
}

void close() {
  SDL_DestroyTexture(win_texture);
  win_texture = NULL;

  SDL_DestroyRenderer(win_render);
  SDL_DestroyWindow(windows);
  win_render = NULL;
  windows = NULL;

  IMG_Quit();
  SDL_Quit();
}

void debug_log(char *msg, const char *err) {
  printf("DEBUG: %s \n MESSAGE: %s \n", msg, err);
}

int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to init");
  }

  if (!load_media()) {
    printf("Failed to load media");
  }

  bool quit = false;
  SDL_Event event;

  while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    SDL_RenderClear(win_render);
    SDL_RenderCopy(win_render, win_texture, NULL, NULL);
    SDL_RenderPresent(win_render);
  }
  return EXIT_SUCCESS;
}
