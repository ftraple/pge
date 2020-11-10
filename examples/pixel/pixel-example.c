#include <stdio.h>
#include <stdlib.h>
#include <pge/pixel-game-engine.h>

int main() {
    // Create window
    int width = 160;
    int height = 120;
    int pixel_scale = 4;
    int fps = 0;
    if (!pge_window_create("Pixel Game Engine - Primitives", width, height, pixel_scale, fps, false)) {
        return EXIT_FAILURE;
    }
    // Game loop - randomly draw pixels
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        // Set random color
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_current_color(color);
        // Draw pixel
        int x1 = rand() % width;
        int y1 = rand() % height;
        pge_draw_point(x1, y1);
        pge_window_show();
    }
    // Destroy window
    pge_window_destroy();
    return EXIT_SUCCESS;
}