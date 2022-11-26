typedef struct {
    Pipe *list;
    int  numPipes;

    SDL_Texture *pipeBody;
    SDL_Texture *pipeHead;
} PipeList;

void initPipeList(App *app, PipeList *list);
void freePipeList(PipeList *list);
void scrollPipes(PipeList *list);
void switchPipes(PipeList *list);
void drawPipes(App *app, PipeList *list);
void doPipes(App *app, PipeList *list);
