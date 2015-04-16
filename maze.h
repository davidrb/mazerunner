#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

typedef enum { North = 0, East, South, West } Direction;

struct Maze;
typedef struct Maze Maze;

extern const int Rows;
extern const int Cols;

Maze *new_maze(const char *);
void delete_maze(Maze *);

bool get_wall(Maze *, int x, int y, Direction);

#endif
