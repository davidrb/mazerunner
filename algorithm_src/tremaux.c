#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>
#define QUEUE_SIZE 3
#include <mazerunner/move_queue.h>

#include <stdio.h>

int marks[Cols][Rows] = {{0}};
Move prev = Forward;

int num_marks(int x, int y, Direction dir) {
    switch(dir) {
	case North: y++; break;
	case South: y--; break;
	case East: x++; break;
	case West: x--; break;
    }
    x = (x < 0 ? 0 : (x >= Cols ? Cols-1 : x));
    y = (y < 0 ? 0 : (y >= Rows ? Rows-1 : y));

    return marks[x][y];
}

Move move(Maze *maze, Mouse *mouse) {
    int x = mouse->x,
	y = mouse->y,
	dir = mouse->dir;

    if (moves_empty()) {

	bool clear_right = is_clear(mouse, maze, Right);
	bool clear_ahead = is_clear(mouse, maze, Forward);
	bool clear_left = is_clear(mouse, maze, Left);

	if (!clear_right && !clear_left && !clear_ahead ) {
	    push_move(Right);
	    push_move(Right);
	    push_move(Forward);
	} else {
	    for(int i = 0; true; i++) {
		if (clear_ahead && (num_marks(x, y, (dir)) == i)) {
		    push_move(Forward);
		} 
		else if (clear_right && (num_marks(x, y, rotate_cw(dir)) == i)) {
		    push_move(Right);
		    push_move(Forward);
		} 
		else if (clear_left && (num_marks(x, y, rotate_ccw(dir)) == i)) {
		    push_move(Left);
		    push_move(Forward);
		} else {
		    continue;
		}
		break;
	    }
	}
    }

    Move next = next_move();

    if (next == Forward)
	marks[x][y]++;
    else if (next == prev) 
	marks[x][y]++;

    prev = next;
    return next;
}

void reset() {
    for(int i = 0; i < Rows; i++) 
	for(int j = 0; j < Cols; j++)
	    marks[i][j] = 0;
}

void cleanup() {}
void init() {}
