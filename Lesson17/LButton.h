//
// Created by shx on 19-5-12.
//

#ifndef LEARNSDL2_LBUTTON_H
#define LEARNSDL2_LBUTTON_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include "texture.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200
#define TOP_BUTTONS 4

typedef enum {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4;
} LButtonSprite;

typedef struct {
    // Top left position
    SDL_Point position;

    // Currently used global sprite
    LButtonSprite current_sprite;

    LTexture *texture;

    SDL_Rect *sprite_clips;
} LButton;

LButton *LButton_init(LTexture *texture, SDL_Rect *clips);

void LButton_set_position(LButton *this, int x, int y);

void LButton_handle_event(LButton *this, SDL_Event *e);

void LButton_render(LButton *this);

void LButton_free(LButton *this);
#endif //LEARNSDL2_LBUTTON_H
