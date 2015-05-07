#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include <stdio.h>

FILE *logfile = 0;

void init() {
    logfile = fopen("log", "w");
    fprintf(logfile, "init\n");
    fprintf(stderr, "initializing algorithm\n");
}

void reset() {
    fprintf(logfile, "reset\n");
}

Direction move( Maze* maze, Mouse *mouse ) {
    fprintf(logfile, "moving\n");

    if ( get_wall(maze, mouse->x, mouse->y, mouse->dir) ) {
	return East;
    }

    return North;
}

void cleanup() {
    fprintf(stderr, "algorithm finished.\n");
    fclose(logfile);
}
