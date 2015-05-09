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

void *get_handle( const char *path ) {
    /* have to add a ./ so dlopen searches in working dir */
    char *fullpath = malloc( strlen(path) + 3 );
    fullpath[0] = '.'; fullpath[1] = '/';
    strcpy(fullpath + 2, path);

    void *handle = dlopen(fullpath, RTLD_LAZY | RTLD_GLOBAL);
    free(fullpath);
    return handle;
}

bool load_algorithm( const char *path, Algorithm *alg ) {
    void *handle = NULL;
    if (!(handle = get_handle(path))) {
	fprintf(stderr, "couldn't open algorithm.\n");
	return false;
    }

    *(void **) (&alg->reset) = dlsym(handle, "reset");
    *(void **) (&alg->move) = dlsym(handle, "move");

    if (!alg->reset || !alg->move) {
	fprintf(stderr, "algorithm is missing a function.\n" );
	return false;
    }

    return true;
}

Algorithm default_algorithm() {
    Algorithm def_alg = {
	.reset = def_reset,
	.move = def_move,
    };
    return def_alg;
}
