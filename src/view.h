#ifndef VIEW_H
#define VIEW_H

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

typedef struct {
    void (*update)(Maze *, Mouse *);
    void (*write_message)(char *);
    void (*destroy)();
} View;

View create_view( int level);

#endif
