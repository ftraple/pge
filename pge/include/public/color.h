#ifndef PGE_COLOR_H_
#define PGE_COLOR_H_

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} pge_Color;

// Color palette
#define PGE_COLOR_LIGHT_GRAY  (pge_Color) {200, 200, 200, 255}
#define PGE_COLOR_GRAY        (pge_Color) {130, 130, 130, 255}
#define PGE_COLOR_DARK_GRAY   (pge_Color) {80, 80, 80, 255}
#define PGE_COLOR_YELLOW      (pge_Color) {253, 249, 0, 255}
#define PGE_COLOR_GOLD        (pge_Color) {255, 203, 0, 255}
#define PGE_COLOR_ORANGE      (pge_Color) {255, 161, 0, 255}
#define PGE_COLOR_PINK        (pge_Color) {255, 109, 194, 255}
#define PGE_COLOR_RED         (pge_Color) {230, 41, 55, 255}
#define PGE_COLOR_MAROON      (pge_Color) {190, 33, 55, 255}
#define PGE_COLOR_GREEN       (pge_Color) {0, 228, 48, 255}
#define PGE_COLOR_LIME        (pge_Color) {0, 158, 47, 255}
#define PGE_COLOR_DARK_GREEN  (pge_Color) {0, 117, 44, 255}
#define PGE_COLOR_SKY_BLUE    (pge_Color) {102, 191, 255, 255}
#define PGE_COLOR_BLUE        (pge_Color) {0, 121, 241, 255}
#define PGE_COLOR_DARK_BLUE   (pge_Color) {0, 82, 172, 255}
#define PGE_COLOR_PURPLE      (pge_Color) {200, 122, 255, 255}
#define PGE_COLOR_VIOLET      (pge_Color) {135, 60, 190, 255}
#define PGE_COLOR_DARK_PURPLE (pge_Color) {112, 31, 126, 255}
#define PGE_COLOR_BEIGE       (pge_Color) {211, 176, 131, 255}
#define PGE_COLOR_BROWN       (pge_Color) {127, 106, 79, 255}
#define PGE_COLOR_DARK_BROWN  (pge_Color) {76, 63, 47, 255}
#define PGE_COLOR_WHITE       (pge_Color) {255, 255, 255, 255}
#define PGE_COLOR_BLACK       (pge_Color) {0, 0, 0, 255}
#define PGE_COLOR_TRANPARENT  (pge_Color) {0, 0, 0, 0}
#define PGE_COLOR_MAGENTA     (pge_Color) {255, 0, 255, 255}
#define PGE_COLOR_RAY_WHITE   (pge_Color) {245, 245, 245, 255}

#endif  // PGE_COLOR_H_