#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>
#define QUEUE_SIZE 3
#include <mazerunner/move_queue.h>

#include <time.h>
#include <stdlib.h>

void init() {}
void cleanup() {}
    
Move moves[3] = { Forward, Left, Right };

Move move(Maze *maze, Mouse *mouse) {
    Move next;

    if( moves_empty() ) {
	if (!is_clear(mouse, maze, Forward) &&
	    !is_clear(mouse, maze, Left) &&
	    !is_clear(mouse, maze, Right)) {
	    
	    push_move(Right);
	    push_move(Right);
	    push_move(Forward);
	} else {
	    next =  moves[rand()%3];
	    while (!is_clear(mouse, maze, next) || next == NoMove) {
		next=(next+1)%4;
	    }
	    push_move(next);
	    if (next != Forward)
		push_move(Forward);
	}
    }

    return next_move();
}

void reset() {
    srand(time(NULL));
}
