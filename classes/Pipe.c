#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "defines.h"
#include "Entity.h"
#include "Pipe.h"

/*-- Pipe Methods --*/
void initPipe(Pipe *pipe, int index) {
    pipe->pipeTop.x  = WINDOW_WIDTH + PIPE_WIDTH*(index+1) + PIPE_GAP*index;
    pipe->pipeTop.y  = 0;
    pipe->pipeTop.w  = PIPE_WIDTH;
    pipe->pipeTop.h  = 50 + rand()%550;
    pipe->pipeTop.dx = -PIPE_SCROLL_SPEED;
    pipe->pipeTop.dy = 0;

    pipe->pipeBottom.x  = pipe->pipeTop.x;
    pipe->pipeBottom.y  = pipe->pipeTop.h + PIPE_VERTGAP;
    pipe->pipeBottom.w  = PIPE_WIDTH;
    pipe->pipeBottom.h  = WINDOW_HEIGHT - pipe->pipeBottom.y;
    pipe->pipeBottom.dx = -PIPE_SCROLL_SPEED;
    pipe->pipeBottom.dy = 0;
}

void scrollPipe(Pipe *pipe) {
    pipe->pipeTop.x    += pipe->pipeTop.dx;
    pipe->pipeBottom.x += pipe->pipeBottom.dx;
}

void switchPipe(Pipe *pipe, Pipe *prev) {
    pipe->pipeTop.x = prev->pipeTop.x + PIPE_WIDTH + PIPE_GAP;
    pipe->pipeTop.h = rand()%((WINDOW_HEIGHT-PIPE_GAP)/2);
    pipe->pipeTop.dy = 0;

    pipe->pipeBottom.x = pipe->pipeTop.x;
    pipe->pipeBottom.y = pipe->pipeTop.h + PIPE_VERTGAP;
    pipe->pipeBottom.h = WINDOW_HEIGHT - pipe->pipeBottom.y;
    pipe->pipeBottom.dy = 0;
}

