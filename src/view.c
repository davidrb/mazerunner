#include "view.h"

#include <assert.h>
#include <stdlib.h>

#include "display.h"

int dirs[4] = { 
    [North] = NORTH, [South] = SOUTH, [East] = EAST, [West] = WEST 
};

void update_mouse(Mouse *mouse) {
    if ( did_crash(mouse) )
	show_mouse(
	       CRASH,
	       getY(mouse), getX(mouse));
    else
	show_mouse(
	       dirs[ getDir(mouse) ],
	       getY(mouse), getX(mouse));

   show_position( getY(mouse), getX(mouse) ); 
   show_cells( get_cells(mouse) );
   show_unique_cells( get_unique_cells(mouse) );
}

void update_lvl0(Maze *maze, Mouse *mouse) {
    for (int x = 0; x < Cols; x++) {
	for(int y = 0; y < Rows; y++) {
	    put_walls( y, x, 
		get_wall(maze, x, y, North),
		get_wall(maze, x, y, East),
		get_wall(maze, x, y, West),
		get_wall(maze, x, y, South));
	}
    }

    update_mouse(mouse);
}

void update_lvl5(Maze *maze, Mouse *mouse) {
    int x = getX(mouse), 
	y = getY(mouse);

    put_walls( y, x,
	get_wall(maze, x, y, North),
	get_wall(maze, x, y, East),
	get_wall(maze, x, y, West),
	get_wall(maze, x, y, South));

    update_mouse(mouse);
}

View create_view( int level ) {
    View view;

    init_display(2);

    show_mouse(0, 0, NORTH);

    view.update = &update_lvl5;

    view.destroy = &clear_screen;

    return view;
}

