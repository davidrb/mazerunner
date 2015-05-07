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
    void *handle = dlopen(path, RTLD_LAZY | RTLD_GLOBAL);

    if (!handle)
	return false;

    *(void **) (&alg->init) = dlsym(handle, "init");
    *(void **) (&alg->reset) = dlsym(handle, "reset");
    *(void **) (&alg->cleanup) = dlsym(handle, "cleanup");
    *(void **) (&alg->move) = dlsym(handle, "move");

    if (!alg->cleanup || !alg->init || !alg->reset || !alg->move) {
	fprintf(stderr, "algorithm is missing a required function.\n" );
	return false;
    }

    return true;
}

Algorithm default_algorithm() {
    Algorithm def_alg = {
	.reset = def_reset,
	.init = def_reset,
	.cleanup = def_reset,
	.move = def_move,
    };
    return def_alg;
}
