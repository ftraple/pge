#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main(int argc, char **argv) {
    // Create
    int screen_width = 160;
    int screen_height = 120;
    if (!pge_window_create("PGE- Primitives Example", screen_width, screen_height, 4, 60, false)) {
        printf("%s\n", pge_get_error_message());
        return EXIT_FAILURE;
    }
    // Game loop
    while (pge_window_is_running()) {
        pge_window_clear(PGE_COLOR_BLACK);
        // Repeat 100 times per frame
        for (int i = 0; i < 100; i++) {
            pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
            pge_draw_set_current_color(color);

            int x1 = rand() % screen_width;
            int y1 = rand() % screen_height;
            int x2 = rand() % screen_width;
            int y2 = rand() % screen_height;
            int radius = rand() % screen_width / 4;

            int type = rand() % 6;
            switch (type) {
                case 0:
                    pge_draw_pixel(x1, y1);
                    break;
                case 1:
                    pge_draw_line(x1, y1, x2, y2);
                    break;
                case 2:
                    pge_draw_rect(x1, y1, x2, y2);
                    break;
                case 3:
                    pge_draw_rect_fill(x1, y1, x2, y2);
                    break;
                case 4:
                    pge_draw_circle(x1, y1, radius);
                    break;
                case 5:
                    pge_draw_circle_fill(x1, y1, radius);
                    break;
            }
            // Show frame rate
            char text_frame_rate[100];
            snprintf(text_frame_rate, sizeof(text_frame_rate), "%d\n", pge_window_get_frame_rate());
            pge_draw_set_current_color(PGE_COLOR_WHITE);
            pge_draw_text(2, 2, 2, text_frame_rate);
        }

        pge_window_draw();
    }
    // Destroy
    pge_window_destroy();
    return EXIT_SUCCESS;
}