/*-- Structure --*/
typedef struct {
    int x;
    int y;
    int w;
    int h;
    int dx;
    int dy;
} Entity;

/*-- Methods --*/
int isColliding(const Entity *entity1, const Entity *entity2);