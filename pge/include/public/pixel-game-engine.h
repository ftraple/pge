#ifndef PGE_H_
#define PGE_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#define PGE_CONTROLLER_MAX 8

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
static const pge_Color PGE_COLOR_TRANSPARENT = {0, 0, 0, 0};
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
    PGE_CONTROLLER_BUTTON_LEFT_STICK,
    PGE_CONTROLLER_BUTTON_RIGHT_STICK,
    PGE_CONTROLLER_BUTTON_LEFT_SHOULDER,
    PGE_CONTROLLER_BUTTON_RIGHT_SHOULDER,
    PGE_CONTROLLER_BUTTON_PAD_UP,
    PGE_CONTROLLER_BUTTON_PAD_DOWN,
    PGE_CONTROLLER_BUTTON_PAD_LEFT,
    PGE_CONTROLLER_BUTTON_PAD_RIGHT,
    PGE_CONTROLLER_BUTTON_MAX
} pge_ControllerButton;

typedef enum {
    PGE_CONTROLLER_AXIS_LEFT_X,
    PGE_CONTROLLER_AXIS_LEFT_Y,
    PGE_CONTROLLER_AXIS_RIGHT_X,
    PGE_CONTROLLER_AXIS_RIGHT_Y,
    PGE_CONTROLLER_AXIS_TRIGGER_LEFT,
    PGE_CONTROLLER_AXIS_TRIGGER_RIGHT,
    PGE_CONTROLLER_AXIS_MAX
} pge_ControllerAxis;

typedef enum {
    PGE_EVENT_CONTROLLER_DEVICE_ADDED,
    PGE_EVENT_CONTROLLER_DEVICE_REMOVED,
    PGE_EVENT_CONTROLLER_AXIS_MOTION,
    PGE_EVENT_CONTROLLER_BUTTON,
} pge_EventType;

typedef enum {
    PGE_AUDIO_STATUS_STOPED,
    PGE_AUDIO_STATUS_PLAYING,
    PGE_AUDIO_STATUS_PAUSED,
} pge_AudioStatus;

typedef enum {
    PGE_ALIGN_LEFT_TOP,
    PGE_ALIGN_LEFT_CENTER,
    PGE_ALIGN_LEFT_BOTTOM,
    PGE_ALIGN_CENTER_TOP,
    PGE_ALIGN_CENTER_CENTER,
    PGE_ALIGN_CENTER_BOTTOM,
    PGE_ALIGN_RIGHT_TOP,
    PGE_ALIGN_RIGHT_CENTER,
    PGE_ALIGN_RIGHT_BOTTOM
} pge_Align;

typedef struct {
    int id;
    uint32_t timestamp;
} pge_ControllerDeviceEvent;

typedef struct {
    int id;
    uint32_t timestamp;
    pge_ControllerButton button;
    bool is_pressed;
} pge_ControllerButtonEvent;

typedef struct {
    int id;
    uint32_t timestamp;
    pge_ControllerAxis axis;
    int16_t value;
    bool is_pressed;
} pge_ControllerAxisEvent;

typedef struct {
    pge_EventType type;
    pge_ControllerDeviceEvent controller_device;
    pge_ControllerButtonEvent controller_button;
    pge_ControllerAxisEvent controller_axis;

} pge_Event;

// System
//--------------------------------------------------------------------------------
int pge_get_major_version();
int pge_get_minor_version();
const char *pge_get_error_message();

// Window
//--------------------------------------------------------------------------------
bool pge_window_create(const char *title, int width, int height, int pixel_scale, int max_fps, bool full_screen);
void pge_window_destroy();
bool pge_window_is_running();
void pge_window_clear(pge_Color color);
void pge_window_draw();
int pge_window_get_width();
int pge_window_get_height();
int pge_window_get_pixel_scale();
void pge_window_set_max_fps(int max_fps);
int pge_window_get_max_fps();
bool pge_window_is_full_screen();
int pge_window_get_frame_rate();

// Events
//--------------------------------------------------------------------------------
bool pge_event_wait(pge_Event *event);

// Controllers
//--------------------------------------------------------------------------------
int pge_controller_amount();
bool pge_controller_is_active(int id);
const char *pge_controller_get_mapping(int id);
int pge_controller_add_mapping(const char *mapping);
int pge_controller_get_axis(int id, pge_ControllerAxis controller_axis);
bool pge_controller_button(int id, pge_ControllerButton button);

// Primitives
//--------------------------------------------------------------------------------
void pge_draw_set_current_color(pge_Color color);
void pge_draw_pixel(int x, int y);
void pge_draw_line(int x1, int y1, int x2, int y2);
void pge_draw_rect(int x, int y, int width, int height);
void pge_draw_rect_fill(int x, int y, int width, int height);
void pge_draw_circle(int center_x, int center_y, int radius);
void pge_draw_circle_fill(int center_x, int center_y, int radius);
void pge_draw_text(int x, int y, int scale, pge_Align align, const char *format, ...);

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