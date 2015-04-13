#include "screen.h"
#include "display.h"

struct Screen {
    void (*init)(Maze *);
    void (*mouse_moved)(Position);
    void (*clear)(void);
};

GUI init_screen(int level) {
    init_display(level);
}

void destroy_screen(GUI *gui) {
}
