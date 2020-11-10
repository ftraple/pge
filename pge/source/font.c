#include "pixel-game-engine.h"
#include "defines.h"

extern pge_Window *window;

pge_FontObj pge_font_load(const char *file_name, int size) {
    pge_FontObj font_obj = (pge_FontObj)malloc(sizeof(struct pge_Font_t));
    if (!font_obj) {
        printf("Fail to allocate font memory.\n");
        return NULL;
    }
    font_obj->sdl_font = TTF_OpenFont(file_name, size);
    if (font_obj->sdl_font == NULL) {
        free(font_obj);
        printf("Failed to load the font! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }
    return font_obj;
}

void pge_font_unload(pge_FontObj font_obj) {
    if (font_obj == NULL) return;
    if (font_obj->sdl_font != NULL) {
        TTF_CloseFont(font_obj->sdl_font);
    }
    free(font_obj);
}
