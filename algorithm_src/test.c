#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include <mazerunner/move_queue.h>

#include <stdio.h>

void init() {
}

Move move( Maze* maze, Mouse *mouse ) {
    int right = rotate_cw(mouse->dir),
	left = rotate_ccw(mouse->dir),
	forward = mouse->dir,
	x = mouse->x,
	y = mouse->y;

    if (moves_empty()) {
	if (!get_wall(maze, x, y, right)) {
	    push_move(Right);
	    push_move(Forward);
	}

	else if (!get_wall(maze, x, y, forward)) {
	    push_move(Forward);
	}

	else if(!get_wall(maze, x, y, left)) {
	    push_move(Left);
	    push_move(Forward);
	}

	else {
	    push_move(Right);
	    push_move(Right);
	    push_move(Forward);
	}
    }

    return next_move();
}

void reset() {
    while(!moves_empty()) next_move();
}

void cleanup() {
}
