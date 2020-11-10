#include "pixel-game-engine.h"
#include "defines.h"

extern pge_Window* window;

struct pge_Text_t {
    pge_FontObj font_obj;
    pge_Color color;
    char* text;
    int size;
    SDL_Texture* sdl_texture;
    int width;
    int height;
};

static void render_text(pge_TextObj text_obj) {
    SDL_Color text_color = {text_obj->color.r, text_obj->color.g, text_obj->color.b, text_obj->color.a};
    SDL_Surface* surface = TTF_RenderText_Solid(text_obj->font_obj->sdl_font, text_obj->text, text_color);
    if (surface == NULL) {
        printf("Fail to render the text.\n");
        return;
    }
    SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (sdl_texture == NULL) {
        printf("Fail to create the texture from the surface.\n");
        return;
    }
    if (text_obj->sdl_texture != NULL) {
        SDL_DestroyTexture(text_obj->sdl_texture);
    }
    SDL_QueryTexture(sdl_texture, NULL, NULL, &(text_obj->width), &(text_obj->height));
    text_obj->sdl_texture = sdl_texture;
}

pge_TextObj pge_text_create(pge_FontObj font_obj, const char* text, pge_Color color) {
    pge_TextObj text_obj = (pge_TextObj)malloc(sizeof(struct pge_Text_t));
    if (!text_obj) {
        printf("Fail to allocate text memory.\n");
        return NULL;
    }
    text_obj->font_obj = font_obj;
    text_obj->color = color;
    text_obj->size = strlen(text);
    text_obj->text = strdup(text);
    text_obj->sdl_texture = NULL;
    text_obj->width = 0;
    text_obj->height = 0;
    render_text(text_obj);
    return text_obj;
}

void pge_text_set(pge_TextObj text_obj, const char* text) {
    if (text_obj == NULL) return;
    render_text(text_obj);
    free(text_obj->text);
    text_obj->size = strlen(text);
    text_obj->text = strdup(text);
}

void pge_text_set_color(pge_TextObj text_obj, pge_Color color) {
    if (text_obj == NULL) return;
    text_obj->color = color;
}

void pge_text_draw(pge_TextObj text_obj, int x, int y) {
    if (text_obj == NULL) return;
    if (text_obj->sdl_texture != NULL) {
        SDL_Rect dst_rect = {x, y, text_obj->width, text_obj->height};
        SDL_RenderCopy(window->sdl_renderer, text_obj->sdl_texture, NULL, &dst_rect);
    }
}

void pge_text_draw_crop(pge_TextObj text_obj, int x, int y, int width, int height, int start_x, int start_y);
