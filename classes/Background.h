typedef struct {
    Entity bg[2];

    SDL_Texture *bgTex;
} Background;

void initBG(App *app, Background *bg);
void drawBG(App *app, Background *bg);