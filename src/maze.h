#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

typedef enum { Rows = 16, Cols = 16 } MazeLimits;
typedef enum { North = 0, East=1, South=2, West=3 } Direction;

typedef struct {
    bool vwalls[Rows][Cols+1];
    bool hwalls[Rows+1][Cols];
} Maze;

Maze create_maze();
int load_maze(Maze* maze, const char *);

bool get_wall(Maze *, int x, int y, Direction);

#endif
