#ifndef MAZE_H
#define MAZE_H

struct Mouse;

#include <stdbool.h>

typedef enum { Rows = 16, Cols = 16 } MazeLimits;
typedef enum { North = 0, East=1, South=2, West=3 } Direction;

Direction rotate_cw( Direction d );
Direction rotate_ccw( Direction d );

typedef bool HLine[Cols];
typedef bool VLine[Cols+1];

typedef HLine HWalls[Rows+1];
typedef VLine VWalls[Rows];

typedef struct {
    VWalls vwalls;
    HWalls hwalls;
} Maze;

Maze create_maze();
int load_maze(Maze* maze, const char *);

void reveal_maze( Maze *maze );
void unreveal_maze( Maze *maze, struct Mouse * );

bool get_wall(Maze *, int x, int y, Direction);

#endif
