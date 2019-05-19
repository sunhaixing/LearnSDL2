//
// Created by shx on 19-5-7.
//

#ifndef LEARNSDL2_TEXTURE_H
#define LEARNSDL2_TEXTURE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    // The window renderer
    SDL_Renderer *renderer;

    // The actual hardware texture
    SDL_Texture *texture;

    // Image dimensions
    int width;
    int height;
} LTexture;

// Initializes variables
LTexture *LTexture_init(SDL_Renderer *r);
// Deallocate memory
void LTexture_destroy(LTexture *this);

// Deallocate texture
void LTexture_free(LTexture *this);

// Load image at specified path
bool LTexture_load_from_file(LTexture *this, char *path);

// Render texture at given point
void LTexture_render(LTexture *this, int x, int y, SDL_Rect *clip);

// Set color modulation
void LTexture_set_color(LTexture *this, uint8_t red, uint8_t green, uint8_t blue);


// Get image dimensions
int LTexture_get_width(LTexture *this);
int LTexture_get_height(LTexture *this);

#endif //LEARNSDL2_TEXTURE_H
