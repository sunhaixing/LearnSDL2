//
// Created by shx on 19-5-23.
//
#include <stdlib.h>
#include "app_window.h"

static void app_window_init(app_window_t *this);
static void app_window_uninit(app_window_t *this);
static void app_window_default_on_render(app_window_t *this);
static void app_window_default_on_event(app_window_t *this);

app_window_t *app_window_create(const char *title,
                                int x, int y, int w,
                                int h, Uint32 flags) {
    app_window_t *window = malloc(sizeof(app_window_t));
    window->x = x;
    window->y = y;
    window->w = w;
    window->h = h;
    window->flags = flags;
    memcpy(window->title, title, strlen(title));
    app_window_init(window);
    return window;
}

void app_window_free(app_window_t *this) {
    app_window_uninit(this);
    free(this);
}

static void app_window_init(app_window_t *this){
    this->window = SDL_CreateWindow(this->title,
            this->x, this->y, this->w, this->h, this->flags);
    if(this->window == NULL) {
        printf("SDL_CreateWindow failed(%s,%d): %s\n",
                __FILE__, __LINE__, SDL_GetError());
        exit(2);
    }

    this->surface = SDL_GetWindowSurface(this->window);
    this->on_render = app_window_default_on_render;
    this->on_event = app_window_default_on_event;
}

static void app_window_uninit(app_window_t *this) {
    SDL_DestroyWindow(this->window);
}

static void app_window_default_on_render(app_window_t *this) {
    SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(this->window);
}

static void app_window_default_on_event(app_window_t *this) {
    return;
}