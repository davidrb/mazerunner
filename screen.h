#ifndef SCREEN_H
#define SCREEN_H

#include "maze.h"

struct Screen;
typedef struct Screen Screen;

Screen init_screen(int level);
void destroy_screen(Screen *);

#endif
