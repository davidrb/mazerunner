#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

Move move(Maze *maze, Mouse *mouse) {
    if (!is_clear(mouse, maze, Forward))
	return Forward;

    if (!is_clear(mouse, maze, Right))
	return Right;

    if (!is_clear(mouse, maze, Left))
	return Left;

    return Forward;
}

void reset() {
}
