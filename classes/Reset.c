#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"
#include "App.h"
#include "Entity.h"
#include "Pipe.h"
#include "PipeList.h"
#include "Bird.h"
#include "Menu.h"


void Reset(App *app, Bird *bird, PipeList *list, Menu *menu) {
    freeBird(bird);
    freePipeList(list);
    menu->yPos = WINDOW_HEIGHT;
    menu->cpt = 0;
    app->score = 0;
    if (app->state == RESTART_STATE) {
        app->state = GAME_STATE;
        initBird(app, bird);
        initPipeList(app, list);
    } 
}