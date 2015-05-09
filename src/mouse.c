#include <mazerunner/mouse.h>
#include <mazerunner/maze.h>

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
	.won = false,
    };

    mouse.visited[mouse.x][mouse.y] = true;

    return mouse;
}

void move_mouse(Mouse *mouse, Maze *maze, Move move) {
    if (move == Forward) 
	go_forward(mouse, maze);
    else if (move == Left)
	mouse->dir = rotate_ccw(mouse->dir);
    else
	mouse->dir = rotate_cw(mouse->dir);
}

void go_forward(Mouse *mouse, Maze *maze) {
    if (mouse->crashed) return;

    Direction dir = mouse->dir;
    int x = mouse->x, y = mouse->y;

    if ( get_wall(maze, x, y, dir) && !mouse->ghost ) {
	mouse->crashed = !mouse->invincible;
    } else {
	offset(&x, &y, dir);

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

   if( (mouse->x == 7 || mouse->x == 8) && 
       (mouse->y == 7 || mouse->y == 8 ))
       mouse->won = true;
}

bool is_clear(Mouse *mouse, Maze *maze, Move move) {
    Direction dir = mouse->dir;
    if (move == Left) 
	dir = rotate_ccw(dir);
    else if (move == Right)
	dir = rotate_cw(dir);

    return !get_wall( maze, mouse->x, mouse->y, dir );
}

bool visited(Mouse *mouse, int x, int y) {
    return mouse->visited[x][y];
}

