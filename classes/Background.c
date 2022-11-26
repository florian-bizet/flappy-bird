#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"
#include "App.h"
#include "Entity.h"
#include "Background.h"

void initBG(App *app, Background *bg) {
    bg->bg[0].x  = 0;
    bg->bg[0].h  = WINDOW_HEIGHT;
    bg->bg[0].y  = 0;
    bg->bg[0].w  = 1920 * WINDOW_WIDTH / WINDOW_HEIGHT;

    bg->bg[1].x  = 1920 * WINDOW_WIDTH / WINDOW_HEIGHT;
    bg->bg[1].h  = WINDOW_HEIGHT;
    bg->bg[1].y  = 0;
    bg->bg[1].w  = 1920 / 1.6;

    bg->bgTex = IMG_LoadTexture(app->renderer, "sprites/bg.png");
}

void drawBG(App *app, Background *bg) {
    SDL_Rect rect;

    Entity *tmp;
    if (bg->bg[0].x < -bg->bg[0].w) {
        tmp = &bg->bg[0];
        bg->bg[0] = bg->bg[1];
        bg->bg[1] = *tmp;
        bg->bg[1].x = bg->bg[0].x + bg->bg[0].w;
    }

    for (int i = 0; i < 2; i++) {
    if (app->state != GAME_OVER_STATE) {bg->bg[i].x -= BG_SCROLL_SPEED;}
        rect.x = bg->bg[i].x;
        rect.y = bg->bg[i].y;
        rect.w = bg->bg[i].w;
        rect.h = bg->bg[i].h;

        SDL_RenderCopy(app->renderer, bg->bgTex, NULL, &rect);
    }
} 