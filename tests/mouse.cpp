#include <gmock/gmock.h>

extern "C" { 
#include <mazerunner/mouse.h>
}

using namespace testing;

TEST(mouse, move_mouse) {
    Mouse mouse = create_mouse();
    Maze maze = create_maze();

    turn_right( &mouse );
    move_mouse( &mouse, &maze );

    ASSERT_THAT( getX(&mouse), Eq(1) );
}
