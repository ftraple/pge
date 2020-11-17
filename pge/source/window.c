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
    window->max_fps = max_fps;
    window->is_fullscreen = fullscreen;
    window->is_running = false;
    window->audio_voulume = SDL_MIX_MAXVOLUME;
    window->audio_muted = false;

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

    // Initialize controllers and keyboard
    for (int i = 0; i < 8; i++) {
        window->controller[i].is_valid = false;
    }
    window->controller_amount = SDL_NumJoysticks();
    for (int i = 0; i < window->controller_amount; i++) {
        if (SDL_IsGameController(i)) {
            window->controller[i].sdl_game_controller = SDL_GameControllerOpen(i);
            if (!window->controller[i].sdl_game_controller) {
                pge_set_error_message("Could not open game controller [%i]: %s", i, SDL_GetError());
            } else {
                window->controller[i].is_valid = true;
            }
        }
    }
    for (int i = 0; i < PGE_CONTROLLER_BUTTON_MAX; i++) {
        window->controller_button[i] = false;
    }

    // FPS
    if (window->max_fps == 0) {
        window->frame_step_ms = 0;
    } else {
        window->frame_step_ms = 1000.0f / window->max_fps;
    }
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
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            window->is_running = false;
            break;
        }
        if (window->controller_amount == 0) {
            // Buttons
            if (sdl_event.type == SDL_KEYDOWN) {
                if (sdl_event.key.keysym.sym == SDLK_x) window->controller_button[PGE_CONTROLLER_BUTTON_B] = true;
                if (sdl_event.key.keysym.sym == SDLK_c) window->controller_button[PGE_CONTROLLER_BUTTON_X] = true;
                if (sdl_event.key.keysym.sym == SDLK_v) window->controller_button[PGE_CONTROLLER_BUTTON_Y] = true;
                if (sdl_event.key.keysym.sym == SDLK_1) window->controller_button[PGE_CONTROLLER_BUTTON_BACK] = true;
                if (sdl_event.key.keysym.sym == SDLK_2) window->controller_button[PGE_CONTROLLER_BUTTON_GUIDE] = true;
                if (sdl_event.key.keysym.sym == SDLK_3) window->controller_button[PGE_CONTROLLER_BUTTON_START] = true;
                if (sdl_event.key.keysym.sym == SDLK_a) window->controller_button[PGE_CONTROLLER_BUTTON_LEFTSTICK] = true;
                if (sdl_event.key.keysym.sym == SDLK_s) window->controller_button[PGE_CONTROLLER_BUTTON_RIGHTSTICK] = true;
                if (sdl_event.key.keysym.sym == SDLK_d) window->controller_button[PGE_CONTROLLER_BUTTON_LEFTSHOULDER] = true;
                if (sdl_event.key.keysym.sym == SDLK_f) window->controller_button[PGE_CONTROLLER_BUTTON_RIGHTSHOULDER] = true;
                if (sdl_event.key.keysym.sym == SDLK_UP) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_UP] = true;
                if (sdl_event.key.keysym.sym == SDLK_DOWN) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_DOWN] = true;
                if (sdl_event.key.keysym.sym == SDLK_LEFT) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_LEFT] = true;
                if (sdl_event.key.keysym.sym == SDLK_RIGHT) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_RIGHT] = true;
            } else if (sdl_event.type == SDL_KEYUP) {
                // Buttons
                if (sdl_event.key.keysym.sym == SDLK_x) window->controller_button[PGE_CONTROLLER_BUTTON_B] = false;
                if (sdl_event.key.keysym.sym == SDLK_c) window->controller_button[PGE_CONTROLLER_BUTTON_X] = false;
                if (sdl_event.key.keysym.sym == SDLK_v) window->controller_button[PGE_CONTROLLER_BUTTON_Y] = false;
                if (sdl_event.key.keysym.sym == SDLK_1) window->controller_button[PGE_CONTROLLER_BUTTON_BACK] = false;
                if (sdl_event.key.keysym.sym == SDLK_2) window->controller_button[PGE_CONTROLLER_BUTTON_GUIDE] = false;
                if (sdl_event.key.keysym.sym == SDLK_3) window->controller_button[PGE_CONTROLLER_BUTTON_START] = false;
                if (sdl_event.key.keysym.sym == SDLK_a) window->controller_button[PGE_CONTROLLER_BUTTON_LEFTSTICK] = false;
                if (sdl_event.key.keysym.sym == SDLK_s) window->controller_button[PGE_CONTROLLER_BUTTON_RIGHTSTICK] = false;
                if (sdl_event.key.keysym.sym == SDLK_d) window->controller_button[PGE_CONTROLLER_BUTTON_LEFTSHOULDER] = false;
                if (sdl_event.key.keysym.sym == SDLK_f) window->controller_button[PGE_CONTROLLER_BUTTON_RIGHTSHOULDER] = false;
                if (sdl_event.key.keysym.sym == SDLK_UP) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_UP] = false;
                if (sdl_event.key.keysym.sym == SDLK_DOWN) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_DOWN] = false;
                if (sdl_event.key.keysym.sym == SDLK_LEFT) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_LEFT] = false;
                if (sdl_event.key.keysym.sym == SDLK_RIGHT) window->controller_button[PGE_CONTROLLER_BUTTON_DPAD_RIGHT] = false;
            }
        }
    }
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
    // Wait until next frame
    if (window->max_fps > 0) {
        int sleep = window->frame_step_ms - (frame_end - window->frame_start);
        if (sleep > 0) {
            SDL_Delay(sleep);
        }
        window->frame_start += window->frame_step_ms;
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

int pge_window_get_fps() {
    return window->max_fps;
}

bool pge_window_is_fullscreen() {
    return window->is_fullscreen;
}

int pge_window_get_frame_rate() {
    return window->frame_rate;
}
