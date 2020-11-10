#ifndef PGE_WINDOW_H_
#define PGE_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

typedef struct {
    bool is_valid;
    SDL_GameController *sdl_game_controller;
} Controller;

typedef struct pge_Window_t pge_Window;
struct pge_Window_t {
    // Window
    int width;
    int height;
    int scale;
    int fps;
    bool is_fullscreen;
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    bool is_running;
    Uint32 frame_step_ms;
    Uint32 frame_start;
    int frame_rate;
    int frame_rate_count;
    Uint32 frame_rate_start;
    // Controllers
    Controller controller[8];
    // Audio
    int audio_voulume;
    bool audio_muted;
};

struct pge_Font_t {
    TTF_Font *sdl_font;
};

#endif  // PGE_WINDOW_H_