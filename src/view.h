#ifndef VIEW_H
#define VIEW_H

#include "maze.h"
#include "mouse.h"

typedef struct {
    void (*update)(Maze *, Mouse *);
    void (*write_message)(char *);
    void (*destroy)();
} View;

View create_view( int level);

#endif
