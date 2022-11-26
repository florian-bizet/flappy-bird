typedef struct {
    Entity pipeTop;
    Entity pipeBottom;
} Pipe;

/*-- Pipe Methods     --*/
void initPipe(Pipe *pipe, int index);
void scrollPipe(Pipe *pipe);
void switchPipe(Pipe *pipe, Pipe *prev);

