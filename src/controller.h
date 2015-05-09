#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mazerunner/mouse.h>
#include <mazerunner/maze.h>

#include "algorithm.h"
#include "view.h"

typedef struct Controller Controller;
bool do_command(Controller *, char);

Controller create_controller(View *, Maze *, Mouse *, Algorithm *);

struct Controller {
    Maze* maze;
    Mouse* mouse;
    View* view;
    Algorithm *algorithm;

    bool quit;
};

#endif
