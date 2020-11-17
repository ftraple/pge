#include "defines.h"
#include "pixel-game-engine.h"

extern pge_Window *window;

int pge_controller_amount() {
    return SDL_NumJoysticks();
}

bool pge_controller_is_valid(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    return window->controller[controller_number].is_valid;
}

const char *pge_controller_get_mapping(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    return SDL_GameControllerMapping(window->controller[controller_number].sdl_game_controller);
}

int pge_controller_add_mapping(const char *mapping) {
    return SDL_GameControllerAddMapping(mapping);
}

int pge_controller_get_axis(unsigned int controller_number, pge_ControllerAxis controller_axis) {
    if (controller_number >= 8) return false;
    return SDL_GameControllerGetAxis(window->controller[controller_number].sdl_game_controller, controller_axis);
}

bool pge_controller_button(unsigned int controller_number, pge_ControllerButton button) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return window->controller_button[button];
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller, button);
}
