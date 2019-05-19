// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press surface constants
enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

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

// The images that correspond to a keypress
static SDL_Surface *g_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];

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

            // Set default current surface
            g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

            // While application is running
            while(!quit) {

                // Handle event on queue
                while(SDL_PollEvent(&e) != 0) {

                    // User request quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        if (e.type == SDL_KEYDOWN) {
                            switch (e.key.keysym.sym) {
                                case SDLK_UP:
                                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_UP];
                                    break;
                                case SDLK_DOWN:
                                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                                    break;
                                case SDLK_LEFT:
                                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                                    break;
                                case SDLK_RIGHT:
                                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                                    break;
                                default:
                                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                                    break;
                            }
                        }
                    }
                }

                // Apply the image
                SDL_BlitSurface(g_current_surface, NULL, g_surface, NULL);

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
    g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] =
            load_surface("../../images/press.bmp");
    if(g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf( "Unable to load default image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load up surface
    g_key_press_surfaces[KEY_PRESS_SURFACE_UP] =
            load_surface("../../images/up.bmp");
    if(g_key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf( "Unable to load up image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load down surface
    g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] =
            load_surface("../../images/down.bmp");
    if(g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf( "Unable to load down image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load left surface
    g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] =
            load_surface("../../images/left.bmp");
    if(g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf( "Unable to load left image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    // Load right surface
    g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] =
            load_surface("../../images/right.bmp");
    if(g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf( "Unable to load right image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

// Frees media and shut down SDL
static void close() {
    // Deallocate surface
    for (enum KeyPressSurface i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(g_key_press_surfaces[i]);
        g_key_press_surfaces[i] = NULL;
    }

    // Destroy window
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}

static SDL_Surface *load_surface(char *path) {
    SDL_Surface *loaded_surface = SDL_LoadBMP(path);
    if(loaded_surface == NULL) {
        printf("Unable to load image %s! SDL error: %s\n", path, SDL_GetError());
    }
    return loaded_surface;
}