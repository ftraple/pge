#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    int width = 160;
    int height = 120;
    int pixel_scale = 4;
    int fps = 60;
    if (!pge_window_create("PGE - Pixel Example", width, height, pixel_scale, fps, false)) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }
    // Game loop - randomly draw pixels
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        // Set random color
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_set_current_color(color);
        // Draw pixel
        int x1 = rand() % width;
        int y1 = rand() % height;
        pge_draw_point(x1, y1);
        // Update window
        pge_window_show();
    }
    // Destroy window
    pge_window_destroy();
    return EXIT_SUCCESS;
}