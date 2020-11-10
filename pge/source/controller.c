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

bool pge_controller_dpad_up(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller,
                                       SDL_CONTROLLER_BUTTON_DPAD_UP);
}

bool pge_controller_dpad_down(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller,
                                       SDL_CONTROLLER_BUTTON_DPAD_DOWN);
}

bool pge_controller_dpad_left(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller,
                                       SDL_CONTROLLER_BUTTON_DPAD_LEFT);
}
bool pge_controller_dpad_right(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller,
                                       SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
}

int pge_controller_left_axis_x(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetAxis(window->controller[controller_number].sdl_game_controller,
                                     SDL_CONTROLLER_AXIS_LEFTX);
}

int pge_controller_left_axis_y(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetAxis(window->controller[controller_number].sdl_game_controller,
                                     SDL_CONTROLLER_AXIS_LEFTY);
}

int pge_controller_right_axis_x(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetAxis(window->controller[controller_number].sdl_game_controller,
                                     SDL_CONTROLLER_AXIS_RIGHTX);
}

int pge_controller_right_axis_y(unsigned int controller_number) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetAxis(window->controller[controller_number].sdl_game_controller,
                                     SDL_CONTROLLER_AXIS_RIGHTY);
}

bool pge_controller_button(unsigned int controller_number, pge_ControllerButton button) {
    if (controller_number >= 8) return false;
    if (!window->controller[controller_number].is_valid) return false;
    return SDL_GameControllerGetButton(window->controller[controller_number].sdl_game_controller, button);
}
