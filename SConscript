# vim: set filetype=python

Import("env tests_env")

main_file = env.File("src/mazerunner.c");
main_obj = env.Object("src/mazerunner.c");

objs = [env.Object(f) for f in Glob("src/*.c") if f != main_file];
test_objs = [tests_env.Object(f) for f in Glob("tests/*.cpp")];

bin = env.Program(
	"../mazerunner", 
	objs + main_obj + ["../lib/display.o"], 
	LIBS='curses');

tests = env.Program( 
	"run_tests", 
	test_objs + objs,
	LIBS='curses');
