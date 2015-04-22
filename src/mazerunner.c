#include <stdio.h>

#include "parse.h"

#include "maze.h"
#include "mouse.h"

#include "view.h"

#include "controller.h"

int main(int argc, char *argv[]) {
    Maze maze = create_maze();
    Mouse mouse = create_mouse();
    View view = create_view(5);
    Controller controller = create_controller(&view, &maze, &mouse);

    if (!parse_maze(argc > 1 ? argv[1] : "maze.dat", &maze)) {
	view.destroy();
	fprintf(stderr, "error parsing maze file\n");
	return 1;
    }

    while( update_controller( &controller ) );

    view.destroy();

    return 0;
}
