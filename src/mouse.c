#define MOUSE_DEF
#include "mouse.h"
#include "maze.h"

Mouse create_mouse() {
    Mouse mouse = {
	.x = 0, .y = 0,
	.dir = North,
	.crashed = false,
	.visited = { {false} },
	.cells = 1,
	.unique_cells = 1,
    };
    mouse.visited[0][0] = true;

    return mouse;
}

int getX(Mouse *m) {
    return m->x;
}

int getY(Mouse *m) {
    return m->y;
}

int get_cells( Mouse *mouse ) {
    return mouse->cells;
}

int get_unique_cells( Mouse *mouse ) {
    return mouse->unique_cells;
}

Direction getDir(Mouse *m) {
    return m->dir;
}

void move_mouse(Mouse *mouse, Maze *maze) {
    if (did_crash(mouse)) return;

    Direction dir = getDir(mouse);
    int x = getX(mouse), y = getY(mouse);

    if ( get_wall(maze, x, y, dir) ) {
	mouse->crashed = true;
    } else {
	if(dir == North) y++;
	else if(dir == South) y--;
	else if(dir == East) x++;
	else if(dir == West) x--;

	if (x < 0 || x >= Cols || y < 0 || y >= Rows) {
	    mouse->crashed = true;
	} else {
	    mouse->x = x; mouse->y = y;
	}
    }

    mouse->cells++;
    if(!visited(mouse, x, y)) {
	mouse->visited[x][y] = true;
	mouse->unique_cells++;
    }
}

void turn_right(Mouse *m) {
    m->dir = (m->dir +1) % 4;
}

void turn_left(Mouse *m) {
    m->dir = (m->dir + 3) % 4;
}

bool visited(Mouse *mouse, int x, int y) {
    return mouse->visited[x][y];
}

bool did_crash(Mouse *m) {
    return m->crashed;
}
