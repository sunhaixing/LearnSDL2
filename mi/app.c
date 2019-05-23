//
// Created by shx on 19-5-23.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "app.h"

static void app_init(app_t *this);
static void app_uninit(app_t *this);
static void app_append_window(app_t *this, app_window_t *win);

app_t *app_create(int argc, char *argv[]) {
    app_t *app = malloc(sizeof(app_t));
    app_init(app);
    return app;
}

void app_free(app_t *this) {
    app_uninit(this);
    free(this);
}

app_error_t app_run(app_t *this) {
    SDL_Event e;
    while(!this->quit) {
        while (SDL_PollEvent(&e) != 0) {

            if(e.type == SDL_QUIT) {
                this->quit = true;
            }
        }
        for (app_window_t *w = this->windows; w != NULL; w = w->next) {
            if(w->on_render != NULL)
                w->on_render(w);
        }
    }

}

app_error_t app_create_window(app_t *this,
                              const char *title,
                              int x, int y, int w,
                              int h, Uint32 flags) {
    app_window_t *window = app_window_create(title, x, y, w, h, flags);
    app_append_window(this, window);
}

static void app_init(app_t *this) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed(%s,%d): %s\n", __FILE__, __LINE__, SDL_GetError());
        exit(1);
    }

    if(! (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init failed(%s,%d): %s\n", __FILE__, __LINE__, SDL_GetError());
        exit(1);
    }

    this->windows = NULL;
    this->quit = false;
}

static void app_uninit(app_t *this) {

    app_window_t *next = NULL;
    while(this->windows) {
        next = this->windows->next;
        app_window_free(this->windows);
        this->windows = next;
    }

    IMG_Quit();
    SDL_Quit();
}

static void app_append_window(app_t *this, app_window_t *win) {
    if(this->windows == NULL) {
        this->windows = win;
        return;
    }

    app_window_t *w = NULL;
    for (w = this->windows; w->next != NULL ; w = w->next);

    w->next = win;
}