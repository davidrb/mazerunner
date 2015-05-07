#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include "parse.h"
#include "view.h"
#include "controller.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    Maze maze = create_maze();
    Mouse mouse = create_mouse();
    Algorithm algorithm = default_algorithm();

    if (!parse_maze(argc > 1 ? argv[1] : "maze.dat", &maze)) {
	fprintf(stderr, "error parsing maze file\n");
	return 1;
    }
    
    if (argc > 2) {
	if(!load_algorithm(argv[2], &algorithm)) {
	    fprintf(stderr, "error loading algorithm");
	    return 2;
	}
	
    }

    View view = create_view(5);
    Controller controller = create_controller(&view, &maze, &mouse, &algorithm);

    while(do_command( &controller, getchar() ));

    view.destroy();

    return 0;
}

