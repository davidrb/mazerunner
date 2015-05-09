#Mazerunner

##Command Line Arguments
- **-m** loads a specified maze file.  Default is "maze.dat"
- **-a** loads an algoithm.  Default is "tremaux.so"

##Controls
- **w** Move forward
- **a** Turn left
- **d** Turn right
- **R** Reset mouse 
- **r** Hug right wall
- **l** Hug left wall
- **g** Toggle ghost mode
- **i** Toggle invincibility
- **space** Step algorithm

##Custom Algorithms
To create a custom algorithm, compile a 
shared library with a `void reset()`,
and a `Move move(Maze *, Mouse *)` function.
See examples in algorithm_src.
