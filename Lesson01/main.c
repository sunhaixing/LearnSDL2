// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {

    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *surface = NULL;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        exit(1);
    }

    // Create window
    window = SDL_CreateWindow("SDL Tutorial",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Window could not be created! SDL error: %s\n", SDL_GetError());
        exit(1);
    }

    // Get window surface
    surface = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait two second
    SDL_Delay(2000);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystem
    SDL_Quit();
    return 0;
}