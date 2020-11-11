#include "pixel-game-engine.h"
#include "defines.h"

extern pge_Window *window;

struct pge_Image_t {
    SDL_Texture *sdl_texture;
    int width;
    int height;
};

pge_ImageObj pge_image_load(const char *file_name) {
    SDL_Surface *surface = IMG_Load(file_name);
    if (!surface) {
        pge_set_error_message("Fail to load the texture: %s", SDL_GetError());
        return NULL;
    }
    SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (!sdl_texture) {
        pge_set_error_message("Fail to create the texture: %s", SDL_GetError());
        return NULL;
    }
    pge_ImageObj image_obj = (pge_ImageObj)malloc(sizeof(struct pge_Image_t));
    if (!image_obj) {
        SDL_FreeSurface(surface);
        pge_set_error_message("Fail to allocate texture memory.");
        return NULL;
    }
    SDL_QueryTexture(sdl_texture, NULL, NULL, &(image_obj->width), &(image_obj->height));
    image_obj->sdl_texture = sdl_texture;
    return image_obj;
}

void pge_image_unload(pge_ImageObj image_obj) {
    if (image_obj == NULL) return;
    if (image_obj->sdl_texture != NULL) {
        SDL_DestroyTexture(image_obj->sdl_texture);
    }
    free(image_obj);
}

void pge_draw_image(pge_ImageObj image_obj, int x, int y, int width, int height, int start_x, int start_y) {
    if (image_obj == NULL) return;
    if (image_obj->sdl_texture == NULL) return;
    SDL_Rect src_rect = {start_x, start_y, width, height};
    SDL_Rect dst_rect = {x, y, width, height};
    SDL_RenderCopy(window->sdl_renderer, image_obj->sdl_texture, &src_rect, &dst_rect);
}
