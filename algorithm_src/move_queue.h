#include <stdlib.h>
#include <assert.h>

#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

int num_moves = 0;

void push_move( Move dir, Move *queue) {
    queue[num_moves++] = dir;
}

Move next_move( Move *queue ) {
    assert(num_moves > 0);

    Move dir = queue[0];
    num_moves--;

    for( int i = 0; i < num_moves; i++) {
	queue[i] = queue[i+1];
    }

    return dir;
}

bool moves_empty() {
    return !(num_moves > 0);
}
