#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "defines.h"
#include "App.h"
#include "Entity.h"
#include "Pipe.h"
#include "PipeList.h"
#include "Bird.h"


/*-- Methods --*/

//Constructor

void initBird(App *app, Bird *bird) {
    bird->bird.x = WINDOW_WIDTH/3;
    bird->bird.y = WINDOW_HEIGHT/2;
    bird->bird.w = 50;
    bird->bird.h = 40;
    bird->bird.dy = 0;
    bird->timeSinceJump = -1;
    bird->health = 1;
    bird->angle = 0;

    if (bird->texture != NULL) {
        bird->texture = NULL;
    }

    bird->texture = IMG_LoadTexture(app->renderer, SKIN);
}

void freeBird(Bird *bird) {
    SDL_DestroyTexture(bird->texture);
}

//Behaviour
void moveBird(App *app, Bird *bird) {
    if (app->click && bird->health > 0) {
        Mix_PlayChannel(0, app->sounds[CLICK_SFX], 0);
        bird->timeSinceJump = 0;
        bird->angle = 0;
    }

    app->click = 0;

    bird->timeSinceJump++;
    
    bird->bird.dy = (((bird->timeSinceJump*bird->timeSinceJump)/2)-350)/60;
    
    bird->bird.y += bird->bird.dy;

    bird->angle += (((bird->timeSinceJump*bird->timeSinceJump)/2)-bird->timeSinceJump-300)/125;
}

void checkCollisions(App *app, Bird *bird, PipeList *pipes) {
    for (int i = 0; i < (pipes->numPipes/2)+1 && bird->health > 0; i++) {
        if (isColliding(&bird->bird, &pipes->list[i].pipeTop) || isColliding(&bird->bird, &pipes->list[i].pipeBottom) ||
            bird->bird.y+bird->bird.h < 0 || bird->bird.y > WINDOW_HEIGHT) {
            bird->health = 0;
            bird->timeSinceJump = 5;
            app->state = GAME_OVER_STATE; 
            Mix_PlayChannel(1, app->sounds[BOOM_SFX] , 0);
            break;
        }

        if (pipes->list[i].pipeTop.dy != 1 && pipes->list[i].pipeTop.x + pipes->list[i].pipeTop.w/2 < bird->bird.x) {
            app->score++;
            pipes->list[i].pipeTop.dy = 1;
            Mix_PlayChannel(1, app->sounds[POINT_SFX], 0);
        }

        
    }
}

//Graphics
void drawBird(App *app, Bird *bird) {
    SDL_Rect rect;
    rect.x = bird->bird.x;
    rect.y = bird->bird.y;
    rect.w = bird->bird.w;
    rect.h = bird->bird.h;

    SDL_RenderCopyEx(app->renderer, bird->texture, NULL, &rect, bird->angle, NULL, 0);
}

//Routine
void DoBird(App *app, Bird *bird, PipeList *pipes) {
    if (app->state != TITLE_SCREEN_STATE) {
        checkCollisions(app, bird, pipes);
        moveBird(app, bird);
    }
    drawBird(app, bird);
}