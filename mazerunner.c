#include "display.h"

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool vwalls[MAXR][MAXC+1];
    bool hwalls[MAXR+1][MAXC];
} Maze;

int readHWalls(bool *hwalls, FILE *file) {
    for (int c = 0; c < MAXC; c++) {

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
    if (fgetc(file) != '|')
	return 1;

    vwalls[0] = true;

    for (int c = 1; c < MAXC+1; c++) {
	if (fgetc(file) != ' ' || fgetc(file) != ' ' || fgetc(file) != ' ')
	    return 1;

	char w = fgetc(file);

	if (w == ' ' || w == '|') {
	    vwalls[c] = (w == '|');
	} else {
	    return 1;
	}

	if( c+1 == MAXC+1 && w != '|' )
	    return 1;
    }

    return 0;
}

int loadMaze(const char* path, Maze* maze) {
    FILE *file = fopen(path, "r");

    for (int r = 0; r < MAXR; r++) {
	if ( readHWalls(maze->hwalls[r], file) != 0 ||
	    fgetc(file) != '\n' ||
	     readVWalls(maze->vwalls[r], file) != 0 ||
	     fgetc(file) != '\n') 
	     goto fail;
    }

    if ( fgetc(file) != '\n' ||
	 readHWalls(maze->hwalls[MAXR], file) != 0 ) {
	goto fail;
    }
    
    for (int i = 0; i < MAXC; i++) {
	if ( maze->hwalls[i] == false ||
	     maze->hwalls[MAXR] == false )
	    goto fail;
    }

    fclose(file);
    return 0;
fail:
    fclose(file);
    return 1;
}

void updateView( int x, int y, int dir ) {
    show_mouse(x, y, dir);
}

#include <string.h>
int main() {
    Maze maze;
    memset(&maze, 0, sizeof(maze));
    loadMaze("maze.dat", &maze); 
    
    int mouseX = 0, mouseY = 0,
	mouseDir = NORTH;

    init_display(0);

    for (int r = 0; r < MAXR; r++) {
	for (int c = 0; c < MAXC; c++) {
	    put_walls(r, c, maze.hwalls[MAXR-r-1][c], 
			    maze.vwalls[MAXR-r-1][c+1],
			    maze.vwalls[MAXR-r-1][c], 
			    maze.hwalls[MAXR-r][c]);
	}
    }

    updateView(mouseX, mouseY, mouseDir);

    getchar();

    clear_screen();

    return 0;
}
