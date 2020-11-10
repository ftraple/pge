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

typedef struct {
    bool dpad_up;
    bool dpad_down;
    bool dpad_left;
    bool dpad_right;
    int left_axis_x;
    int left_axis_y;
    int right_axis_x;
    int right_axis_y;
    bool button[10];
} ControllerKeyboard;

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
    float frame_step_ms;
    float frame_start;
    int frame_rate;
    int frame_rate_count;
    Uint32 frame_rate_start;
    // Controllers
    int controller_amount;
    ControllerKeyboard keyboard;
    Controller controller[8];


    // Audio
    int audio_voulume;
    bool audio_muted;
};

struct pge_Font_t {
    TTF_Font *sdl_font;
};

#endif  // PGE_WINDOW_H_