#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

#include "maze.h"

typedef struct Mouse Mouse;
typedef enum { Forward, Right, Left, NoMove } Move;

Mouse create_mouse();

void move_mouse(Mouse *, Maze *, Move);
void go_forward(Mouse *, Maze *);

bool is_clear(Mouse *, Maze *, Move);
bool visited(Mouse *, int x, int y);

struct Mouse {
    int x, y;
    Direction dir;
    bool crashed;
    bool invincible, ghost;
    bool visited[Rows][Cols];
    int cells, unique_cells;
    bool won, cheater;
};

#endif
