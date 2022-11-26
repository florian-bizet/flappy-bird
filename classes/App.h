/*-- Structure --*/

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Mix_Chunk *sounds[NUM_SOUNDS];
    int keys[400];
    char click;
    char isTransitioning;
    int score;
    int state;
    int highscore;
    
    FILE *highscoreFile;
} App;


/*-- Methods --*/

//Window Manager
void QuitSDL(App *app);
void InitSDL(App *app);

//Audio Manager
void LoadSounds(Mix_Chunk **sounds);
void FreeSounds(Mix_Chunk **sounds);

//Graphics Manager
void Clear(App *app);
void Update(App *app);

//Input Manager
void DoKeyDown(App *app, SDL_KeyboardEvent *event);
void DoKeyUp(App *app, SDL_KeyboardEvent *event);
void DoInput(App *app);
void UpdateState(App *app);

//Misc Methods
char* scoreToString(App *app);
void  saveHighScore(App *app);

//Routine (function called in main)
void DoApp(App *app);

