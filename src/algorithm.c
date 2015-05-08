#include "algorithm.h"

#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void def_reset() {}

#pragma GCC diagnostic ignored "-Wunused-parameter"
static Move def_move( Maze *maze, Mouse *mouse ) {
    return Forward;
}

typedef Direction (*MoveFunc)(Maze *, Mouse *);
typedef void (*ResetFunc)();

bool load_algorithm( const char *path, Algorithm *alg ) {
    char *fullpath = malloc( strlen(path) + 3 );
    fullpath[0] = '.'; fullpath[1] = '/';
    strcpy(fullpath + 2, path);

    void *handle = dlopen(fullpath, RTLD_LAZY | RTLD_GLOBAL);
    free(fullpath);

    if (!handle) {
	fprintf(stderr, "couldn't open algorithm.\n");
	return false;
    }

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
