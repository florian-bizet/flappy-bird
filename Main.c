#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "classes/defines.h"

#include "classes/App.h"
#include "classes/Entity.h"
#include "classes/Pipe.h"
#include "classes/PipeList.h"
#include "classes/Bird.h"
#include "classes/Menu.h"
#include "classes/Reset.h"
#include "classes/Background.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    App app;
    InitSDL(&app);

    Bird bird;
    

    PipeList pipes;
    Background bg;
    initBG(&app, &bg);

    Menu menu;
    initFonts(&menu);

    initBird(&app, &bird);
    initPipeList(&app, &pipes);

    while (app.state != CLOSING_STATE) {
        while (app.state != RESTART_STATE && app.state != CLOSING_STATE) {
            doPipes(&app, &pipes);
            DoBird(&app, &bird, &pipes);
            DoMenu(&app, &menu);
            DoApp(&app);
            drawBG(&app, &bg);
        }
        Reset(&app, &bird, &pipes, &menu);
    }

    freeFonts(&menu);
    QuitSDL(&app);

    return 0;
}