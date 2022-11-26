typedef struct {
    TTF_Font *font;
    int yPos;
    int cpt;
} Menu;

void initFonts(Menu *menu);
void freeFonts(Menu *menu);
void drawScore(App *app, Menu *menu);
void drawTitleScreen(App *app, Menu *menu);
void drawGameOverScreen(App *app, Menu *menu);

void DoMenu(App *app, Menu *menu);