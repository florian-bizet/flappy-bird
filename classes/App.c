#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"
#include "App.h"


//Window Manager

//Destructor
void QuitSDL(App *app) {
    
    
    if (app->renderer != NULL) {
        SDL_DestroyRenderer(app->renderer);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    FreeSounds(app->sounds);    
    Mix_CloseAudio();
    TTF_Quit();

    SDL_Quit();
    app->state = CLOSING_STATE;
}

//Constructor
void InitSDL(App *app) {
    //Initializing app to avoid segfaults
    app->window = NULL;
    app->renderer = NULL;
    
    //Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("\nError initializing SDL : %s", SDL_GetError());
        QuitSDL(app);
    } else {
        printf("\nSuccessfully initialized SDL !");
    }

    //Creating Window
    app->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (app->window == NULL) {
        printf("\nError creating window : %s", SDL_GetError());
        QuitSDL(app);
    } else {
        printf("\nSuccessfully created window !");
    }

    //Creating Renderer
    app->renderer = SDL_CreateRenderer(app->window, -1, 0);
    if (app->renderer == NULL) {
        printf("\nError creating renderer : %s", SDL_GetError());
        QuitSDL(app);
    } else {
        printf("\nSuccessfully created Renderer !");
    }

    //Creating audio channels
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        printf("\nError initializing Audio : %s", SDL_GetError());
        QuitSDL(app);
    } else {
        printf("\nSuccessfully initialized audio !");
    }

    if (TTF_Init() == -1) {
        printf("\nError initializing TTF: %s", SDL_GetError());
        QuitSDL(app);
    } else {
        printf("\nSuccessfully initialized TTF !");
    }

    Mix_AllocateChannels(NUM_CHAN);
    LoadSounds(app->sounds);

    for (int i = 0; i < 300; i++) {
        app->keys[i] = 0;
    }

    app->click = 0;
    app->isTransitioning = false;
    app->score = 0;
    app->state = TITLE_SCREEN_STATE;

    printf("\nEverything has been successfully initialized");
}

//Graphics Manager

void Clear(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 88, 172, 224, 255);
    SDL_RenderClear(app->renderer);
}

void Update(App *app) {
    SDL_RenderPresent(app->renderer);
}

//Input Manager

void DoKeyDown(App *app, SDL_KeyboardEvent *event) {
    if (event->keysym.scancode < 300) {
        app->keys[event->keysym.scancode] = 1;
    }
}

void DoKeyUp(App *app, SDL_KeyboardEvent *event) {
    if (event->keysym.scancode < 300) {
        app->keys[event->keysym.scancode] = 0;
    }
}

void DoInput(App *app) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                app->state = CLOSING_STATE;
                break;
            case SDL_KEYDOWN:
                DoKeyDown(app, &event.key);
                break;
            case SDL_KEYUP:
                DoKeyUp(app, &event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                app->click = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                app->click = 0;
                
                break;
        }
    }
}

void UpdateState(App *app) {
    if (app->click && !app->isTransitioning) {
        switch (app->state) {
            case TITLE_SCREEN_STATE:
                app->state = GAME_STATE;
                break;
            case GAME_OVER_STATE:
                app->state = RESTART_STATE;
                break;
            
        }
    }
}

//Misc Methods

char* scoreToString(App *app) {
    /* Allocates memory for the string
       Assumes caller calls free afterwards */
    int length = snprintf(NULL, 0, "%d", app->score);
    char *sRet = malloc(length+1);
    snprintf(sRet, length+1, "%d", app->score);

    return sRet;

}

//Audio Manager

void LoadSounds(Mix_Chunk **sounds) {
    sounds[CLICK_SFX] = Mix_LoadWAV("sounds/flap.wav");
    sounds[BOOM_SFX]  = Mix_LoadWAV("sounds/vineboom.wav");
    sounds[POINT_SFX] = Mix_LoadWAV("sounds/pass.wav");
    Mix_VolumeChunk(sounds[BOOM_SFX], 40);
    Mix_VolumeChunk(sounds[POINT_SFX], 50);
}

void FreeSounds(Mix_Chunk **sounds) {
    for (int i = 0; i < NUM_CHAN; i++) {
        Mix_FreeChunk(sounds[i]);
    }
}

//Routine
void DoApp(App *app) {
    Update(app);
    SDL_Delay(16);
    Clear(app);
    DoInput(app);
    UpdateState(app); 
}