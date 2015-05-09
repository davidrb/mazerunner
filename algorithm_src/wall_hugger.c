#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#define QUEUE_SIZE 3
#include <mazerunner/move_queue.h>

#include <stdio.h>

Move move( Maze* maze, Mouse *mouse ) {
    if (moves_empty()) {
	if (is_clear(mouse, maze, Right)) {
	    push_move(Right);
	    push_move(Forward);
	}

	else if (is_clear(mouse, maze, Forward)) {
	    push_move(Forward);
	}

	else if(is_clear(mouse, maze, Left)) {
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
