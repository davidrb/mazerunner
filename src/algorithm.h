#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "mouse.h"
#include "maze.h"

struct Algorithm;
typedef struct Algorithm Algorithm;

void update(Algorithm *, Maze *, Mouse *);

#endif
