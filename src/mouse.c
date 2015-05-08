#define MOUSE_DEF
#include <mazerunner/mouse.h>
#include <mazerunner/maze.h>

Direction rotate_cw( Direction dir ) {
    return (dir+1) % 4;
}

Direction rotate_ccw( Direction dir ) {
    return (dir+3) % 4;
}

Mouse create_mouse() {
    Mouse mouse = {
	.x = 0, .y = 0,
	.dir = North,
	.crashed = false,
	.visited = {{false}},
	.invincible = false,
	.ghost = false,
	.cells = 1,
	.unique_cells = 1,
    };

    mouse.visited[mouse.x][mouse.y] = true;

    return mouse;
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

void move_mouse(Mouse *mouse, Maze *maze, Move move) {
    if (move == Forward) 
	go_forward(mouse, maze);
    else if (move == Left)
	turn_left(mouse);
    else
	turn_right(mouse);
}

void go_forward(Mouse *mouse, Maze *maze) {
    if (did_crash(mouse)) return;

    Direction dir = getDir(mouse);
    int x = mouse->x, y = mouse->y;

    if ( get_wall(maze, x, y, dir) && !mouse->ghost ) {
	mouse->crashed = !mouse->invincible;
    } else {
	if(dir == North) y++;
	else if(dir == South) y--;
	else if(dir == East) x++;
	else if(dir == West) x--;

	if (x < 0 || x >= Cols || y < 0 || y >= Rows) {
	    mouse->crashed = !mouse->invincible && !mouse->ghost;
	    x = mouse->x;
	    y = mouse->y;
	} else {
	    mouse->cells++;
	    mouse->x = x; 
	    mouse->y = y;
	}
    }

    if(!visited(mouse, x, y)) {
	mouse->visited[x][y] = true;
	mouse->unique_cells++;
    }
}

bool is_clear(Mouse *mouse, Maze *maze, Move move) {
    Direction dir = mouse->dir;
    if (move == Left) 
	dir = rotate_ccw(dir);
    else if (move == Right)
	dir = rotate_cw(dir);

    return !get_wall( maze, mouse->x, mouse->y, dir );
}

void turn_right(Mouse *m) {
    m->dir = (m->dir +1) % 4;
}

void turn_left(Mouse *m) {
    m->dir = (m->dir + 3) % 4;
}

void set_invincible(Mouse *m, bool b) {
    m->invincible = b;
}

void set_ghost(Mouse *m, bool b) {
    m->ghost = b;
}

bool visited(Mouse *mouse, int x, int y) {
    return mouse->visited[x][y];
}

bool did_crash(Mouse *m) {
    return m->crashed;
}
