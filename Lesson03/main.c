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

// The window we'll be rendering to
static SDL_Window *g_window = NULL;

// The surface contained by the window
static SDL_Surface *g_surface = NULL;

// The image we'll load and show on the screen
static SDL_Surface *g_hello = NULL;

int main(int argc, char *argv[]) {

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
                }

                // Apply the image
                SDL_BlitSurface(g_hello, NULL, g_surface, NULL);

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
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_RESIZABLE);
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

    // Load splash image
    g_hello = SDL_LoadBMP("../../images/x.bmp");
    if(g_hello == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n",
                "hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    SDL_FreeSurface(g_hello);
    g_hello = NULL;

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}