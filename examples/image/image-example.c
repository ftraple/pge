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
    bool full_screen = false;
    if (!pge_window_create("PGE - Image Example", screen_width, screen_height, pixel_scale, fps, full_screen)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Load a font
    pge_ImageObj image = pge_image_load("../../../examples/resources/image/test.png");
    if (!image) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop
    while (pge_window_is_running()) {
        // Capture events
        pge_Event event;
        while (pge_event_wait(&event)) {
        }
        pge_window_clear(PGE_COLOR_BLACK);
        // Draw Image
        pge_image_draw(image, 10, 10);
        pge_image_draw_crop(image, 450, 100, 160, 160, 120, 120);
        // Update window
        pge_window_draw();
    }
    // Destroy
    pge_image_unload(image);
    pge_window_destroy();
    return EXIT_SUCCESS;
}