#include "maze.h"
#include "display.h"
#include "parse.h"

#include "maze_def.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int Rows = MAXR;
const int Cols = MAXC;

Maze *new_maze(const char* path) {
    Maze *maze = malloc(sizeof(Maze));

    if( parseFile(path, maze) == 0)
	return maze;

    free(maze);
    return NULL;
}

void delete_maze(Maze *maze) {
    if(maze) free(maze);
}

bool get_wall(Maze *maze, int x, int y, Direction dir) {
    assert(maze);
    assert(0 <= x && x < Cols);
    assert(0 <= y && y < Rows);

    switch(dir) {
	case North:
	    return maze->hwalls[Rows-y-1][x];
	case South:
	    return maze->hwalls[Rows-y][x];
	case West:
	    return maze->vwalls[Rows-y-1][x];
	case East:
	    return maze->vwalls[Rows-y-1][x+1];
	default:
	    assert(0);
    }
}
