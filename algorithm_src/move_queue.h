#include <stdlib.h>
#include <assert.h>

#include <mazerunner/maze.h>

int num_moves = 0;

void push_move( Direction dir, Direction *queue) {
    queue[num_moves++] = dir;
}

Direction next_move( Direction *queue ) {
    assert(num_moves > 0);

    Direction dir = queue[0];
    num_moves--;

    for( int i = 0; i < num_moves; i++) {
	queue[i] = queue[i+1];
    }

    return dir;
}

bool moves_empty() {
    return !(num_moves > 0);
}
