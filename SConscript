# vim: set filetype=python

Import("cpp_env c_env")

main_file = c_env.File("src/mazerunner.c");
main_obj = c_env.Object("src/mazerunner.c");

objs = [c_env.Object(f) for f in Glob("src/*.c") if f != main_file];

bin = c_env.Program(
	"../mazerunner", 
	objs + main_obj + ["../lib/display.o"], 
	LIBS='curses');

test_objs = [cpp_env.Object(f) for f in Glob("tests/*.cpp")];

tests = cpp_env.Program( 
	"tests/tests", 
	test_objs + objs + ["../lib/display.o"],
	LIBS='curses');

run_tests = Command( target="run_tests",
		     source=tests,
		     action=".build/tests/tests");

AlwaysBuild(run_tests);
Default(run_tests);

