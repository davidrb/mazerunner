#include <stdio.h>

#include "maze.h"
#include "parse.h"
#include "view.h"

#include "mouse.h"

int main(int argc, char *argv[]) {
    Maze maze = create_maze();
    Mouse mouse = create_mouse();
    View view = create_view(0);

    if (!parse_maze(argc > 1 ? argv[1] : "maze.dat", &maze)) {
	view.destroy();
	fprintf(stderr, "error parsing maze file\n");
	return 1;
    }

    view.update(&maze, &mouse);

    for( char c = getchar(); c != 'q'; c = getchar()) {
	if (c == 'w')
	    move_mouse(&mouse, &maze);
	else if (c == 'a')
	    turn_left(&mouse);
	else if (c == 'd')
	    turn_right(&mouse);
	else if (c == 'r') {
	    mouse = create_mouse();
	    view.destroy();
	    view = create_view(2);
	}

	view.update(&maze, &mouse);
    }

    view.destroy();

    return 0;
}
