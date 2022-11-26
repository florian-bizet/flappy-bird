#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#include "defines.h"
#include "App.h"
#include "Entity.h"
#include "Menu.h"

void initFonts(Menu *menu) {
    menu->font       = TTF_OpenFont("Fonts/04B_19__.TTF", 28);
}

void freeFonts(Menu *menu) {
    TTF_CloseFont(menu->font);
}

void drawScore(App *app, Menu *menu) {
    //Colors
    const SDL_Color WHITE = {255, 255, 255};
    const SDL_Color BLACK = { 0 ,  0 ,  0 };
    
    //score to String
    char *stringScore = scoreToString(app);

    SDL_Surface *surface = TTF_RenderText_Solid(menu->font, stringScore, WHITE);
    SDL_Surface *shadow  = TTF_RenderText_Solid(menu->font, stringScore, BLACK);
    
    SDL_Texture *texture   = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_Texture *shadowTex = SDL_CreateTextureFromSurface(app->renderer, shadow);
   
    SDL_Rect rectangle;
    SDL_QueryTexture(shadowTex, NULL, NULL, &rectangle.w, &rectangle.h);
    
    rectangle.w *= 2;
    rectangle.h *= 2;
    rectangle.x = (WINDOW_WIDTH/2) - (rectangle.w/2);
    rectangle.y = (WINDOW_HEIGHT/8);

    SDL_RenderCopy(app->renderer, shadowTex, NULL, &rectangle);

    rectangle.x -= 5;
    rectangle.y -= 5;

    SDL_RenderCopy(app->renderer, texture, NULL, &rectangle);

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(shadowTex);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(shadow);
    
    free(stringScore);
}

void drawTitleScreen(App *app, Menu *menu) {
    //Colors
    const SDL_Color WHITE = {255, 255, 255};
    const SDL_Color BLACK = { 0 ,  0 ,  0 };
    
    SDL_Surface *titleSurface  = TTF_RenderText_Solid(menu->font, "Flappy Bird Clone", WHITE);
    SDL_Surface *shadowSurface = TTF_RenderText_Solid(menu->font, "Flappy Bird Clone", BLACK);

    SDL_Texture *titleTexture  = SDL_CreateTextureFromSurface(app->renderer, titleSurface);
    SDL_Texture *shadowTexture = SDL_CreateTextureFromSurface(app->renderer, shadowSurface);

    SDL_Rect rectangle;
    SDL_QueryTexture(titleTexture, NULL, NULL, &rectangle.w, &rectangle.h);
    
    rectangle.w *= 2;
    rectangle.h *= 2;
    rectangle.x = (WINDOW_WIDTH/2) - (rectangle.w/2) + 5;
    rectangle.y = (WINDOW_HEIGHT/8) + 5;

    SDL_RenderCopy(app->renderer, shadowTexture, NULL, &rectangle);

    rectangle.x -= 5;
    rectangle.y -= 5;

    SDL_RenderCopy(app->renderer, titleTexture, NULL, &rectangle);
    
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(shadowTexture);

    SDL_FreeSurface(titleSurface);
    SDL_FreeSurface(shadowSurface); 
}

void drawGameOverScreen(App *app, Menu *menu) {
    const SDL_Color WHITE = {255, 255, 255};
    const SDL_Color BLACK = { 0 ,  0 ,  0 };

    char *score = scoreToString(app);
    char scoreTitle[9] = "Score :";
    
    
    SDL_Texture *tex = IMG_LoadTexture(app->renderer, "sprites/GameOverScreen.jpg");
    SDL_Surface *textSurface = TTF_RenderText_Solid(menu->font, scoreTitle, WHITE);
    SDL_Surface *shadowSurface = TTF_RenderText_Solid(menu->font, scoreTitle, BLACK);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(menu->font, score, WHITE);
    SDL_Surface *shadowScoreSurface = TTF_RenderText_Solid(menu->font, score, BLACK);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(app->renderer, textSurface);
    SDL_Texture *shadowTexture = SDL_CreateTextureFromSurface(app->renderer, shadowSurface);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(app->renderer, scoreSurface);
    SDL_Texture *shadowScoreTexture = SDL_CreateTextureFromSurface(app->renderer, shadowScoreSurface);

    SDL_Rect rect;


    rect.w = 300;
    rect.h = 300;

    rect.x = (WINDOW_WIDTH/2) - rect.w/2;

    app->isTransitioning = menu->yPos > (WINDOW_HEIGHT/2) - rect.h/2;

    if (app->isTransitioning) {
        menu->yPos -= (-log(menu->cpt+0.05) + 6)*2.7;
    } 

    rect.y = menu->yPos;

    SDL_RenderCopy(app->renderer, tex, NULL, &rect);

    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    rect.y = menu->yPos - rect.h - 15;
    rect.x += 5;

    SDL_RenderCopy(app->renderer, shadowTexture, NULL, &rect);

    rect.x -= 5;
    rect.y -= 5;

    SDL_RenderCopy(app->renderer, textTexture, NULL, &rect);

    rect.x += rect.w + 15;
    rect.y += 5;

    SDL_QueryTexture(scoreTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(app->renderer, shadowScoreTexture, NULL, &rect);

    rect.x -= 5;
    rect.y -= 5;

    SDL_RenderCopy(app->renderer, scoreTexture, NULL, &rect);


    SDL_DestroyTexture(tex);

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(shadowSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(shadowScoreSurface);

    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(shadowTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(shadowScoreTexture);

    menu->cpt++;
    free(score);
}

void DoMenu(App *app, Menu *menu) {
    switch (app->state) {
        case TITLE_SCREEN_STATE: 
            menu->yPos = WINDOW_HEIGHT;
            menu->cpt = 0;
            drawTitleScreen(app, menu);
            break;
        case GAME_STATE: 
            drawScore(app, menu);
            break;
        case GAME_OVER_STATE: 
            drawGameOverScreen(app, menu);
            break;
    }
}