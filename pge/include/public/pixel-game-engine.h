#ifndef PGE_H_
#define PGE_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} pge_Color;

// Color palette
static const pge_Color PGE_COLOR_LIGHT_GRAY = {200, 200, 200, 255};
static const pge_Color PGE_COLOR_GRAY = {130, 130, 130, 255};
static const pge_Color PGE_COLOR_DARK_GRAY = {80, 80, 80, 255};
static const pge_Color PGE_COLOR_YELLOW = {253, 249, 0, 255};
static const pge_Color PGE_COLOR_GOLD = {255, 203, 0, 255};
static const pge_Color PGE_COLOR_ORANGE = {255, 161, 0, 255};
static const pge_Color PGE_COLOR_PINK = {255, 109, 194, 255};
static const pge_Color PGE_COLOR_RED = {230, 41, 55, 255};
static const pge_Color PGE_COLOR_MAROON = {190, 33, 55, 255};
static const pge_Color PGE_COLOR_GREEN = {0, 228, 48, 255};
static const pge_Color PGE_COLOR_LIME = {0, 158, 47, 255};
static const pge_Color PGE_COLOR_DARK_GREEN = {0, 117, 44, 255};
static const pge_Color PGE_COLOR_SKY_BLUE = {102, 191, 255, 255};
static const pge_Color PGE_COLOR_BLUE = {0, 121, 241, 255};
static const pge_Color PGE_COLOR_DARK_BLUE = {0, 82, 172, 255};
static const pge_Color PGE_COLOR_PURPLE = {200, 122, 255, 255};
static const pge_Color PGE_COLOR_VIOLET = {135, 60, 190, 255};
static const pge_Color PGE_COLOR_DARK_PURPLE = {112, 31, 126, 255};
static const pge_Color PGE_COLOR_BEIGE = {211, 176, 131, 255};
static const pge_Color PGE_COLOR_BROWN = {127, 106, 79, 255};
static const pge_Color PGE_COLOR_DARK_BROWN = {76, 63, 47, 255};
static const pge_Color PGE_COLOR_WHITE = {255, 255, 255, 255};
static const pge_Color PGE_COLOR_BLACK = {0, 0, 0, 255};
static const pge_Color PGE_COLOR_TRANPARENT = {0, 0, 0, 0};
static const pge_Color PGE_COLOR_MAGENTA = {255, 0, 255, 255};
static const pge_Color PGE_COLOR_RAY_WHITE = {245, 245, 245, 255};

typedef struct pge_Sound_t *pge_SoundObj;
typedef struct pge_Music_t *pge_MusicObj;
typedef struct pge_Font_t *pge_FontObj;
typedef struct pge_Text_t *pge_TextObj;
typedef struct pge_Image_t *pge_ImageObj;

typedef enum {
    PGE_CONTROLLER_BUTTON_A,
    PGE_CONTROLLER_BUTTON_B,
    PGE_CONTROLLER_BUTTON_X,
    PGE_CONTROLLER_BUTTON_Y,
    PGE_CONTROLLER_BUTTON_BACK,
    PGE_CONTROLLER_BUTTON_GUIDE,
    PGE_CONTROLLER_BUTTON_START,
    PGE_CONTROLLER_BUTTON_LEFTSTICK,
    PGE_CONTROLLER_BUTTON_RIGHTSTICK,
    PGE_CONTROLLER_BUTTON_LEFTSHOULDER,
    PGE_CONTROLLER_BUTTON_RIGHTSHOULDER
} pge_ControllerButton;

typedef enum {
    PGE_AUDIO_STATUS_STOPED,
    PGE_AUDIO_STATUS_PLAYING,
    PGE_AUDIO_STATUS_PAUSED,
} pge_AudioStatus;

// System
//--------------------------------------------------------------------------------
int pge_get_major_version();
int pge_get_minor_version();
const char *pge_get_error_message();

// Window
//--------------------------------------------------------------------------------
bool pge_window_create(const char *title, int width, int height, int pixel_scale, int max_fps, bool fullscreen);
void pge_window_destroy();
bool pge_window_is_running();
void pge_window_clear(pge_Color color);
void pge_window_draw();
int pge_window_get_width();
int pge_window_get_height();
int pge_window_get_pixel_scale();
int pge_window_get_max_fps();
bool pge_window_is_fullscreen();
int pge_window_get_frame_rate();

// Controllers
//--------------------------------------------------------------------------------
int pge_controller_amount();
bool pge_controller_is_valid(unsigned int controller_number);
const char *pge_controller_get_mapping(unsigned int controller_number);
int pge_controller_add_mapping(const char *mapping);
// Dpad
bool pge_controller_dpad_up(unsigned int controller_number);
bool pge_controller_dpad_down(unsigned int controller_number);
bool pge_controller_dpad_left(unsigned int controller_number);
bool pge_controller_dpad_right(unsigned int controller_number);
// Left Axis
int pge_controller_left_axis_x(unsigned int controller_number);
int pge_controller_left_axis_y(unsigned int controller_number);
// Right Axis
int pge_controller_right_axis_x(unsigned int controller_number);
int pge_controller_right_axis_y(unsigned int controller_number);
// Buttons
bool pge_controller_button(unsigned int controller_number, pge_ControllerButton button);

// Primitives
//--------------------------------------------------------------------------------
void pge_draw_set_current_color(pge_Color color);
void pge_draw_pixel(int x, int y);
void pge_draw_line(int x1, int y1, int x2, int y2);
void pge_draw_rect(int x, int y, int width, int height);
void pge_draw_rect_fill(int x, int y, int width, int height);
void pge_draw_circle(int center_x, int center_y, int radius);
void pge_draw_circle_fill(int center_x, int center_y, int radius);
void pge_draw_text(int x, int y, int scale, const char *text);

// Font
//--------------------------------------------------------------------------------
pge_FontObj pge_font_load(const char *file_name, int size);
void pge_font_unload(pge_FontObj font_obj);

// Text
//--------------------------------------------------------------------------------
pge_TextObj pge_text_create(pge_FontObj font_obj, const char *text, pge_Color color);
void pge_text_destroy(pge_TextObj text_obj);
void pge_text_set_text(pge_TextObj text_obj, const char *text);
void pge_text_set_color(pge_TextObj text_obj, pge_Color color);
int pge_text_get_width(pge_TextObj text_obj);
int pge_text_get_height(pge_TextObj text_obj);
void pge_text_draw(pge_TextObj text_obj, int x, int y);
void pge_text_draw_crop(pge_TextObj text_obj, int x, int y, int width, int height, int start_x, int start_y);

// Image
//--------------------------------------------------------------------------------
pge_ImageObj pge_image_load(const char *file_name);
void pge_image_unload(pge_ImageObj image_obj);
int pge_image_get_width(pge_ImageObj image_obj);
int pge_image_get_height(pge_ImageObj image_obj);
void pge_image_draw(pge_ImageObj image_obj, int x, int y);
void pge_image_draw_crop(pge_ImageObj image_obj, int x, int y, int width, int height, int start_x, int start_y);

// Sound
//--------------------------------------------------------------------------------
pge_SoundObj pge_sound_load(const char *file_name);
void pge_sound_unload(pge_SoundObj sound_obj);
void pge_sound_play(pge_SoundObj sound_obj, bool loop);
void pge_sound_stop(pge_SoundObj sound_obj);
void pge_sound_pause(pge_SoundObj sound_obj);
void pge_sound_resume(pge_SoundObj sound_obj);
pge_AudioStatus pge_sound_status(pge_SoundObj sound_obj);
void pge_sound_volume(pge_SoundObj sound_obj, int volume);

// Music
//--------------------------------------------------------------------------------
pge_MusicObj pge_music_load(const char *file_name);
void pge_music_unload(pge_MusicObj music_obj);
void pge_music_play(pge_MusicObj music_obj, bool loop);
void pge_music_stop();
void pge_music_pause();
void pge_music_resume();
pge_AudioStatus pge_music_status();
void pge_music_volume(int volume);

#endif  // PGE_H_