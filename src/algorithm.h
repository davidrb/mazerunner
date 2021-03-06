#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

typedef struct Algorithm Algorithm;

Algorithm default_algorithm();
bool load_algorithm( const char *path, Algorithm *alg );

struct Algorithm {
    void (*reset)();
    Move (*move)(Maze *, Mouse *);
};

#endif
