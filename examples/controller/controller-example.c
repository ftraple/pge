#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main(int argc, char **argv) {
    // Create
    int screen_width = 160;
    int screen_height = 120;
    if (!pge_window_create("PGE - Controller Example", screen_width, screen_height, 4, 60, false)) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }
    // Game loop
    int radius = 3;
    int x = (screen_width / 2) - radius;
    int y = (screen_height / 2) - radius;

    printf("Amount of controllers: %d\n", pge_controller_amount());

    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);

        if (pge_controller_amount() == 0) {
            if (pge_controller_dpad_left(0)) {
                x--;
            } else if (pge_controller_dpad_right(0)) {
                x++;
            }
            if (pge_controller_dpad_up(0)) {
                y--;
            } else if (pge_controller_dpad_down(0)) {
                y++;
            }
        } else {
            if (pge_controller_left_axis_x(0) < 0) {
                x--;
            } else if (pge_controller_left_axis_x(0) > 0) {
                x++;
            }
            if (pge_controller_left_axis_y(0) < 0) {
                y--;
            } else if (pge_controller_left_axis_y(0) > 0) {
                y++;
            }
        }

        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_A)) {
            printf("PGE_CONTROLLER_BUTTON_A\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_B)) {
            printf("PGE_CONTROLLER_BUTTON_B\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_X)) {
            printf("PGE_CONTROLLER_BUTTON_X\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_Y)) {
            printf("PGE_CONTROLLER_BUTTON_Y\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_BACK)) {
            printf("PGE_CONTROLLER_BUTTON_BACK\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_GUIDE)) {
            printf("PGE_CONTROLLER_BUTTON_GUIDE\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_START)) {
            printf("PGE_CONTROLLER_BUTTON_START\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_LEFTSTICK)) {
            printf("PGE_CONTROLLER_BUTTON_LEFTSTICK\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_RIGHTSTICK)) {
            printf("PGE_CONTROLLER_BUTTON_RIGHTSTICK\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_LEFTSHOULDER)) {
            printf("PGE_CONTROLLER_BUTTON_LEFTSHOULDER\n");
        };
        if (pge_controller_button(0, PGE_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
            printf("PGE_CONTROLLER_BUTTON_RIGHTSHOULDER\n");
        };

        pge_draw_set_current_color(PGE_COLOR_PINK);
        pge_draw_circle(x, y, radius);

        pge_window_show();
    }
    // Destroy
    pge_window_destroy();
    return EXIT_SUCCESS;
}