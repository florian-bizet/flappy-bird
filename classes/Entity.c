#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Entity.h"

int isColliding(const Entity *entity1, const Entity *entity2) {
    if ((entity1->x < entity2->x + entity2->w && entity1->x + entity1->w > entity2->x) && (entity1->y < entity2->y + entity2->h && entity1->y + entity1->h > entity2->y)) {
        return 1;
    }
    return 0;
}