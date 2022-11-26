#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "defines.h"
#include "App.h"
#include "Entity.h"
#include "Pipe.h"
#include "PipeList.h"


void initPipeList(App *app, PipeList *list) {
    list->numPipes = (WINDOW_WIDTH/(PIPE_WIDTH + PIPE_GAP)) + 2;
    list->list = malloc(sizeof(Pipe)*list->numPipes);

    for (int i = 0; i < list->numPipes; i++) {
        initPipe(&list->list[i], i);
    }

    list->pipeHead = IMG_LoadTexture(app->renderer, "sprites/pipeHead.png");
    list->pipeBody = IMG_LoadTexture(app->renderer, "sprites/pipeBody.png");
}

void freePipeList(PipeList *list) {
    free(list->list);
    SDL_DestroyTexture(list->pipeBody);
    SDL_DestroyTexture(list->pipeHead);
}

void scrollPipes(PipeList *list) {
    for (int i = 0; i < list->numPipes; i++) {
        scrollPipe(&list->list[i]);
    }
}

void switchPipes(PipeList *list) {
    Pipe *pipeTemp;
    
    if (list->list[0].pipeTop.x < -list->list[0].pipeTop.w) {
        if (list->numPipes > 1) {
            pipeTemp = &list->list[0];
            for (int j = 1; j < list->numPipes; j++) {
                list->list[j-1] = list->list[j];
            }
            list->list[list->numPipes-1] = *pipeTemp;
            switchPipe(&list->list[list->numPipes-1], &list->list[list->numPipes-2]);
        } else {
            initPipe(&list->list[list->numPipes-1], 0);
        }
        
    }
}

void drawPipes(App *app, PipeList *list) {
    SDL_Rect rect;
    for (int i = 0; i < list->numPipes; i++) {
        
        //Pipe Body
        rect.x = list->list[i].pipeTop.x + 5;
        rect.y = list->list[i].pipeTop.y;
        rect.w = list->list[i].pipeTop.w - 10;
        rect.h = list->list[i].pipeTop.h;

        SDL_RenderCopy(app->renderer, list->pipeBody, NULL, &rect);

        rect.y = list->list[i].pipeBottom.y;
        rect.h = list->list[i].pipeBottom.h;

        SDL_RenderCopy(app->renderer, list->pipeBody, NULL, &rect);

        //Pipe Head
        rect.w = list->list[i].pipeTop.w;
        rect.x = list->list[i].pipeTop.x;
        rect.h = PIPE_WIDTH/2;
        rect.y = list->list[i].pipeTop.h - rect.h;

        SDL_RenderCopy(app->renderer, list->pipeHead, NULL, &rect);
        
        rect.y = list->list[i].pipeBottom.y;

        SDL_RenderCopy(app->renderer, list->pipeHead, NULL, &rect);

    }
}

void doPipes(App *app, PipeList *list) {
    if (app->state == GAME_STATE) {
        scrollPipes(list);
        switchPipes(list);
    }
    drawPipes(app, list);
}