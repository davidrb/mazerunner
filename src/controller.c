#include "controller.h"

bool do_command(Controller* this, char c) {
    if (c == 'w')
	move_mouse(this->mouse, this->maze);
    else if (c == 'a')
	turn_left(this->mouse);
    else if (c == 'd')
	turn_right(this->mouse);
    else if (c == 'r') {
	*this->mouse = create_mouse();
	(*this->view).destroy();
	*this->view = create_view(5);
    } else if (c == 'i') {
	set_invincible(this->mouse, !this->mouse->invincible);
	this->view->write_message(
	    this->mouse->invincible ? "set invincible" : "unset invincible");
    } else if (c == 'g') {
	set_ghost(this->mouse, !this->mouse->ghost);
	this->view->write_message(
	    this->mouse->ghost ? "set ghost" : "unset ghost");
    } else if (c == 'q' || c == 4) {
	return false;
    }

    this->view->update(this->maze, this->mouse);
    return true;
}

Controller create_controller(View *view, Maze* maze, Mouse* mouse) {
    Controller controller = {
	.view = view,
	.maze = maze,
	.mouse = mouse,
    };

    view->update(maze, mouse);

    return controller;
}