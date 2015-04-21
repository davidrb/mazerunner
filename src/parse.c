#include "parse.h"
#include "maze.h"

#include <stdio.h>
#include <assert.h>

int readHWalls(bool *hwalls, FILE *file) {
    assert(file);

    for (int c = 0; c < Cols; c++) {
	if(fgetc(file) != '+')
	    return 1;
	
	char w = fgetc(file);

	if (w != fgetc(file) || w != fgetc(file) || (w != ' ' && w != '-'))
	    return 1;
    
	hwalls[c] = (w == '-');
    }

    return fgetc(file) != '+';
}

int readVWalls(bool *vwalls, FILE *file) {
    assert(file);

    if (fgetc(file) != '|')
	return 1;

    vwalls[0] = true;

    for (int c = 1; c < Cols; c++) {
	if (fgetc(file) != ' ' || fgetc(file) != ' ' || fgetc(file) != ' ')
	    return 1;

	char w = fgetc(file);

	if (w != ' ' && w != '|') return 1;

	vwalls[c] = (w == '|');
    }

    vwalls[Cols] = true;

    return (fgetc(file) == '|');
}

int parse_maze(const char* path, Maze *maze) {
    FILE *file = fopen(path, "r");
    if (!file) return 1;

    for (int r = 0; r < Rows; r++) {
	if ( readHWalls(maze->hwalls[r], file) != 0 || fgetc(file) != '\n' ||
	     readVWalls(maze->vwalls[r], file) != 0 || fgetc(file) != '\n') 

	    fclose(file);
	    return 1;
    }

    if ( readHWalls(maze->hwalls[Rows], file) != 0 ) {
	fclose(file);
	return 1;
    }
    
    for (int i = 0; i < Cols; i++) {
	if ( !maze->hwalls[0][i] || !maze->hwalls[Rows][i] ) {
	    fclose(file);
	    return 1;
	}
    }

    fclose(file);
    return 0;
}

