#ifndef DIRECTION_H
#define DIRECTION_H

typedef enum { North = 0, East=1, South=2, West=3 } Direction;

static inline 
Direction rotate_cw( Direction dir ) {
    return (Direction)((dir+1u) % 4u);
}

static inline 
Direction rotate_ccw( Direction dir ) {
    return (Direction)((dir+3u) % 4u);
}

static inline 
Direction rotate_opp( Direction dir ) {
    return (Direction)((dir+2u) % 4u);
}

static inline
void offset( int *x, int *y, Direction dir ) {
    if(dir == North) (*y)++;
    else if(dir == South) (*y)--;
    else if(dir == East) (*x)++;
    else (*x)--;
}

#endif
