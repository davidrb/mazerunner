#include "algorithm.h"

#include <dlfcn.h>

#include <stdio.h>

static void def_reset() {}

#pragma GCC diagnostic ignored "-Wunused-parameter"
static Direction def_move( Maze *maze, Mouse *mouse ) {
    return North;
}

typedef Direction (*MoveFunc)(Maze *, Mouse *);
typedef void (*ResetFunc)();

bool load_algorithm( const char *path, Algorithm *alg ) {
    void (*init)();
    void (*reset)();
    Direction (*move)(Maze *, Mouse *);

    void *handle = dlopen(path, RTLD_LAZY);
    *(void **) (&init) = dlsym(handle, "init");
    *(void **) (&reset) = dlsym(handle, "reset");
    *(void **) (&move) = dlsym(handle, "move");
    init();

    alg->move = move;
    alg->reset = reset;

    getchar();

    return true;
}

Algorithm default_algorithm() {
    Algorithm def_alg = {
	def_reset, def_move,
    };
    return def_alg;
}
