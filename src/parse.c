#include "parse.h"

#include <mazerunner/maze.h>

#include <stdio.h>
#include <assert.h>
#include <setjmp.h>

void doAll( HWalls, VWalls, FILE*, jmp_buf);
void doTopOrBottom( HLine, FILE*, jmp_buf );
void doMiddle( HWalls, VWalls, FILE*, jmp_buf );

void readHWalls( HLine, FILE *, jmp_buf );
void readVWalls( VLine, FILE *, jmp_buf );

bool readHWall( FILE *, jmp_buf );
bool readVWall( FILE *, jmp_buf );

void expectNewLine( FILE *, jmp_buf );
void expectPost( FILE *, jmp_buf );
void expectVWall( FILE *, jmp_buf );
void expectHWall( FILE *, jmp_buf );
void expectThreeSpaces( FILE *, jmp_buf );

bool parse_maze(const char* path, Maze *maze) {
    FILE *file = fopen(path, "r");
    jmp_buf buf;

    if ( file && setjmp(buf) == 0 ) {
	doAll( maze->hwalls, maze->vwalls, file, buf );
    } else {
	fclose(file);
	return false;
    }

    fclose(file);
    return true;
}

void doAll( HWalls hwalls, VWalls vwalls, FILE *file, jmp_buf buf ) {
    doTopOrBottom( hwalls[0], file, buf);
    doMiddle( hwalls, vwalls, file, buf);
    doTopOrBottom( hwalls[Rows], file, buf);
}

void doMiddle(HWalls hwalls, VWalls vwalls, FILE *file, jmp_buf buf) {
    readVWalls(vwalls[0], file, buf);

    for (int r = 1; r < Rows; r++) {
	readHWalls(hwalls[r], file, buf);
	readVWalls(vwalls[r], file, buf);
    }
}

void doTopOrBottom(bool *hwalls, FILE *file, jmp_buf buf) {
    for (int i = 0; i < Cols; i++) {
	expectPost(file, buf);
	expectHWall(file, buf);

	hwalls[i] = true;
    }

    expectPost(file, buf);
    expectNewLine(file, buf);
}

void readHWalls(bool *hwalls, FILE *file, jmp_buf buf) {
    assert(file);

    for (int c = 0; c < Cols; c++) {
	expectPost(file, buf);
	hwalls[c] = readHWall(file, buf);
    }

    expectPost(file, buf);
    expectNewLine(file, buf);
}

void readVWalls(bool *vwalls, FILE *file, jmp_buf buf) {
    assert(file);

    expectVWall(file, buf);
    vwalls[0] = true;

    for (int c = 1; c < Cols; c++) {
	expectThreeSpaces(file, buf);
	vwalls[c] = readVWall(file, buf);
    }

    expectThreeSpaces(file, buf);
    expectVWall(file, buf);
    vwalls[Cols] = true;

    expectNewLine(file, buf);
}

bool readHWall(FILE *file, jmp_buf buf) {
    char w = fgetc(file);

    if (w != fgetc(file) || w != fgetc(file) || (w != ' ' && w != '-'))
	longjmp(buf, 1);

    return (w == '-');
}

bool readVWall(FILE *file, jmp_buf buf) {
    char w = fgetc(file);

    if (w != ' ' && w != '|') 
	longjmp(buf, 1);

    return w == '|';
}

void expectPost(FILE *file, jmp_buf buf) {
    if(fgetc(file) != '+')
	longjmp(buf, 1);
}

void expectHWall(FILE *file, jmp_buf buf) {
    if (!readHWall(file, buf))
	longjmp(buf, 1);
}

void expectVWall(FILE *file, jmp_buf buf) {
    if (fgetc(file) != '|')
	longjmp(buf, 1);
}

void expectThreeSpaces(FILE* file, jmp_buf buf) {
    if (fgetc(file) != ' ' || fgetc(file) != ' ' || fgetc(file) != ' ')
	longjmp(buf, 1);
}

void expectNewLine(FILE *file, jmp_buf buf) {
    if(fgetc(file) != '\n') 
	longjmp(buf, 1);
}
