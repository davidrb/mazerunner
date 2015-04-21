# vim: set filetype=python

import os

env = Environment()
env.Append( LINKFLAGS="-m32" );
env.Append( CPPPATH=["include"] );

env['ENV']['TERM'] = os.environ['TERM']

c_env = env.Clone();
c_env.Append( CCFLAGS=["-m32", "-std=c99", "-Wall", "-Werror", "-pedantic"] );

cpp_env = env.Clone();
cpp_env.Append( CPPFLAGS=["-m32", "-std=c++1y", "-Wall", "-Werror", "-pedantic"] );
cpp_env.Append( LIBS=["gmock"] );

Export("cpp_env c_env");

SConscript('SConscript', variant_dir='.build', duplicate=0);
