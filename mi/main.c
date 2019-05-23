#include <stdio.h>
#include "app.h"

int main(int argc, char *argv[]) {
    app_t *app = app_create(argc, argv);
    app_create_window(app, "test",
            SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800, 600,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    app_error_t ret = app_run(app);
    app_free(app);
    return ret;
}