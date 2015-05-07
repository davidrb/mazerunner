# vim: set filetype=python

env = Environment()

env.Append( LINKFLAGS=["-g", "-m32", "-rdynamic"] );
env.Append( CPPPATH=["include"] );
env.Append( LIBPATH="lib" );

c_env = env.Clone();
c_env.Append( CCFLAGS=["-Wextra", "-g", "-m32", "-std=c99"] );
c_env.Append( CCFLAGS=["-Wall", "-Werror", "-pedantic"] );

cpp_env = env.Clone();
cpp_env.Append( CPPFLAGS=["-g", "-m32", "-std=c++1y"]);
cpp_env.Append( CPPFLAGS=["-Wall", "-Werror", "-pedantic"] );
cpp_env.Append( LIBS=["gmock"] );
cpp_env.Append( CPPPATH=["src"] );

Export("env cpp_env c_env");

SConscript('SConscript', variant_dir='.build', duplicate=0);
