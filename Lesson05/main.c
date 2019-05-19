// Using SDL and standard IO
#include <SDL2/SDL.h>
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

static SDL_Surface *load_surface(char *path);

// The window we'll be rendering to
static SDL_Window *g_window = NULL;

// The surface contained by the window
static SDL_Surface *g_surface = NULL;

// Current displayed image
static SDL_Surface *g_current_surface = NULL;

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

                // Apply the image
                //SDL_BlitSurface(g_current_surface, NULL, g_surface, NULL);

                SDL_BlitScaled(g_current_surface, NULL,
                        g_surface, &stretch_rect);

                // Update the window
                SDL_UpdateWindowSurface(g_window);
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

    // Get window surface
    g_surface = SDL_GetWindowSurface(g_window);

    success = true;

    return success;
}

// Load media
static bool load_media() {

    // Loading success flag
    bool success = true;

    // Load default surface
    g_current_surface = load_surface("../../images/small.bmp");
    if(g_current_surface == NULL) {
        printf( "Unable to load default image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    SDL_FreeSurface(g_current_surface);
    g_current_surface = NULL;

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}

static SDL_Surface *load_surface(char *path) {
    SDL_Surface *optimized_surface = NULL;
    SDL_Surface *loaded_surface = SDL_LoadBMP(path);
    if(loaded_surface == NULL) {
        printf("Unable to load image %s! SDL error: %s\n", path, SDL_GetError());
    } else {
        optimized_surface = SDL_ConvertSurface(loaded_surface, g_surface->format,
                0);
        if(optimized_surface == NULL) {
            printf("Unable to optimize surface %s! SDL error: %s\n",
                    path, SDL_GetError());
        }

        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
}