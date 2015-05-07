#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include "parse.h"
#include "view.h"
#include "controller.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    Maze maze = create_maze();
    Mouse mouse = create_mouse();
    View view = create_view(5);

    if (!parse_maze(argc > 1 ? argv[1] : "maze.dat", &maze)) {
	view.destroy();
	fprintf(stderr, "error parsing maze file\n");
	return 1;
    }

    Controller controller = create_controller(&view, &maze, &mouse);
    while(do_command( &controller, getchar() ));

    view.destroy();

    return 0;
}

