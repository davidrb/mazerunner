#ifndef ALGORITHM_H
#define ALGORITH_H

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

typedef struct Algorithm Algorithm;

Algorithm default_algorithm();
bool load_algorithm( const char *path, Algorithm *alg );

struct Algorithm {
    void (*reset)();
    void (*init)();
    void (*cleanup)();
    Move (*move)(Maze *, Mouse *);
};

#endif
