//
// Created by shx on 19-5-12.
//

#include <stdbool.h>
#include "LButton.h"

LButton *LButton_init(LTexture *texture, SDL_Rect *clips) {
    LButton *ret;

    ret = malloc(sizeof(LButton));
    ret->position.x = 0;
    ret->position.y = 0;
    ret->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    ret->texture = texture;
    ret->sprite_clips = clips;
}

void LButton_set_position(LButton *this, int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

void LButton_handle_event(LButton *this, SDL_Event *e) {
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN
        || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if(x < this->position.x
            || x > this->position.y + BUTTON_WIDTH
            || y < this->position.y
            || y > this->position.y + BUTTON_HEIGHT) {
            inside = false;
            this->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    this->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    this->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    this->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
            }
        }
    }
}

void LButton_render(LButton *this) {
    LTexture_render(this->texture, this->position.x, this->position.y, &this->sprite_clips[this->current_sprite],
            0, NULL, SDL_FLIP_NONE);
}

void LButton_free(LButton *this) {
    free(this);
}