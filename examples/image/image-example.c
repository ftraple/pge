#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    int screen_width = 640;
    int screen_height = 480;
    int pixel_scale = 1;
    int fps = 60;
    bool fullscreen = false;
    if (!pge_window_create("PGE - Text Example", screen_width, screen_height, pixel_scale, fps, fullscreen)) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }
    // Load a font
    pge_ImageObj image = pge_image_load("../../../examples/resources/image/test.png");
    if (!image) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }

    // Game loop
    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);
        // Draw Image
        pge_image_draw(image, 10, 10);
        pge_image_draw_crop(image, 450, 100, 160, 160, 120, 120);
        // Update window
        pge_window_show();
    }
    // Destroy
    pge_image_unload(image);
    pge_window_destroy();
    return EXIT_SUCCESS;
}