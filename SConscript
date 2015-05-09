# vim: set filetype=python
import os

env = Environment();

env.Append( LINKFLAGS=["-m32", "-rdynamic"] );
env.Append( CPPPATH=["include"] );
env.Append( LIBPATH="lib" );

env['SHLIBPREFIX'] = '';

env.Append( CCFLAGS=
   ["-Wall", "-Werror", "-pedantic", "-Wextra", "-m32", "-std=c99"] );

objs = [env.Object(f) for f in Glob("src/*.c")];

bin = env.Program(
	"../mazerunner", 
	objs + ["../lib/display.o"], 
	LIBS=['dl', 'curses']);

algs = []
for name in os.listdir('../algorithm_src'):
    if (name[-2:] == ".c"):
	so_name = '../' + name[:-2] + '.so'
	src_path = '../algorithm_src/' + name

        algs += [ env.SharedLibrary(so_name, src_path) ];

env.Default([bin] + algs);
