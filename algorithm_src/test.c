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

#pragma GCC diagnostic ignored "-Wunused-parameter"
Direction move( Maze* maze, Mouse *mouse ) {
    fprintf(logfile, "moving\n");
    return West;
}
