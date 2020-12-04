#include "defines.h"

pge_Window *window = NULL;

bool pge_window_create(const char *title, int width, int height, int pixel_scale, int max_fps, bool fullscreen) {
    if (pixel_scale <= 0) pixel_scale = 1;
    pge_set_error_message("");
    // Create the window object
    window = (pge_Window *)malloc(sizeof(struct pge_Window_t));
    if (!window) {
        pge_set_error_message("Fail to allocate window memory.");
        return false;
    }
    window->width = width;
    window->height = height;
    window->pixel_scale = pixel_scale;
    window->is_fullscreen = fullscreen;
    window->is_running = false;
    window->audio_voulume = SDL_MIX_MAXVOLUME;
    window->audio_muted = false;
    pge_window_set_max_fps(max_fps);

    // Intialize the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        pge_set_error_message("Fail to init SDL: %s", SDL_GetError());
        return false;
    }

    // Intialize the TTF
    int result = TTF_Init();
    if (TTF_Init() != 0) {
        pge_set_error_message("Fail to init SDL_ttf: %s", TTF_GetError());
        return false;
    }

    // Initialize the audio mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // Create the SDL window
    window->sdl_window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width * pixel_scale, height * pixel_scale,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window->sdl_window) {
        pge_set_error_message("Fail to create the SDL window: %s", TTF_GetError());
        return false;
    }
    // Create the SDL renderer
    window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (!window->sdl_renderer) {
        pge_set_error_message("Fail to create the SDL renderer: %s", TTF_GetError());
        return false;
    }
    SDL_SetWindowMinimumSize(window->sdl_window, width * pixel_scale, height * pixel_scale);
    SDL_RenderSetLogicalSize(window->sdl_renderer, width, height);
    SDL_RenderSetScale(window->sdl_renderer, pixel_scale, pixel_scale);

    // Initialize controllers
    for (int i = 0; i < 8; i++) {
        window->controller[i].is_active = false;
    }

    // Frame rate
    window->frame_start = SDL_GetTicks();
    window->frame_rate = window->max_fps;
    window->frame_rate_count = 0;
    window->frame_rate_start = window->frame_start;
    window->is_running = true;
    return true;
}

void pge_window_destroy() {
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);
    free(window);
}

bool pge_window_is_running() {
    return window->is_running;
}

void pge_window_clear(pge_Color color) {
    SDL_SetRenderDrawColor(window->sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(window->sdl_renderer);
}

void pge_window_draw() {
    SDL_RenderPresent(window->sdl_renderer);
    // Frame rate
    float frame_end = SDL_GetTicks();
    // Calculate frame rate
    window->frame_rate_count++;
    if (frame_end > window->frame_rate_start + 1000.0f) {
        window->frame_rate = window->frame_rate_count;
        window->frame_rate_count = 0;
        window->frame_rate_start = frame_end;
    }
}

int pge_window_get_width() {
    return window->width;
}

int pge_window_get_height() {
    return window->height;
}

int pge_window_get_pixel_scale() {
    return window->pixel_scale;
}

void pge_window_set_max_fps(int max_fps) {
    window->max_fps = max_fps;
    if (window->max_fps <= 0) {
        window->frame_step_ms = 0;
    } else {
        window->frame_step_ms = 1000.0f / window->max_fps;
    }
}

int pge_window_get_max_fps() {
    return window->max_fps;
}

bool pge_window_is_fullscreen() {
    return window->is_fullscreen;
}

int pge_window_get_frame_rate() {
    return window->frame_rate;
}
