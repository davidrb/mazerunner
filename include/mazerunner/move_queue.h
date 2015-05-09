#ifndef MOVE_QUEUE
#define MOVE_QUEUE

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include <stdlib.h>
#include <assert.h>

/* fixed size statis FIFO queue */
/* #define QUEUE_SIZE before including */

#ifndef QUEUE_SIZE
#define QUEUE_SIZE 1
#endif

Move move_queue[QUEUE_SIZE];
int num_moves = 0;

static inline
void push_move( Move dir) {
    assert( num_moves <= QUEUE_SIZE );

    move_queue[num_moves++] = dir;

    assert(num_moves > 0);
}

static inline
Move next_move() {
    assert(num_moves > 0);

    Move dir = move_queue[0];

    num_moves--;
    for( int i = 0; i < num_moves; i++) {
	move_queue[i] = move_queue[i+1];
    }

    return dir;
}

static inline
bool moves_empty() {
    assert(num_moves >= 0);
    return !(num_moves > 0);
}

#endif
