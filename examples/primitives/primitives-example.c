#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pixel-game-engine.h"

int main(int argc, char **argv) {
    // Create
    int width = 160;
    int height = 120;
    if (!pge_window_create("Pixel Game Engine - Primitives", width, height, 4, 60, false)) {
        return EXIT_FAILURE;
    }
    // Game loop
    pge_window_clear(PGE_COLOR_BLACK);
    while (pge_window_is_running()) {
        pge_Color color = {rand() % 255, rand() % 255, rand() % 255, 255};
        pge_draw_current_color(color);

        int x1 = rand() % width;
        int y1 = rand() % height;
        int x2 = rand() % width;
        int y2 = rand() % height;
        int radius = rand() % width / 4;

        int type = rand() % 6;
        switch (type) {
            case 0:
                pge_draw_point(x1, y1);
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
            default:
                break;
        }

        pge_window_show();
    }
    // Destroy
    pge_window_destroy();
    return EXIT_SUCCESS;
}