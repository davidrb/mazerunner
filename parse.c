#include "parse.h"
#include "maze.h"

#include "maze_def.h"

#include <stdio.h>
#include <assert.h>

int readHWalls(bool *hwalls, FILE *file) {
    assert(file);

    for (int c = 0; c < Cols; c++) {

	if(fgetc(file) != '+')
	    return 1;
	
	char w = fgetc(file);

	if (w != fgetc(file) || w != fgetc(file))
	    return 1;
    
	if (w == ' ' || w == '-') {
	    hwalls[c] = (w == '-');
	} else {
	    return 1;
	}
    }

    if (fgetc(file) != '+') {
	return 1;
    }

    return 0;
}

int readVWalls(bool *vwalls, FILE *file) {
    assert(file);

    if (fgetc(file) != '|')
	return 1;

    vwalls[0] = true;

    for (int c = 1; c < Cols+1; c++) {
	if (fgetc(file) != ' ' || fgetc(file) != ' ' || fgetc(file) != ' ')
	    return 1;

	char w = fgetc(file);

	if (w == ' ' || w == '|') {
	    vwalls[c] = (w == '|');
	} else {
	    return 1;
	}

	if( c+1 == Cols+1 && w != '|' )
	    return 1;
    }

    return 0;
}

int parseFile(const char* path, Maze *maze) {
    FILE *file = fopen(path, "r");
    if (!file) return 1;

    for (int r = 0; r < Rows; r++) {
	if ( readHWalls(maze->hwalls[r], file) != 0 ||
	    fgetc(file) != '\n' ||
	     readVWalls(maze->vwalls[r], file) != 0 ||
	     fgetc(file) != '\n') 
	     goto fail;
    }

    if ( readHWalls(maze->hwalls[Rows], file) != 0 ) {
	goto fail;
    }
    
    for (int i = 0; i < Cols; i++) {
	if ( maze->hwalls[0][i] == false ||
	     maze->hwalls[Rows][i] == false )
	    goto fail;
    }

    fclose(file);
    return 0;
fail:
    fclose(file);
    return 1;
}

