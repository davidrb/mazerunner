# vim: set filetype=python

env = Environment()

env.Append( LINKFLAGS=["-g", "-m32", "-rdynamic"] );
env.Append( CPPPATH=["include"] );
env.Append( LIBPATH="lib" );

c_env = env.Clone();
c_env.Append( CCFLAGS=["-Wextra", "-g", "-m32", "-std=c99"] );
c_env.Append( CCFLAGS=["-Wall", "-Werror", "-pedantic"] );

alg_env = c_env
alg_env['SHLIBPREFIX'] = '';
Export("env c_env alg_env");

SConscript('SConscript', variant_dir='.build', duplicate=0);
