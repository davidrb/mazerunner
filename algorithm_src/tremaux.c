#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>
#include <mazerunner/move_queue.h>

void init() {
}

Move move(Mouse *mouse, Maze *maze) {
    mouse++; maze++;
    return Forward;
}

void reset() {
}

void cleanup() {
}
