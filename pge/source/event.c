#include "defines.h"
#include "pixel-game-engine.h"

extern pge_Window *window;

bool pge_event_wait(pge_Event *event) {
    SDL_Event sdl_event;

    float frame_end = SDL_GetTicks();

    while (true) {
        if (window->max_fps > 0) {
            window->sleep = window->frame_step_ms - (frame_end - window->frame_start);
            if (window->sleep > 0) {
                if (!SDL_WaitEventTimeout(&sdl_event, window->sleep)) {
                    return false;
                }
            } else {
                window->frame_start += window->frame_step_ms;
            }
        } else {
            if (!SDL_PollEvent(&sdl_event)) {
                return false;
            }
        }
        switch (sdl_event.type) {
            case SDL_CONTROLLERDEVICEADDED: {
                printf("[INFO] sdl_event.type [%d]\n", sdl_event.type);
                int controller_index = sdl_event.cdevice.which;
                printf("[INFO] Controller [%d] found.\n", controller_index);
                if (controller_index < PGE_CONTROLLER_MAX &&
                    window->controller[controller_index].is_active == false &&
                    SDL_IsGameController(controller_index)) {
                    window->controller[controller_index].sdl_game_controller = SDL_GameControllerOpen(controller_index);
                    if (!window->controller[controller_index].sdl_game_controller) {
                        pge_set_error_message("Could not open the game controller [%i]: %s", controller_index, SDL_GetError());
                    } else {
                        window->controller[controller_index].is_active = true;
                        event->type = PGE_EVENT_CONTROLLER_DEVICE_ADDED;
                        SDL_Joystick *sdl_joystick = SDL_GameControllerGetJoystick(window->controller[controller_index].sdl_game_controller);
                        window->controller[controller_index].id = SDL_JoystickInstanceID(sdl_joystick);
                        event->controller_device.id = window->controller[controller_index].id;
                        return true;
                    }
                }
                return false;
            }
            case SDL_CONTROLLERDEVICEREMOVED: {
                int id = sdl_event.cdevice.which;
                for (int i = 0; i < PGE_CONTROLLER_MAX; i++) {
                    if (window->controller[i].id == id && window->controller[i].is_active == true) {
                        SDL_GameControllerClose(window->controller[i].sdl_game_controller);
                        window->controller[i].is_active = false;
                        event->type = PGE_EVENT_CONTROLLER_DEVICE_REMOVED;
                        event->controller_device.id = id;
                        return true;
                    }
                }
                return false;
            }
            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP: {
                event->type = PGE_EVENT_CONTROLLER_BUTTON;
                event->controller_button.id = sdl_event.cbutton.which;
                event->controller_button.timestamp = sdl_event.cbutton.timestamp;
                event->controller_button.button = sdl_event.cbutton.button;
                event->controller_button.is_pressed = (sdl_event.cbutton.state == 0) ? false : true;
                return true;
            }
            case SDL_CONTROLLERAXISMOTION: {
                event->type = PGE_EVENT_CONTROLLER_AXIS_MOTION;
                event->controller_axis.id = sdl_event.caxis.which;
                event->controller_axis.timestamp = sdl_event.caxis.timestamp;
                event->controller_axis.axis = sdl_event.caxis.axis;
                event->controller_axis.value = sdl_event.caxis.value;
                event->controller_axis.is_pressed = (sdl_event.caxis.value == 0) ? false : true;
                return true;
            }
            frame_end = SDL_GetTicks();
        }
    }
    return false;
}
