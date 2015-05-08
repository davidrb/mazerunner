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
	       mouse->y, mouse->x);
    else
	show_mouse(
	       dirs[ getDir(mouse) ],
	       mouse->y, mouse->x);

   show_position( mouse->x, mouse->y ); 
   show_cells( get_cells(mouse) );
   show_unique_cells( get_unique_cells(mouse) );
}

void clear_maze() {
     for (int x = 0; x < Cols; x++) {
	for(int y = 0; y < Rows; y++) {
	    put_walls( y, x, 0, 0, 0, 0 );
	}
    }
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
    int x = mouse->x,
	y = mouse->y;

    put_walls( y, x,
	get_wall(maze, x, y, North),
	get_wall(maze, x, y, East),
	get_wall(maze, x, y, West),
	get_wall(maze, x, y, South));

    mouse_cam(
	get_wall(maze, x, y, rotate_ccw(mouse->dir)),
	get_wall(maze, x, y, mouse->dir),
	get_wall(maze, x, y, rotate_cw(mouse->dir)));

    update_mouse(mouse);
}

void view_write_error(char *s) {
    write_message(s, 0);
}

View create_view( int level ) {
    View view;

    init_display(level);

    if (level == 5)
	view.update = update_lvl5;
    else
	view.update = update_lvl0;

    view.write_message = view_write_error;
    view.destroy = clear_screen;
    view.clear_maze = clear_maze;

    return view;
}

