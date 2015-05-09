#include <mazerunner/maze.h>
#include <mazerunner/mouse.h>

#include "parse.h"
#include "view.h"
#include "controller.h"

#include <stdio.h>
#include <string.h>

Maze maze;
Mouse mouse;
Algorithm algorithm;
Controller controller;
View view;

const char *mazefile = "maze.dat";
const char *algfile = "tremaux.so";

int main(int argc, char *argv[])
{
    /* parse command line args */
    for (int i = 1; i+1 < argc; i+=2) {
	if (strcmp(argv[i], "-m") == 0)
	    mazefile = argv[i+1];

	else if (strcmp(argv[i], "-a") == 0)
	    algfile = argv[i+1];
    }

    /* initialize program */
    if (algfile && !load_algorithm(algfile, &algorithm)) {
	fprintf(stderr, "error loading algorithm\n");
	return 1;
    }

    if (!parse_maze(mazefile, &maze)) {
	fprintf(stderr, "error reading maze file\n");
	return 1;
    }

    view = create_view();

    controller = create_controller(
	&view, &maze, &mouse, &algorithm);

    /* run program */
    while(!controller.quit) {
	do_command( &controller, getchar() );
    }

    /* cleanup */
    view.destroy();

    return 0;
}

