#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include "move_queue.h"

#include <stdio.h>

void init() {
}

Direction queue[3];

Direction move( Maze* maze, Mouse *mouse ) {
    int right = rotate_cw(mouse->dir),
	left = rotate_ccw(mouse->dir),
	forward = mouse->dir,
	x = mouse->x,
	y = mouse->y;

    if (moves_empty()) {
	if (!get_wall(maze, x, y, right)) {
	    push_move(East, queue);
	    push_move(North, queue);
	}

	else if (!get_wall(maze, x, y, forward)) {
	    push_move(North, queue);
	}

	else if(!get_wall(maze, x, y, left)) {
	    push_move(West, queue);
	    push_move(North, queue);
	}

	else {
	    push_move(East, queue);
	    push_move(East, queue);
	    push_move(North, queue);
	}
    }

    return next_move(queue);
}

void reset() {
    while(!moves_empty()) next_move(queue);
}

void cleanup() {
}
