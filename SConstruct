# vim: set filetype=python

env = Environment()

env.Append( CCFLAGS=["-m32", "-std=c99", "-Wall", "-Werror", "-pedantic"] );
env.Append( CPPPATH=["include"] );
env.Append( LINKFLAGS="-m32" );

Export('env')

tests_env = Environment();
tests_env.Append( CPPFLAGS=["-m32", "-std=c++14", "-Wall", "-Werror", "-pedantic"] );

Export("tests_env");

SConscript('SConscript', variant_dir='.build', duplicate=0);
