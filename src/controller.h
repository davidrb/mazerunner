#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mazerunner/mouse.h>
#include <mazerunner/maze.h>

#include "algorithm.h"
#include "view.h"

struct Controller {
    Maze* maze;
    Mouse* mouse;
    View* view;
    Algorithm *algorithm;
};

bool do_command(struct Controller *, char);
typedef struct Controller Controller;

Controller create_controller(View *, Maze *, Mouse *, Algorithm *);

#endif
