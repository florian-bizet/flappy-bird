typedef struct {
    Entity bird;

    int timeSinceJump;
    int health;
    double angle;
    SDL_Texture *texture;
} Bird;

/*-- Methods --*/

//Constructor
void initBird(App *app, Bird *bird);
void freeBird(Bird *bird);

//Behaviour
void moveBird(App *app, Bird *bird);

//Graphics
void drawBird(App *app, Bird *bird);
void checkCollisions(App *app, Bird *bird, PipeList *pipes);

//Routine
void DoBird(App *app, Bird *bird, PipeList *pipes);