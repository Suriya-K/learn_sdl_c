#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

// Function Decleare
bool init();
bool load_media();
void close();

// Global Varaible Handle Windows and Surface
SDL_Window *g_win = NULL;
SDL_Surface *g_surface = NULL;
SDL_Surface *g_cat_surf = NULL;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL could not Initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  g_win = SDL_CreateWindow("Event Handle", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, 640, 480, 0);

  if (!g_win) {
    printf("Could not Create Window! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  g_surface = SDL_GetWindowSurface(g_win);

  return success;
}

bool load_media() {
  bool success = true;

  g_cat_surf = SDL_LoadBMP("./cat.bmp");

  if (!g_cat_surf) {
    printf("Unable to load image %s! SDL_Error: %s\n", "/cat.bmp",
           SDL_GetError());
    success = false;
  }

  return success;
}

void close() {
  SDL_FreeSurface(g_cat_surf);
  g_cat_surf = NULL;

  SDL_DestroyWindow(g_win);
  g_win = NULL;

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  if (!init()) {
    printf("Failed to Initialize");
  }

  if (!load_media()) {
    printf("Failed to Load media\n");
  }

  bool quit = false;
  SDL_Event event;

  while (!quit) {

    while (SDL_PollEvent(&event) != 0) {
      printf("Current Event type Happen: %d\n", event.type);

      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_BlitSurface(g_cat_surf, NULL, g_surface, NULL);
    SDL_UpdateWindowSurface(g_win);
  }

  close();

  return 0;
}
