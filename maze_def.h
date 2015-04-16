#ifndef MAZE_DEF_H
#define MAZE_DEF_H

#include "display.h"

struct Maze {
    bool vwalls[MAXR][MAXC+1];
    bool hwalls[MAXR+1][MAXC];
};


#endif
