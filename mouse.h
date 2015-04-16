#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

#include "maze.h"

typedef struct {
    int x, y;
    Direction dir;
    bool crashed;
    bool visited[Rows][Cols];
    int cells, unique_cells;
} Mouse;

Mouse create_mouse();

int getX(Mouse *);
int getY(Mouse *);

Direction getDir(Mouse *);

void move_mouse(Mouse *, Maze *);

void turn_left(Mouse *);
void turn_right(Mouse *);

bool visited(Mouse *, int x, int y);

int get_cells( Mouse * );
int get_unique_cells( Mouse * );

bool did_crash(Mouse *);

#endif
