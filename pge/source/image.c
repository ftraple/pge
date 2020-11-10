#include "pixel-game-engine.h"
#include "defines.h"

extern pge_Window *window;

struct pge_Image_t {
    SDL_Texture *sdl_texture;
};

pge_ImageObj pge_image_load(const char *file_name) {
    SDL_Surface *surface = IMG_Load(file_name);
    if (!surface) {
        printf("Fail to load the texture: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);
    if (!sdl_texture) {
        printf("Fail to create the texture: %s\n", SDL_GetError());
        return NULL;
    }
    pge_ImageObj image_obj = (pge_ImageObj)malloc(sizeof(struct pge_Image_t));
    if (!image_obj) {
        SDL_FreeSurface(surface);
        printf("Fail to allocate texture memory.\n");
        return NULL;
    }
    image_obj->sdl_texture = sdl_texture;
    return image_obj;
}

void pge_image_unload(pge_ImageObj image_obj) {
    if (image_obj == NULL) return;
    SDL_DestroyTexture(image_obj->sdl_texture);
    free(image_obj);
}

void pge_draw_image(pge_ImageObj image_obj, int x, int y, int width, int height, int start_x, int start_y) {
    if (image_obj == NULL) return;
    SDL_Rect src_rect = {start_x, start_y, width, height};
    SDL_Rect dst_rect = {x, y, width, height};
    SDL_RenderCopy(window->sdl_renderer, image_obj->sdl_texture, &src_rect, &dst_rect);
}
