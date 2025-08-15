#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

enum KEY_PRESS_SURFACE_TOTAL {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool load_media();
void close();

// Load Image
SDL_Surface *load_surface(char *path);

//
// GLOBAL VARIABLE
//

// global window
SDL_Window *g_window = NULL;

// global screen surface
SDL_Surface *g_screen_surface = NULL;

// global surface that corresponse to a keypress
SDL_Surface *g_keypress_surface[KEY_PRESS_SURFACE_TOTAL];

// global current display surface
SDL_Surface *g_current_surface = NULL;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Failed to inititlize window %s\n", SDL_GetError());
    success = false;
  }

  g_window = SDL_CreateWindow("Key Press Event", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  if (!g_window) {
    printf("Failed to created window SDL_Error: %s\n", SDL_GetError());
    success = false;
  }

  g_screen_surface = SDL_GetWindowSurface(g_window);
  if (!g_screen_surface) {
    printf("Failed to get are surface of window SDL_Error: %s\n",
           SDL_GetError());
    success = false;
  }

  return success;
}

SDL_Surface *load_surface(char *path) {
  // Load image to specified path
  SDL_Surface *load_bmp = SDL_LoadBMP(path);
  if (!load_bmp) {
    printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
  }

  return load_bmp;
}

bool load_media() {
  bool success = true;

  g_keypress_surface[KEY_PRESS_SURFACE_DEFAULT] = load_surface("./press.bmp");
  if (!g_keypress_surface[KEY_PRESS_SURFACE_DEFAULT]) {
    printf("Failed to load default image\n");
    success = false;
  }

  g_keypress_surface[KEY_PRESS_SURFACE_DOWN] = load_surface("./down.bmp");
  if (!g_keypress_surface[KEY_PRESS_SURFACE_DOWN]) {
    printf("Failed to load down image\n");
    success = false;
  }

  g_keypress_surface[KEY_PRESS_SURFACE_UP] = load_surface("./up.bmp");
  if (!g_keypress_surface[KEY_PRESS_SURFACE_UP]) {
    printf("Failed to load up image\n");
    success = false;
  }

  g_keypress_surface[KEY_PRESS_SURFACE_LEFT] = load_surface("./left.bmp");
  if (!g_keypress_surface[KEY_PRESS_SURFACE_LEFT]) {
    printf("Failed to load left image\n");
    success = false;
  }

  g_keypress_surface[KEY_PRESS_SURFACE_RIGHT] = load_surface("./right.bmp");
  if (!g_keypress_surface[KEY_PRESS_SURFACE_RIGHT]) {
    printf("Failed to load right image\n");
    success = false;
  }

  return success;
}

void close() {
  SDL_FreeSurface(g_current_surface);
  g_current_surface = NULL;

  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(g_keypress_surface[i]);
    g_keypress_surface[i] = NULL;
  }

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  SDL_Quit();
}

int main(int argc, char *argv[]) {

  if (!init()) {
    printf("Failed to Initialize\n");
  }
  if (!load_media()) {
    printf("Failed to Load media\n");
  }

  bool quit = false;
  SDL_Event event;
  g_current_surface = g_keypress_surface[KEY_PRESS_SURFACE_DEFAULT];

  while (!quit) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {

        case SDLK_UP:
          g_current_surface = g_keypress_surface[KEY_PRESS_SURFACE_UP];
          break;

        case SDLK_DOWN:
          g_current_surface = g_keypress_surface[KEY_PRESS_SURFACE_DOWN];
          break;

        case SDLK_LEFT:
          g_current_surface = g_keypress_surface[KEY_PRESS_SURFACE_LEFT];
          break;

        case SDLK_RIGHT:
          g_current_surface = g_keypress_surface[KEY_PRESS_SURFACE_RIGHT];
          break;
        }
      }
    }
    SDL_BlitSurface(g_current_surface, NULL, g_screen_surface, NULL);
    SDL_UpdateWindowSurface(g_window);
  }

  close();

  return 0;
}
