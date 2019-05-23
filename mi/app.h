//
// Created by shx on 19-5-23.
//

#ifndef LEARNSDL2_APP_H
#define LEARNSDL2_APP_H


#include <stdbool.h>
#include "app_error.h"
#include "app_window.h"

typedef struct {
    app_window_t *windows;

    bool quit;
} app_t;

app_t *app_create(int argc, char *argv[]);
void app_free(app_t *this);

app_error_t app_create_window(app_t *this,
                              const char *title,
                              int x, int y, int w,
                              int h, Uint32 flags);

app_error_t app_run(app_t *this);

#endif //LEARNSDL2_APP_H
