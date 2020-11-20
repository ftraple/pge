#include "defines.h"
#include "pixel-game-engine.h"

extern pge_Window *window;

int pge_controller_amount() {
    return SDL_NumJoysticks();
}

bool pge_controller_is_active(int id) {
    for (int i = 0; i < PGE_CONTROLLER_MAX; i++) {
        if (window->controller[i].id == id) {
            return window->controller[i].is_active;
        }
    }
    return false;
}

const char *pge_controller_get_mapping(int id) {
    for (int i = 0; i < PGE_CONTROLLER_MAX; i++) {
        if (window->controller[i].id == id) {
            return SDL_GameControllerMapping(window->controller[i].sdl_game_controller);
        }
    }
    return NULL;
}

int pge_controller_add_mapping(const char *mapping) {
    return SDL_GameControllerAddMapping(mapping);
}

int pge_controller_get_axis(int id, pge_ControllerAxis controller_axis) {
    for (int i = 0; i < PGE_CONTROLLER_MAX; i++) {
        if (window->controller[i].id == id && window->controller[i].is_active) {
            return SDL_GameControllerGetAxis(window->controller[i].sdl_game_controller, controller_axis);
        }
    }
    return 0;
}

bool pge_controller_button(int id, pge_ControllerButton button) {
    for (int i = 0; i < PGE_CONTROLLER_MAX; i++) {
        if (window->controller[i].id == id && window->controller[i].is_active) {
            return SDL_GameControllerGetButton(window->controller[i].sdl_game_controller, button);
        }
    }
    return false;
}
