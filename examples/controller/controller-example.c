#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

void print_controller_axis(pge_ControllerAxisEvent* axis_event) {
    printf("Controller [%d]", axis_event->id);
    switch (axis_event->axis) {
        case PGE_CONTROLLER_AXIS_LEFT_X:
            printf(" Axis Left X [%d] ", axis_event->value);
            break;
        case PGE_CONTROLLER_AXIS_LEFT_Y:
            printf(" Axis Left Y [%d] ", axis_event->value);
            break;
        case PGE_CONTROLLER_AXIS_RIGHT_X:
            printf(" Axis Right X [%d] ", axis_event->value);
            break;
        case PGE_CONTROLLER_AXIS_RIGHT_Y:
            printf(" Axis Right Y [%d] ", axis_event->value);
            break;
        case PGE_CONTROLLER_AXIS_TRIGGER_LEFT:
            printf(" Axis Trigger Left [%d] ", axis_event->value);
            break;
        case PGE_CONTROLLER_AXIS_TRIGGER_RIGHT:
            printf(" Axis Trigger Right [%d] ", axis_event->value);
            break;
    }
    printf("%s\n", axis_event->is_pressed ? "pressed" : "released");
}

void print_controller_buttons(pge_ControllerButtonEvent* button_event) {
    printf("[%d]", button_event->id);
    switch (button_event->button) {
        case PGE_CONTROLLER_BUTTON_A:
            printf(" Button A ");
            break;
        case PGE_CONTROLLER_BUTTON_B:
            printf(" Button B ");
            break;
        case PGE_CONTROLLER_BUTTON_X:
            printf(" Button X ");
            break;
        case PGE_CONTROLLER_BUTTON_Y:
            printf(" Button Y ");
            break;
        case PGE_CONTROLLER_BUTTON_BACK:
            printf(" Button Back ");
            break;
        case PGE_CONTROLLER_BUTTON_GUIDE:
            printf(" Button Guide ");
            break;
        case PGE_CONTROLLER_BUTTON_START:
            printf(" Button Start ");
            break;
        case PGE_CONTROLLER_BUTTON_LEFT_STICK:
            printf(" Button Left Stick ");
            break;
        case PGE_CONTROLLER_BUTTON_RIGHT_STICK:
            printf(" Button Right Stick ");
            break;
        case PGE_CONTROLLER_BUTTON_LEFT_SHOULDER:
            printf(" Button Left Shoulder ");
            break;
        case PGE_CONTROLLER_BUTTON_RIGHT_SHOULDER:
            printf(" Button Right Shoulder ");
            break;
        case PGE_CONTROLLER_BUTTON_DPAD_UP:
            printf(" Button Dpad Up ");
            break;
        case PGE_CONTROLLER_BUTTON_DPAD_DOWN:
            printf(" Button Dpad Down ");
            break;
        case PGE_CONTROLLER_BUTTON_DPAD_LEFT:
            printf(" Button Dpad Left ");
            break;
        case PGE_CONTROLLER_BUTTON_DPAD_RIGHT:
            printf(" Button Dpad Right ");
            break;
    }
    printf("%s\n", button_event->is_pressed ? "pressed" : "released");
}

int main(int argc, char** argv) {
    // Create
    int screen_width = 160;
    int screen_height = 120;
    if (!pge_window_create("PGE - Controller Example", screen_width, screen_height, 4, 60, false)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop
    int radius = 3;
    int x = (screen_width / 2) - radius;
    int y = (screen_height / 2) - radius;
    int controller_id = 0;
    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);
        pge_Event event;
        while (pge_event_pool(&event)) {
            switch (event.type) {
                case PGE_EVENT_CONTROLLER_DEVICE_ADDED:
                    printf("Controller [%d] Added\n", event.controller_device.id);
                    controller_id = event.controller_device.id;
                    break;
                case PGE_EVENT_CONTROLLER_DEVICE_REMOVED:
                    printf("Controller [%d] Removed\n", event.controller_device.id);
                    break;
                case PGE_EVENT_CONTROLLER_AXIS_MOTION:
                    print_controller_axis(&event.controller_axis);
                    break;
                case PGE_EVENT_CONTROLLER_BUTTON:
                    print_controller_buttons(&event.controller_button);
                    break;
            }
        }

        // Left Axis
        if (pge_controller_is_active(controller_id)) {
            if (pge_controller_get_axis(controller_id, PGE_CONTROLLER_AXIS_LEFT_X) < 0) {
                x--;
            } else if (pge_controller_get_axis(controller_id, PGE_CONTROLLER_AXIS_LEFT_X) > 0) {
                x++;
            }
            if (pge_controller_get_axis(controller_id, PGE_CONTROLLER_AXIS_LEFT_Y) < 0) {
                y--;
            } else if (pge_controller_get_axis(controller_id, PGE_CONTROLLER_AXIS_LEFT_Y) > 0) {
                y++;
            }
        }

        pge_draw_set_current_color(PGE_COLOR_PINK);
        pge_draw_circle(x, y, radius);

        pge_window_draw();
    }
    // Destroy
    pge_window_destroy();
    return EXIT_SUCCESS;
}
