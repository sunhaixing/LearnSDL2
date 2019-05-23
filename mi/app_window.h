//
// Created by shx on 19-5-23.
//

#ifndef LEARNSDL2_APP_WINDOW_H
#define LEARNSDL2_APP_WINDOW_H

#include <SDL2/SDL.h>



struct app_window_t;
typedef struct app_window_t app_window_t;

typedef void(* on_render_t) (app_window_t*);
typedef void(* on_event_t) (app_window_t*);

struct app_window_t{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;

    char title[255];
    int x;
    int y;
    int w;
    int h;
    uint32_t flags;

    on_render_t on_render;
    on_event_t on_event;

    app_window_t *next;
} ;

app_window_t *app_window_create(const char *title,
                                int x, int y, int w,
                                int h, Uint32 flags);
void app_window_free(app_window_t *this);

#endif //LEARNSDL2_APP_WINDOW_H
