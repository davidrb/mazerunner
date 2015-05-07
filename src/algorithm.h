#ifndef ALGORITHM_H
#define ALGORITH_H

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

typedef struct {
    void (*reset)();
    Direction (*move)();
} Algorithm;

#endif
