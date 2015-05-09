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
	y = mouse->y;
    Direction dir = mouse->dir;

    bool clear_right = is_clear(mouse, maze, Right),
	 clear_ahead = is_clear(mouse, maze, Forward),
	 clear_left = is_clear(mouse, maze, Left);

    int  num_right = num_marks(x, y, rotate_cw(dir)),
	 num_ahead = num_marks(x, y, dir),
	 num_left = num_marks(x, y, rotate_ccw(dir));

    if (moves_empty()) {
	if (!clear_right && !clear_left && !clear_ahead ) {
	    push_move(Right);
	    push_move(Right);
	    push_move(Forward);
	} else {
	    for(int i = 0; true; i++) {
		if (clear_ahead && num_ahead == i) {
		    push_move(Forward);
		    break;
		} 

		if (clear_right && num_right == i) {
		    push_move(Right);
		    push_move(Forward);
		    break;
		} 

		if (clear_left && num_left == i) {
		    push_move(Left);
		    push_move(Forward);
		    break;
		}
	    }
	}
    }

    Move next = next_move();

    if (next == Right && next == prev)
	marks[x][y]=2;
    else if (next == Forward && marks[x][y] == 0) 
	marks[x][y]=1;
    else if (marks[x][y] == 1) {
	if ( (!clear_left || num_left != 0) &&
	     (!clear_ahead || num_ahead != 0) &&
	     (!clear_right || num_right != 0))
	    marks[x][y] = 2;
    }

    prev = next;

    FILE *file = fopen("tremaux.txt", "w");
    for (int i = Rows-1; i >= 0; i--) {
	for (int j = 0; j < Cols; j++)
	    fprintf(file, " %d ", marks[j][i]);
	fprintf(file, "\n");
    }
    fclose(file);

    return next;
}

void reset() {
    for(int i = 0; i < Rows; i++) 
	for(int j = 0; j < Cols; j++)
	    marks[i][j] = 0;
}

void cleanup() {}
void init() {}
