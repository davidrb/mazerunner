#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include <mazerunner/move_queue.h>

#include <stdio.h>

void init() {
}

Move queue[3];

Move move( Maze* maze, Mouse *mouse ) {
    int right = rotate_cw(mouse->dir),
	left = rotate_ccw(mouse->dir),
	forward = mouse->dir,
	x = mouse->x,
	y = mouse->y;

    if (moves_empty()) {
	if (!get_wall(maze, x, y, right)) {
	    push_move(Right, queue);
	    push_move(Forward, queue);
	}

	else if (!get_wall(maze, x, y, forward)) {
	    push_move(Forward, queue);
	}

	else if(!get_wall(maze, x, y, left)) {
	    push_move(Left, queue);
	    push_move(Forward, queue);
	}

	else {
	    push_move(Right, queue);
	    push_move(Right, queue);
	    push_move(Forward, queue);
	}
    }

    return next_move(queue);
}

void reset() {
    while(!moves_empty()) next_move(queue);
}

void cleanup() {
}
