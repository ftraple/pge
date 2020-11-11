#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main() {
    // Create window
    int screen_width = 640;
    int screen_height = 480;
    int pixel_scale = 1;
    int fps = 60;
    if (!pge_window_create("PGE - Text Example", screen_width, screen_height, pixel_scale, fps, false)) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }
    // Load a font
    pge_FontObj font = pge_font_load("../../../examples/resources/font/OpenSans-Bold.ttf", 44);
    if (!font) {
        printf("%s\n", pge_get_error());
        return EXIT_FAILURE;
    }
    // Create a text
    pge_TextObj text = pge_text_create(font, "Hello World!", PGE_COLOR_YELLOW);
    int text_x = (screen_width - pge_text_get_width(text)) / 2;

    pge_TextObj text_crop = pge_text_create(font, "Hello World!", PGE_COLOR_PINK);
    int text_crop_x = (screen_width / 2) - 80;
    int text_crop_height = pge_text_get_height(text_crop);
    // Game loop
    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);
        // Draw Text
        pge_text_draw(text, text_x, 100);
        // Draws Cropped Text
        pge_text_draw_crop(text_crop, text_crop_x, 200, 160, text_crop_height, 50, 0);
        pge_draw_set_current_color(PGE_COLOR_BLUE);
        pge_draw_rect(text_crop_x, 200, 160, text_crop_height);
        // Update window
        pge_window_show();
    }
    // Destroy
    pge_text_destroy(text);
    pge_text_destroy(text_crop);
    pge_font_unload(font);
    pge_window_destroy();
    return EXIT_SUCCESS;
}