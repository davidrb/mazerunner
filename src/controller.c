#include "controller.h"

typedef void (*Command)(Controller *, char);

bool do_command(Controller* this, char c) {
    if (c == 'w' || c == 'a' || c == 'd') {
	this->algorithm->reset();

	if (c == 'w')
	    move_mouse(this->mouse, this->maze, Forward);
	else if (c == 'a')
	    turn_left(this->mouse);
	else
	    turn_right(this->mouse);
    } else if (c == 'R') {
	*this->mouse = create_mouse();
	(*this->view).destroy();
	*this->view = create_view(5);
	this->algorithm->reset();
    } else if (c == 'r') {
	int x = this->mouse->x;
	int y = this->mouse->y;
	int dir = this->mouse->dir;

	if ( (get_wall(this->maze, x, y, rotate_cw(dir)) ||
	     get_wall(this->maze, x, y, rotate_ccw(dir))) &&
	     !get_wall(this->maze, x, y, dir) ) {
	    move_mouse(this->mouse, this->maze, Forward);
	} else {
	    turn_right(this->mouse);
	}
    } else if (c == 'i') {
	set_invincible(this->mouse, !this->mouse->invincible);
	this->view->write_message(
	    this->mouse->invincible ? "set invincible" : "unset invincible");
    } else if (c == 'g') {
	set_ghost(this->mouse, !this->mouse->ghost);
	this->view->write_message(
	    this->mouse->ghost ? "set ghost" : "unset ghost");
    } else if (c == 'm') {
	reveal_maze(this->maze);
    } else if (c == 'n') {
	(*this->view).destroy();
	(*this->view) = create_view(5);
	unreveal_maze(this->maze, this->mouse);
    } else if (c == ' ') {
	Move move = this->algorithm->move( this->maze, this->mouse );
	move_mouse( this->mouse, this->maze,  move );
    } else if (c == 'q' || c == 4) {
	return false;
    }

    this->view->update(this->maze, this->mouse);
    return true;
}

Controller create_controller(View *view, Maze* maze, 
	Mouse* mouse, Algorithm *algorithm) 
{
    Controller controller = {
	.view = view,
	.maze = maze,
	.mouse = mouse,
	.algorithm = algorithm,
    };

    view->update(maze, mouse);

    return controller;
}
