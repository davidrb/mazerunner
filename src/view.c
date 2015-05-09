#include "view.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"

int dirs[4] = { 
    [North] = NORTH, [South] = SOUTH, [East] = EAST, [West] = WEST 
};

static void update_mouse(Mouse *mouse) {
    int x = mouse->x, y = mouse->y;

    if ( mouse->crashed ) {
	show_mouse(CRASH, y, x);
	write_message("You Crashed! Would you like to continue (y/n)?", 0);
    } else {
	if (mouse->won)
	    write_message( "You Won!", 0 );
	show_mouse(dirs[ mouse->dir ], y, x);
    }

   show_position( mouse->x, mouse->y ); 
   show_cells( mouse->cells );
   show_unique_cells( mouse->unique_cells );
}

static void clear() {
    for (int x = 0; x < Cols; x++)
	for(int y = 0; y < Rows; y++)
	    put_walls( y, x, 0, 0, 0, 0 );

    clear_screen();
    init_display(5);
}

static void update(Maze *maze, Mouse *mouse) {
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
    write_message(s, 1);
}

View create_view() {
    View view;

    init_display(5);

    view.update = update;
    view.write_message = view_write_error;
    view.destroy = clear_screen;
    view.clear = clear;

    return view;
}

