#ifndef QUEUE_SIZE
#define QUEUE_SIZE 100
#endif

#include <stdlib.h>
#include <assert.h>

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

/* inline fixed size queue */

Move move_queue[QUEUE_SIZE];
int num_moves = 0;

void push_move( Move dir) {
    move_queue[num_moves++] = dir;
}

Move next_move() {
    assert(num_moves > 0);

    Move dir = move_queue[0];
    num_moves--;

    for( int i = 0; i < num_moves; i++) {
	move_queue[i] = move_queue[i+1];
    }

    return dir;
}

bool moves_empty() {
    return !(num_moves > 0);
}
