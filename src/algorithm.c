#include "algorithm.h"

#include <stdio.h>

Algorithm load_algorithm( const char *path ) {
    Algorithm alg;
    FILE *file = fopen(path, "r");
    if (file) fclose( file );  
    return alg;
}

static void reset() {}

#pragma GCC diagnostic ignored "-Wunused-parameter"
static Direction move( Maze *maze, Mouse *mouse ) {
    return North;
}

Algorithm default_algorithm() {
    Algorithm def_alg = {
	reset, move,
    };
    return def_alg;
}
