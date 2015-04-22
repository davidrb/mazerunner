#include "parse.h"
#include "maze.h"

#include <stdio.h>
#include <assert.h>
#include <setjmp.h>

void readHWalls(bool *, FILE *, jmp_buf);
void readVWalls(bool *, FILE *, jmp_buf);

bool readHWall(FILE *file, jmp_buf buf);
bool readVWall(FILE *, jmp_buf);

void doTopOrBottom(bool *hwalls, FILE *, jmp_buf buf);
void doMiddle(bool hwalls[Rows+1][Cols], 
	      bool vwalls[Rows][Cols+1], 
	      FILE *file, jmp_buf buf);

void expectNewLine(FILE *, jmp_buf);
void expectPost(FILE *file, jmp_buf buf);
void expectVWall(FILE *file, jmp_buf buf);
void expectThreeSpaces(FILE*, jmp_buf);

bool parse_maze(const char* path, Maze *maze) {
    jmp_buf buf;
    FILE *file = fopen(path, "r");

    if ( file && !setjmp(buf) ) {

	doTopOrBottom( maze->hwalls[0], file, buf);



	doTopOrBottom( maze->hwalls[0], file, buf);

	fclose(file);
	return true;
    } else {
	fclose(file);
	return false;
    }
}


void doMiddle(bool hwalls[Rows+1][Cols], 
	      bool vwalls[Rows][Cols+1], 
	      FILE *file, jmp_buf buf) 
{
    for (int r = 1; r < Rows; r++) {
	readHWalls(hwalls[r], file, buf);
	expectNewLine(file, buf);

	readVWalls(vwalls[r], file, buf);
	expectNewLine(file, buf);
    }
}

void doTopOrBottom(bool *hwalls, FILE *file, jmp_buf buf) {
    for (int i = 0; i < Cols; i++) {
	if ( !readHWall(file, buf) )
	    longjmp(buf, 1);
	hwalls[i] = true;
    }
}

void readHWalls(bool *hwalls, FILE *file, jmp_buf buf) {
    assert(file);

    for (int c = 0; c < Cols; c++) {
	expectPost(file, buf);
	hwalls[c] = readHWall(file, buf);
    }

    expectPost(file, buf);
}

void readVWalls(bool *vwalls, FILE *file, jmp_buf buf) {
    assert(file);

    expectVWall(file, buf);
    vwalls[0] = true;

    for (int c = 1; c < Cols; c++) {
	expectThreeSpaces(file, buf);
	vwalls[c] = readVWall(file, buf);
    }

    expectVWall(file, buf);
    vwalls[Cols] = true;
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
