// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include "texture.h"
#include "LButton.h"

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
static TTF_Font *g_font;
static LTexture *g_text_texture = NULL;

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

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
                    }

                    for(int i = 0; i < BUTTON_SPRITE_TOTAL)
                }

                SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // Clear screen
                SDL_RenderClear(g_renderer);


                LTexture_render(g_text_texture,
                                (SCREEN_WIDTH - g_text_texture->width) / 2,
                                (SCREEN_HEIGHT - g_text_texture->height) / 2,
                        NULL, 0, NULL, SDL_FLIP_NONE);

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


    // Initialize PNG loading
    if(!IMG_Init(img_flag) & img_flag) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
                SDL_GetError());
        return success;
    }

    if(TTF_Init() == -1) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
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

    // Open the font
    g_font = TTF_OpenFont("../../fonts/msyh.ttf", 16);
    if(g_font == NULL) {
        printf("Failed to load font! SDL_ttf error: %s\n", TTF_GetError());
        success = false;
    } else {
        SDL_Color textColor = {0};
        g_text_texture = LTexture_init(g_renderer);
        if(!LTexture_load_from_rendered_text(g_text_texture, g_font,
                "This is a 中文test TEXT",
                textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    LTexture_destroy(g_text_texture);
    g_text_texture = NULL;

    TTF_CloseFont(g_font);
    g_font = NULL;

    // Destroy window
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    // Quit SDL subsystem
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}