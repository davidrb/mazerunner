#include "display.h"

#include <stdio.h>
#include <stdbool.h>

#include "parse.h"
#include "maze.h"

void updateView( int x, int y, int dir ) {
    show_mouse(x, y, dir);
}

#include <string.h>
#include <assert.h>

int main() {
    Maze *maze = new_maze("maze.dat");
    assert(maze);

    int mouseX = 0, mouseY = 0,
	mouseDir = NORTH;

    init_display(5);

    for (int r = 0; r < MAXR; r++) {
	for (int c = 0; c < MAXC; c++) {
	    put_walls(r, c, 
		    get_wall(maze, c, r, North),
		    get_wall(maze, c, r, East),
		    get_wall(maze, c, r, West),
		    get_wall(maze, c, r, South));
	    }
    }

    updateView(mouseX, mouseY, mouseDir);

    getchar();

    clear_screen();
    
    if (maze)
    delete_maze(maze);

    return 0;
}
