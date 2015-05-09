#include "controller.h"

bool do_command(Controller* this, char c) {
    Mouse *mouse = this->mouse;
    Maze *maze = this->maze;
    View *view = this->view;
    Algorithm *algorithm = this->algorithm;

    // movement
    if (c == 'w' || c == 'a' || c == 'd') {
	algorithm->reset();

	if (c == 'w')
	    move_mouse(mouse, maze, Forward);
	else if (c == 'a')
	    move_mouse(mouse, maze, Left);
	else if (c == 'd')
	    move_mouse(mouse, maze, Right);
    } 
    // reset
    else if (c == 'R') {
	*mouse = create_mouse();
	algorithm->reset();
	view->clear();
    } 
    // right wall hug
    else if (c == 'r') {
	algorithm->reset();
	if (is_clear(mouse, maze, Right)) {
	    move_mouse(mouse, maze, Right);
	    move_mouse(mouse, maze, Forward);
	} 
	else if (is_clear(mouse, maze, Forward)) {
	    move_mouse(mouse, maze, Forward);
	} 
	else if (is_clear(mouse, maze, Left)) {
	    move_mouse(mouse, maze, Left);
	    move_mouse(mouse, maze, Forward);
	} else {
	    move_mouse(mouse, maze, Right);
	    move_mouse(mouse, maze, Right);
	    move_mouse(mouse, maze, Forward);
	}

    } 
    // left wall hug
    else if (c == 'l') {
	algorithm->reset();
	if (is_clear(mouse, maze, Left)) {
	    move_mouse(mouse, maze, Left);
	    move_mouse(mouse, maze, Forward);
	} 
	else if (is_clear(mouse, maze, Forward)) {
	    move_mouse(mouse, maze, Forward);
	} 
	else if (is_clear(mouse, maze, Right)) {
	    move_mouse(mouse, maze, Right);
	    move_mouse(mouse, maze, Forward);
	} else {
	    move_mouse(mouse, maze, Left);
	    move_mouse(mouse, maze, Left);
	    move_mouse(mouse, maze, Forward);
	}

    } 
    // invincibility
    else if (c == 'i') {
	mouse->invincible = !mouse->invincible;
	view->write_message(
	    mouse->invincible ? "set invincible" : "unset invincible");
    } 
    // ghost mode
    else if (c == 'g') {
	mouse->ghost = !mouse->ghost;
	view->write_message(
	    mouse->ghost ? "set ghost" : "unset ghost");
    } 
    // cheat
    else if (c == 'm') {
	reveal_maze(maze);
	view->write_message( "You Cheated" );
    } 
    // uncheat
    else if (c == 'n') {
	view->clear();
	unreveal_maze(maze, mouse);
	view->write_message( "You Still Cheated" );
    } 
    // mouse's choice
    else if (c == ' ') {
	Move move = algorithm->move( maze, mouse );
	move_mouse( mouse, maze,  move );
    } 
    // quit
    else if (c == 'q' || c == 4) {
	return false;
    }

    view->update(maze, mouse);
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
