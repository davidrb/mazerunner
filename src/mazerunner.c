#include <stdio.h>

#include "maze.h"
#include "parse.h"
#include "view.h"
#include "mouse.h"

int main() {
    Maze maze;

    if (0 != parse_maze("maze.dat", &maze)) {
	fprintf(stderr, "error opening maze file\n");
	return 1;
    }

    Mouse mouse = create_mouse();

    View view = create_view(5);
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
	    view = create_view(5);
	}

	view.update(&maze, &mouse);
    }

    view.destroy();

    return 0;
}
