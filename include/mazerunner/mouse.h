#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

#include "maze.h"

typedef struct Mouse Mouse;

Mouse create_mouse();

void move_mouse(Mouse *, Maze *);

void turn_left(Mouse *);
void turn_right(Mouse *);

void set_invincible(Mouse *, bool);
void set_ghost(Mouse *, bool);

Direction getDir(Mouse *);

int getX(Mouse *);
int getY(Mouse *);

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
};

#endif