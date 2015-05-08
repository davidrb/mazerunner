# vim: set filetype=python

Import("env c_env alg_env")

objs = [c_env.Object(f) for f in Glob("src/*.c")];

bin = c_env.Program(
	"../mazerunner", 
	objs + ["../lib/display.o"], 
	LIBS=['dl', 'curses']);

test_alg = alg_env.SharedLibrary( '../test.so', 'algorithm_src/test.c');

env.Default([ bin, test_alg]);
