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
    int pixel_scale;
    int max_fps;
    bool is_fullscreen;
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    bool is_running;
    float frame_step_ms;
    float frame_start;
    int frame_rate;
    int frame_rate_count;
    Uint32 frame_rate_start;
    // Controllers
    int controller_amount;
    bool controller_button[PGE_CONTROLLER_BUTTON_MAX];
    Controller controller[PGE_CONTROLLER_MAX];
    // Audio
    int audio_voulume;
    bool audio_muted;
};

struct pge_Font_t {
    TTF_Font *sdl_font;
};

void pge_set_error_message(const char *format, ...);

#endif  // PGE_WINDOW_H_