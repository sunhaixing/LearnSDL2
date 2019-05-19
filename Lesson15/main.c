// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "texture.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and create window
static bool init();

// Load media
static bool load_media();

// Frees media and shut down SDL
static void close();

// The window we'll be rendering to
static SDL_Window *g_window = NULL;

// The window renderer
static SDL_Renderer *g_renderer = NULL;

// Scene texture
static LTexture *g_texture = NULL;

static LTexture *g_modulated_texture = NULL;

static SDL_Rect g_sprite_clips[4];

int main(int argc, char *argv[]) {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    double degree = 0.0;

    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    uint8_t r = 0xFF;
    uint8_t g = 0xFF;
    uint8_t b = 0xFF;

    // Apply the image stretched
    SDL_Rect stretch_rect;
    stretch_rect.x = 0;
    stretch_rect.y = 0;
    stretch_rect.w = SCREEN_WIDTH;
    stretch_rect.h = SCREEN_HEIGHT;


    if(!init()) {
        printf("Failed to initialize!\n");
    } else {
        if(!load_media()) {
            printf("Failed to load media!\n");
        } else {

            // While application is running
            while(!quit) {

                // Handle event on queue
                while(SDL_PollEvent(&e) != 0) {

                    // User request quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch(e.key.keysym.sym) {
                            case SDLK_a:
                                degree -= 60;
                                break;
                            case SDLK_d:
                                degree += 60;
                                break;
                            case SDLK_q:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                            case SDLK_w:
                                flipType = SDL_FLIP_NONE;
                                break;
                            case SDLK_e:
                                flipType = SDL_FLIP_VERTICAL;
                                break;
                        }
                    }
                }

                SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
                // Clear screen
                SDL_RenderClear(g_renderer);

                LTexture_set_color(g_texture, r, g, b);
                LTexture_render(g_texture, 0, 0, NULL, 0, NULL, SDL_FLIP_NONE);

                LTexture_set_alpha(g_modulated_texture, 128);
                LTexture_render(g_modulated_texture, 0, 0, NULL, degree, NULL, flipType);
                // Update screen
                SDL_RenderPresent(g_renderer);
            }
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}

// Starts up SDL and create window
static bool init() {
    // Initialization flag
    bool success = false;
    int img_flag = IMG_INIT_PNG;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return success;
    }

    // Create window
    g_window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL) {
        printf("Window could not be created! SDL error: %s\n", SDL_GetError());
        return success;
    }

    // Create renderer for window
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(g_renderer == NULL) {
        printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
        return success;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    if(!IMG_Init(img_flag) & img_flag) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
                SDL_GetError());
        return success;
    }

    success = true;

    return success;
}

static void fill_sdl_rect(SDL_Rect *r, int x, int y, int w, int h) {
    r->x = x;
    r->y = y;
    r->h = h;
    r->w = w;
}

// Load media
static bool load_media() {

    // Loading success flag
    bool success = true;

    g_modulated_texture = LTexture_init(g_renderer);
    LTexture_load_from_file(g_modulated_texture, "../../images/logo.png");
    if(g_modulated_texture == NULL) {
        printf( "Unable to load texture image! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        LTexture_set_blend_mode(g_modulated_texture, SDL_BLENDMODE_BLEND);
    }

    g_texture = LTexture_init(g_renderer);
    LTexture_load_from_file(g_texture, "../../images/background.png");
    if(g_texture == NULL) {
        printf( "Unable to load texture image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    LTexture_destroy(g_texture);
    g_texture = NULL;

    // Destroy window
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    // Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}