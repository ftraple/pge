#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <stdbool.h>

#include "pixel-game-engine.h"

// System
//--------------------------------------------------------------------------------
static int get_major_version(lua_State *L) {
    int major_version = pge_get_major_version();
    lua_pushinteger(L, major_version);
    return 1;
}

static int get_minor_version(lua_State *L) {
    int minor_version = pge_get_minor_version();
    lua_pushinteger(L, minor_version);
    return 1;
}

static int get_error_message(lua_State *L) {
    const char *error_message = pge_get_error_message();
    lua_pushstring(L, error_message);
    return 1;
}

// Window
//--------------------------------------------------------------------------------
static int window_create(lua_State *L) {
    const char *title = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);
    int pixel_scale = luaL_checkinteger(L, 4);
    int max_fps = luaL_checkinteger(L, 5);
    int fullscreen = lua_toboolean(L, 6);
    bool result = pge_window_create(title, width, height, pixel_scale, max_fps, fullscreen);
    lua_pushboolean(L, result);
    return 1;
}

static int window_destroy(lua_State *L) {
    pge_window_destroy();
    return 0;
}

static int window_is_running(lua_State *L) {
    bool is_running = pge_window_is_running();
    lua_pushboolean(L, is_running);
    return 1;
}

static int window_clear(lua_State *L) {
    pge_Color color;
    color.r = luaL_checkinteger(L, 1);
    color.g = luaL_checkinteger(L, 2);
    color.b = luaL_checkinteger(L, 3);
    color.a = luaL_checkinteger(L, 4);
    pge_window_clear(color);
    return 0;
}

static int window_draw(lua_State *L) {
    pge_window_draw();
    return 0;
}

static int window_get_width(lua_State *L) {
    int width = pge_window_get_width();
    lua_pushinteger(L, width);
    return 1;
}

static int window_get_height(lua_State *L) {
    int height = pge_window_get_height();
    lua_pushinteger(L, height);
    return 1;
}

static int window_get_pixel_scale(lua_State *L) {
    int pixel_scale = pge_window_get_pixel_scale();
    lua_pushinteger(L, pixel_scale);
    return 1;
}

static int window_set_max_fps(lua_State *L) {
    int max_fps = luaL_checkinteger(L, 1);
    pge_window_set_max_fps(max_fps);
    return 0;
}

static int window_get_max_fps(lua_State *L) {
    int max_fps = pge_window_get_max_fps();
    lua_pushinteger(L, max_fps);
    return 1;
}

static int window_is_fullscreen(lua_State *L) {
    int fullscreen = pge_window_is_fullscreen();
    lua_pushboolean(L, fullscreen);
    return 1;
}

static int window_get_frame_rate(lua_State *L) {
    int frame_rate = pge_window_get_frame_rate();
    lua_pushinteger(L, frame_rate);
    return 1;
}

// Primitives
//--------------------------------------------------------------------------------
static int draw_set_current_color(lua_State *L) {
    pge_Color color;
    color.r = luaL_checkinteger(L, 1);
    color.g = luaL_checkinteger(L, 2);
    color.b = luaL_checkinteger(L, 3);
    color.a = luaL_checkinteger(L, 4);
    pge_draw_set_current_color(color);
    return 0;
}

static int draw_pixel(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    pge_draw_pixel(x, y);
    return 0;
}

static int draw_line(lua_State *L) {
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int x2 = luaL_checkinteger(L, 3);
    int y2 = luaL_checkinteger(L, 4);
    pge_draw_line(x1, y1, x2, y2);
    return 0;
}

static int draw_rect(lua_State *L) {
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    pge_draw_rect(x1, y1, width, height);
    return 0;
}

static int draw_rect_fill(lua_State *L) {
    int x1 = luaL_checkinteger(L, 1);
    int y1 = luaL_checkinteger(L, 2);
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    pge_draw_rect_fill(x1, y1, width, height);
    return 0;
}

static int draw_circle(lua_State *L) {
    int center_x = luaL_checkinteger(L, 1);
    int center_y = luaL_checkinteger(L, 2);
    int radius = luaL_checkinteger(L, 3);
    pge_draw_circle(center_x, center_y, radius);
    return 0;
}

static int draw_circle_fill(lua_State *L) {
    int center_x = luaL_checkinteger(L, 1);
    int center_y = luaL_checkinteger(L, 2);
    int radius = luaL_checkinteger(L, 3);
    pge_draw_circle_fill(center_x, center_y, radius);
    return 0;
}

static int draw_text(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int scale = luaL_checkinteger(L, 3);
    int align = luaL_checkinteger(L, 4);
    const char *format = luaL_checkstring(L, 5);
    pge_draw_text(x, y, scale, align, format);
    return 0;
}

// Library register
//--------------------------------------------------------------------------------
static const struct luaL_Reg pge_lua[] = {
    // System
    {"get_major_version", get_major_version},
    {"get_minor_version", get_minor_version},
    {"get_error_message", get_error_message},
    // Window
    {"window_create", window_create},
    {"window_destroy", window_destroy},
    {"window_is_running", window_is_running},
    {"window_clear", window_clear},
    {"window_draw", window_draw},
    {"window_get_width", window_get_width},
    {"window_get_height", window_get_height},
    {"window_get_pixel_scale", window_get_pixel_scale},
    {"window_set_max_fps", window_set_max_fps},
    {"window_get_max_fps", window_get_max_fps},
    {"window_is_fullscreen", window_is_fullscreen},
    {"window_get_frame_rate", window_get_frame_rate},
    // Primitives
    {"draw_set_current_color", draw_set_current_color},
    {"draw_pixel", draw_pixel},
    {"draw_line", draw_line},
    {"draw_rect", draw_rect},
    {"draw_rect_fill", draw_rect_fill},
    {"draw_circle", draw_circle},
    {"draw_circle_fill", draw_circle_fill},
    {"draw_text", draw_text},

    {NULL, NULL}};

int luaopen_libpge_lua(lua_State *L) {
    luaL_newlib(L, pge_lua);
    return 1;
}