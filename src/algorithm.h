#ifndef ALGORITHM_H
#define ALGORITH_H

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

typedef struct {
    void (*reset)();
    void (*init)();
    void (*cleanup)();
    Direction (*move)(Maze *, Mouse *);
} Algorithm;

Algorithm default_algorithm();
bool load_algorithm( const char *path, Algorithm *alg );

#endif
