#ifndef MAZE_H
#define MAZE_H

#include <mazerunner/direction.h>
#include <stdbool.h>

struct Mouse;
typedef struct Maze Maze;

typedef enum { Rows = 16, Cols = 16 } MazeLimits;

Maze create_maze();
int load_maze(Maze* maze, const char *);

bool get_wall(Maze *, int x, int y, Direction);

void reveal_maze( Maze *maze );
void unreveal_maze( Maze *maze, struct Mouse * );

static inline
void clamp_coords( int *x, int *y ) {
    *x = (*x < 0 ? 0 : (*x >= Cols ? Cols-1 : *x));
    *y = (*y < 0 ? 0 : (*y >= Rows ? Rows-1 : *y));
}

typedef bool HLine[Cols];
typedef bool VLine[Cols+1];
typedef HLine HWalls[Rows+1];
typedef VLine VWalls[Rows];

struct Maze {
    VWalls vwalls;
    HWalls hwalls;
};

#endif
