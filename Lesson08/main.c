// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and create window
static bool init();

// Load media
static bool load_media();

// Frees media and shut down SDL
static void close();

// Load individual image as texture
static SDL_Texture *load_texture(char *path);

// The window we'll be rendering to
static SDL_Window *g_window = NULL;

// The window renderer
static SDL_Renderer *g_renderer = NULL;

// Current displayed texture
static SDL_Texture *g_current_texture = NULL;

int main(int argc, char *argv[]) {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

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
                    }
                }

                // Clear screen
                SDL_SetRenderDrawColor(g_renderer, 0x5E, 0x5E, 0x5E, 0xFF);
                SDL_RenderClear(g_renderer);

                // Render red filled rect
                SDL_Rect fill_rect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
                                      SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(g_renderer, 0xFF, 0x00, 0x00, 0x0);
                SDL_RenderFillRect(g_renderer, &fill_rect);

                for (int j = SCREEN_WIDTH / 4; j < SCREEN_WIDTH * 3 / 4; ++j) {
                    for (int i = SCREEN_HEIGHT / 4; i < SCREEN_HEIGHT * 3 / 4; ++i) {
                        SDL_SetRenderDrawColor(g_renderer, 0xFF * (i - SCREEN_HEIGHT / 4)/ (SCREEN_HEIGHT / 2), 125, 125, 0xFF);
                        SDL_RenderDrawPoint(g_renderer, j , i);
                    }
                }

                // Render green outlined quad
                SDL_Rect outline_rect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                                         SCREEN_WIDTH * 2 / 3,
                                         SCREEN_HEIGHT * 2 / 3};
                SDL_SetRenderDrawColor(g_renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(g_renderer, &outline_rect);



                SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(g_renderer, 0, SCREEN_HEIGHT / 2,
                        SCREEN_WIDTH, SCREEN_HEIGHT / 2);


                for (int i = 0; i < SCREEN_HEIGHT; i += 3) {
                    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, i * 0xFF / SCREEN_HEIGHT, 0xFF);
                    SDL_RenderDrawPoint(g_renderer, SCREEN_WIDTH / 2 , i);
                }

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

// Load media
static bool load_media() {

    // Loading success flag
    bool success = true;

    // Nothing to load
    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    SDL_DestroyTexture(g_current_texture);
    g_current_texture = NULL;

    // Destroy window
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_renderer = NULL;

    // Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}

static SDL_Texture *load_texture(char *path) {
    SDL_Texture *new_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if(loaded_surface == NULL) {
        printf("Unable to load image %s! SDL error: %s\n", path, SDL_GetError());
    } else {
        new_texture = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);
        if(new_texture == NULL) {
            printf("Unable to create texture from %s! SDL error: %s\n",
                    path, SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }
    return new_texture;
}