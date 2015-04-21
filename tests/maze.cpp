#include <gmock/gmock.h>

extern "C" {
#include "maze.h"
}

using namespace testing;

TEST( maze, create_maze ) {
    Maze maze = create_maze();

    ASSERT_TRUE( get_wall(&maze, 0, 0, South) );
    ASSERT_TRUE( get_wall(&maze, Cols-1, 0, South) );

    ASSERT_TRUE( get_wall(&maze, 0, 0, West) );
    ASSERT_TRUE( get_wall(&maze, 0, Rows-1, West) );

    ASSERT_TRUE( get_wall(&maze, 0, Rows-1, North) );
    ASSERT_TRUE( get_wall(&maze, Cols-1, Rows-1, North) );

    ASSERT_TRUE( get_wall(&maze, Cols-1, 0, East) );
    ASSERT_TRUE( get_wall(&maze, Cols-1, Rows-1, East) );
}
