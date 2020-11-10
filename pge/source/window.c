#include "defines.h"

pge_Window *window = NULL;

int pge_get_major_version() {
    return PGE_MAJOR_VERSION;
};
int pge_get_minor_version() {
    return PGE_MINOR_VERSION;
};

bool pge_window_create(const char *title, int width, int height, int scale, int fps, bool fullscreen) {
    if (scale <= 0) scale = 1;
    // Create the window object
    window = (pge_Window *)malloc(sizeof(struct pge_Window_t));
    if (!window) {
        printf("Fail to allocate window memory.\n");
        return false;
    }
    window->width = width;
    window->height = height;
    window->scale = scale;
    window->fps = fps;
    window->is_fullscreen = fullscreen;
    window->is_running = false;
    window->audio_voulume = SDL_MIX_MAXVOLUME;
    window->audio_muted = false;

    // Intialize the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Fail to init the SDL: %s\n", SDL_GetError());
        return false;
    }

    // Intialize the TTF
    int result = TTF_Init();
    if (TTF_Init() != 0) {
        printf("Fail to init the TTF: %s\n", SDL_GetError());
        return false;
    }

    // Initialize the audio mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // Create the SDL window
    window->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window->sdl_window) {
        printf("SDL: Fail to create the window: %s\n", SDL_GetError());
        return false;
    }
    // Create the SDL renderer
    window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (!window->sdl_renderer) {
        printf("SDL: Fail to create the renderer: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetWindowMinimumSize(window->sdl_window, width * scale, height * scale);
    SDL_RenderSetLogicalSize(window->sdl_renderer, width, height);
    SDL_RenderSetScale(window->sdl_renderer, scale, scale);

    // Initialize controllers and keyboard
    for (int i = 0; i < 8; i++) {
        window->controller[i].is_valid = false;
    }
    window->controller_amount = SDL_NumJoysticks();
    for (int i = 0; i < window->controller_amount; i++) {
        if (SDL_IsGameController(i)) {
            window->controller[i].sdl_game_controller = SDL_GameControllerOpen(i);
            if (!window->controller[i].sdl_game_controller) {
                fprintf(stderr, "Could not open game controller %i: %s\n", i, SDL_GetError());
            } else {
                window->controller[i].is_valid = true;
            }
        }
    }
    window->keyboard.dpad_up = false;
    window->keyboard.dpad_down = false;
    window->keyboard.dpad_left = false;
    window->keyboard.dpad_right = false;
    window->keyboard.left_axis_x = 0;
    window->keyboard.left_axis_y = 0;
    window->keyboard.right_axis_x = 0;
    window->keyboard.right_axis_y = 0;
    for (int i = 0; i < 11; i++) {
        window->keyboard.button[i] = false;
    }

    // FPS
    if (window->fps == 0) {
        window->frame_step_ms = 0;
    } else {
        window->frame_step_ms = 1000 / window->fps;
    }
    window->frame_start = SDL_GetTicks();
    window->frame_rate = window->fps;
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
            if (sdl_event.type == SDL_KEYDOWN) {
                // Dpad
                if (sdl_event.key.keysym.sym == SDLK_UP) {
                    window->keyboard.dpad_up = true;
                } else if (sdl_event.key.keysym.sym == SDLK_DOWN) {
                    window->keyboard.dpad_down = true;
                }
                if (sdl_event.key.keysym.sym == SDLK_LEFT) {
                    window->keyboard.dpad_left = true;
                } else if (sdl_event.key.keysym.sym == SDLK_RIGHT) {
                    window->keyboard.dpad_right = true;
                }
                // Buttons
                if (sdl_event.key.keysym.sym == SDLK_z) window->keyboard.button[0] = true;   // A
                if (sdl_event.key.keysym.sym == SDLK_x) window->keyboard.button[1] = true;   // B
                if (sdl_event.key.keysym.sym == SDLK_c) window->keyboard.button[2] = true;   // X
                if (sdl_event.key.keysym.sym == SDLK_v) window->keyboard.button[3] = true;   // Y
                if (sdl_event.key.keysym.sym == SDLK_1) window->keyboard.button[4] = true;   // Back
                if (sdl_event.key.keysym.sym == SDLK_2) window->keyboard.button[5] = true;   // Guide
                if (sdl_event.key.keysym.sym == SDLK_3) window->keyboard.button[6] = true;   // Start
                if (sdl_event.key.keysym.sym == SDLK_a) window->keyboard.button[7] = true;   // Left Steack
                if (sdl_event.key.keysym.sym == SDLK_s) window->keyboard.button[8] = true;   // Right Steack
                if (sdl_event.key.keysym.sym == SDLK_d) window->keyboard.button[9] = true;   // Left Shoulder
                if (sdl_event.key.keysym.sym == SDLK_f) window->keyboard.button[10] = true;  // Right Shouder
            } else if (sdl_event.type == SDL_KEYUP) {
                if (sdl_event.key.keysym.sym == SDLK_UP) {
                    window->keyboard.dpad_up = false;
                } else if (sdl_event.key.keysym.sym == SDLK_DOWN) {
                    window->keyboard.dpad_down = false;
                }
                if (sdl_event.key.keysym.sym == SDLK_LEFT) {
                    window->keyboard.dpad_left = false;
                } else if (sdl_event.key.keysym.sym == SDLK_RIGHT) {
                    window->keyboard.dpad_right = false;
                }
                // Buttons
                if (sdl_event.key.keysym.sym == SDLK_z) window->keyboard.button[0] = false;   // A
                if (sdl_event.key.keysym.sym == SDLK_x) window->keyboard.button[1] = false;   // B
                if (sdl_event.key.keysym.sym == SDLK_c) window->keyboard.button[2] = false;   // X
                if (sdl_event.key.keysym.sym == SDLK_v) window->keyboard.button[3] = false;   // Y
                if (sdl_event.key.keysym.sym == SDLK_1) window->keyboard.button[4] = false;   // Back
                if (sdl_event.key.keysym.sym == SDLK_2) window->keyboard.button[5] = false;   // Guide
                if (sdl_event.key.keysym.sym == SDLK_3) window->keyboard.button[6] = false;   // Start
                if (sdl_event.key.keysym.sym == SDLK_a) window->keyboard.button[7] = false;   // Left Steack
                if (sdl_event.key.keysym.sym == SDLK_s) window->keyboard.button[8] = false;   // Right Steack
                if (sdl_event.key.keysym.sym == SDLK_d) window->keyboard.button[9] = false;   // Left Shoulder
                if (sdl_event.key.keysym.sym == SDLK_f) window->keyboard.button[10] = false;  // Right Shouder
            }
        }
    }
    return window->is_running;
}

void pge_window_clear(pge_Color color) {
    SDL_SetRenderDrawColor(window->sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(window->sdl_renderer);
}

void pge_window_show() {
    SDL_RenderPresent(window->sdl_renderer);
    // Frame rate
    Uint32 frame_end = SDL_GetTicks();
    // Calculate frame rate
    window->frame_rate_count++;
    if (frame_end > window->frame_rate_start + 1000) {
        window->frame_rate = window->frame_rate_count;
        window->frame_rate_count = 0;
        window->frame_rate_start = frame_end;
    }
    // Wait until next frame
    if (window->fps > 0) {
        int sleep = window->frame_step_ms - (frame_end - window->frame_start);
        if (sleep > 0) {
            SDL_Delay(sleep);
        }
        window->frame_start += window->frame_step_ms;
    }
}

int pge_window_get_with() {
    return window->width;
}

int pge_window_get_height() {
    return window->height;
}

int pge_window_get_scale() {
    return window->scale;
}

int pge_window_get_fps() {
    return window->fps;
}

bool pge_window_is_fullscreen() {
    return window->is_fullscreen;
}

int pge_window_get_frame_rate() {
    return window->frame_rate;
}
