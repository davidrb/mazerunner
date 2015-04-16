# vim: set filetype=python

env = Environment();

env.Append(CCFLAGS=['-g', '-std=c99', '-m32', '-Wall', '-Werror', '-Wextra']);
env.Append(LINKFLAGS=['-m32']);

bin = env.Program("../mazerunner", Glob("*.c") + ["display.o"], LIBS='curses');
