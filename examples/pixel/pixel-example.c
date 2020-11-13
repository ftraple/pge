#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    int screen_width = 160;
    int screeen_height = 120;
    int pixel_scale = 4;
    int max_fps = 60;
    bool fullscreen = false;
    if (!pge_window_create("PGE - Pixel Example",
                           screen_width, screeen_height,
                           pixel_scale, max_fps, fullscreen)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop - randomly draw pixels
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        // Set random color
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_set_current_color(color);
        // Draw pixel
        int x1 = rand() % screen_width;
        int y1 = rand() % screeen_height;
        pge_draw_pixel(x1, y1);
        // Update window
        pge_window_draw();
    }
    // Destroy window
    pge_window_destroy();
    return EXIT_SUCCESS;
}