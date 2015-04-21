#include "algorithm.h"

struct Algorithm {
    void (*update)(Algorithm *, Maze *, Mouse *);
};

void update(Algorithm *a, Maze *maze, Mouse *m) {
    a->update(a, maze, m);
}
