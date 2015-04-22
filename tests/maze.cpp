#include <gmock/gmock.h>

extern "C" {
#include "maze.h"
#include "parse.h"
}

using namespace testing;

bool check_boundaries(Maze *);

TEST( maze, create_maze ) {
    Maze maze = create_maze();
    ASSERT_TRUE( check_boundaries(&maze) );
}

TEST( maze, check_bad_maze ) {
    Maze maze = create_maze();
    ASSERT_FALSE( parse_maze("badmaze.dat", &maze) );
}

TEST( maze, parse_boundaries ) {
    Maze maze = create_maze();
    parse_maze("maze.dat", &maze);
    ASSERT_TRUE(check_boundaries(&maze));
}

bool check_boundaries(Maze* maze) {
    for (int x = 0; x < Cols-1; x++) {
	if (!get_wall( maze, x, 0, South ) || !get_wall(maze, x, Rows-1, North))
	    return false;
    }
    
    for (int y = 0; y < Rows-1; y++) {
	if (!get_wall( maze, 0, y, West ) || !get_wall(maze, Cols-1, y, East))
	    return false;
    }

    return true;
}
