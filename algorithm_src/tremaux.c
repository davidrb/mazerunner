#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>
#include <mazerunner/move_queue.h>

void init() {
}

int marks[Cols][Rows] = {{0}};

Move move(Mouse *mouse, Maze *maze) {
    /*
    int x = mouse->x,
	y = mouse->y;

    marks[x][y]++;
*/
    mouse++;
    maze++;
    Move next = Forward;
    return next;
}

void reset() {
}

void cleanup() {
}
