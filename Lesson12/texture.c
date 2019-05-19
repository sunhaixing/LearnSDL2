//
// Created by shx on 19-5-7.
//
#include <SDL2/SDL_image.h>
#include "texture.h"

// Initializes variables
LTexture *LTexture_init(SDL_Renderer *r) {
    LTexture *ret = malloc(sizeof(LTexture));
    ret -> width = 0;
    ret -> height = 0;
    ret -> texture = NULL;
    ret -> renderer = r;
    return ret;
}

// Deallocate memory
void LTexture_destroy(LTexture *this) {
    LTexture_free(this);
    free(this);
}

// Deallocate texture
void LTexture_free(LTexture *this) {
    if (this->texture != NULL) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
        this->height = 0;
        this->width = 0;
    }
}

// Load image at specified path
bool LTexture_load_from_file(LTexture *this, char *path) {
    LTexture_free(this);

    SDL_Texture *new_texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Unable to load image %s! SDL_image error %s\n", path,
                SDL_GetError());
        return false;
    }

    SDL_SetColorKey(surface, SDL_TRUE,
            SDL_MapRGB(surface->format, 0x00, 0xFF, 0xFF));
    new_texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (new_texture == NULL) {
        printf("Unable to create texture from %s! SDL_image error %s\n", path,
               SDL_GetError());
        return false;
    }

    this->width = surface->w;
    this->height = surface->h;

    SDL_FreeSurface(surface);

    this->texture = new_texture;
    return true;
}

// Render texture at given point
void LTexture_render(LTexture *this, int x, int y, SDL_Rect *clip) {
    SDL_Rect r = {x, y, this->width, this->height};
    if (clip != NULL) {
        r.w = clip->w;
        r.h = clip->h;
    }
    SDL_RenderCopy(this->renderer, this->texture, clip, &r);
}

// Get image dimensions
int LTexture_get_width(LTexture *this){
    return this->width;
}

int LTexture_get_height(LTexture *this) {
    return this->height;
}

void LTexture_set_color(LTexture *this, uint8_t red, uint8_t green, uint8_t blue) {
    SDL_SetTextureColorMod(this->texture, red, green, blue);
}