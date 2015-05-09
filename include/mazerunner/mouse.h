#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

#include "maze.h"

typedef struct Mouse Mouse;

Mouse create_mouse();

typedef enum { Forward, Right, Left, NoMove } Move;
void move_mouse(Mouse *, Maze *, Move);

void go_forward(Mouse *, Maze *);
void turn_left(Mouse *);
void turn_right(Mouse *);

bool is_clear(Mouse *, Maze *, Move);

Direction getDir(Mouse *);

bool visited(Mouse *, int x, int y);

int get_cells( Mouse * );
int get_unique_cells( Mouse * );

bool did_crash(Mouse *);

struct Mouse {
    int x, y;
    Direction dir;
    bool crashed;
    bool invincible, ghost;
    bool visited[Rows][Cols];
    int cells, unique_cells;
    bool won;
};

#endif
