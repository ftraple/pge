#include "defines.h"
#include "pixel-game-engine.h"
#include "primitive-font.h"

extern pge_Window *window;

typedef struct {
    int char_width;
    int char_height;
    int char_space;
} PrimitiveFont;

static PrimitiveFont font = {
    char_width : 5,
    char_height : 11,
    char_space : 2,
};

void pge_draw_set_current_color(pge_Color color) {
    SDL_SetRenderDrawColor(window->sdl_renderer, color.r, color.g, color.b, color.a);
}

void pge_draw_pixel(int x, int y) {
    SDL_RenderDrawPoint(window->sdl_renderer, x, y);
}

void pge_draw_line(int x1, int y1, int x2, int y2) {
    // Horizontal line
    if (y2 == y1) {
        for (int x = x1; x <= x2; ++x) {
            pge_draw_pixel(x, y1);
        }
        return;
    }
    // Vertical line
    if (x2 == x1) {
        for (int y = y1; y <= y2; ++y) {
            pge_draw_pixel(x1, y);
        }
        return;
    }
    // Diagonal line
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    while (x1 != x2 || y1 != y2) {
        pge_draw_pixel(x1, y1);
        int e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void pge_draw_rect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(window->sdl_renderer, &rect);
}

void pge_draw_rect_fill(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(window->sdl_renderer, &rect);
}

static void draw_circle_points(pge_Window *window, int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(window->sdl_renderer, xc + x, yc + y);
    SDL_RenderDrawPoint(window->sdl_renderer, xc - x, yc + y);
    SDL_RenderDrawPoint(window->sdl_renderer, xc + x, yc - y);
    SDL_RenderDrawPoint(window->sdl_renderer, xc - x, yc - y);
    SDL_RenderDrawPoint(window->sdl_renderer, xc + y, yc + x);
    SDL_RenderDrawPoint(window->sdl_renderer, xc - y, yc + x);
    SDL_RenderDrawPoint(window->sdl_renderer, xc + y, yc - x);
    SDL_RenderDrawPoint(window->sdl_renderer, xc - y, yc - x);
}

// Bresenham’s circle drawing algorithm
void pge_draw_circle(int center_x, int center_y, int radius) {
    if (radius <= 0) {
        SDL_RenderDrawPoint(window->sdl_renderer, center_x, center_y);
        return;
    }
    int x = 0;
    int y = radius;
    int distance = 3 - 2 * radius;
    draw_circle_points(window, center_x, center_y, x, y);
    while (y >= x) {
        x++;
        if (distance > 0) {
            y--;
            distance = distance + 4 * (x - y) + 10;
        } else {
            distance = distance + 4 * x + 6;
        }
        draw_circle_points(window, center_x, center_y, x, y);
    }
}

static void draw_circle_lines(pge_Window *window, int xc, int yc, int x, int y) {
    SDL_RenderDrawLine(window->sdl_renderer, xc - x, yc - y, xc + x, yc - y);
    SDL_RenderDrawLine(window->sdl_renderer, xc - y, yc - x, xc + y, yc - x);
    SDL_RenderDrawLine(window->sdl_renderer, xc - y, yc + x, xc + y, yc + x);
    SDL_RenderDrawLine(window->sdl_renderer, xc - x, yc + y, xc + x, yc + y);
}

void pge_draw_circle_fill(int center_x, int center_y, int radius) {
    int x = 0;
    int y = radius;
    int distance = 3 - 2 * radius;
    draw_circle_lines(window, center_x, center_y, x, y);
    while (y >= x) {
        x++;
        if (distance > 0) {
            y--;
            distance = distance + 4 * (x - y) + 10;
        } else {
            distance = distance + 4 * x + 6;
        }
        draw_circle_lines(window, center_x, center_y, x, y);
    }
}

static void draw_char(int x, int y, int scale, char c) {
    c = c - 32;  // Remove the 32 first character from ASC table
    SDL_Rect rect = {x, y, scale, scale};
    for (int row = 0; row < font.char_height; ++row) {
        for (int col = 0; col < font.char_width; ++col) {
            rect.x = x + (col * scale);
            rect.y = y + (row * scale);
            if (g_font[c][row][col] == 1) {
                SDL_RenderFillRect(window->sdl_renderer, &rect);
            }
        }
    }
}

void pge_draw_text(int x, int y, int scale, pge_Align align, const char *format, ...) {
    if (scale <= 0) scale = 1;
    // Extract the real text
    char text[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(text, sizeof(text), format, args);
    va_end(args);
    if (rc <= 0) return;
    // Calculate text width and height first
    int text_size = strlen(text);
    int start_x = x;
    int start_y = y;
    int text_width = 0;
    int text_height = font.char_height * scale;
    int cur_x = 0;
    for (int i = 0; i < text_size; i++) {
        if (text[i] == '\n') {
            if (cur_x > text_width) {
                text_width = cur_x;
            }
            cur_x = 0;
            text_height += font.char_height * scale;
        } else {
            cur_x += (font.char_width * scale) + font.char_space;
        }
    }

    // Calculate the alignment
    switch (align) {
        case PGE_ALIGN_LEFT_TOP:
            start_x = x;
            start_y = y;
            break;
        case PGE_ALIGN_LEFT_CENTER:
            start_x = x;
            start_y = y - text_height / 2;
            break;
        case PGE_ALIGN_LEFT_BOTTOM:
            start_x = x;
            start_y = y - text_height;
            break;
        case PGE_ALIGN_CENTER_TOP:
            start_x = x - text_width / 2;
            start_y = y;
            break;
        case PGE_ALIGN_CENTER_CENTER:
            start_x = x - text_width / 2;
            start_y = y - text_height / 2;
            break;
        case PGE_ALIGN_CENTER_BOTTOM:
            start_x = x - text_width / 2;
            start_y = y - text_height;
            break;
        case PGE_ALIGN_RIGHT_TOP:
            start_x = x - text_width;
            start_y = y;
            break;
        case PGE_ALIGN_RIGHT_CENTER:
            start_x = x - text_width;
            start_y = y - text_height / 2;
            break;
        case PGE_ALIGN_RIGHT_BOTTOM:
            start_x = x - text_width;
            start_y = y - text_height;
            break;
    }
    // Draw the text
    cur_x = start_x;
    int cur_y = start_y;
    for (int i = 0; i < text_size; i++) {
        if (text[i] == '\n') {
            cur_x = start_x;
            cur_y += font.char_height * scale;
        } else {
            draw_char(cur_x, cur_y, scale, text[i]);
            cur_x += (font.char_width * scale) + font.char_space;
        }
    }
}
