#ifndef MAZE_H
#define MAZE_H

#include "bool.h"

typedef enum { NORTH, SOUTH, EAST, WEST } Direction; 

typedef struct {
    int x, y;
} Position;

struct Maze;
typedef struct Maze Maze;

Maze init_maze(const char *);

#endif
