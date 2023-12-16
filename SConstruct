##
# @author Alexander Breuer (alex.breuer AT uni-jena.de)
#
# @section DESCRIPTION
# Entry-point for builds.
##
import SCons
import os

print( '####################################' )
print( '### Tsunami Lab                  ###' )
print( '###                              ###' )
print( '### https://scalable.uni-jena.de ###' )
print( '####################################' )
print()
print('running build script')

# configuration
vars = Variables()

vars.AddVariables(
  EnumVariable( 'mode',
                'compile modes, option \'san\' enables address and undefined behavior sanitizers',
                'release',
                allowed_values=('release', 'debug', 'release+san', 'debug+san' )
              )
)

vars.AddVariables(
  EnumVariable( 'CXX',
                'compiler options: g++, icpc',
                'g++',
                allowed_values=('g++', 'icpc')
              )
)

# exit in the case of unknown variables
if vars.UnknownVariables():
  print( "build configuration corrupted, don't know what to do with: " + str(vars.UnknownVariables().keys()) )
  exit(1)

# create environment
env = Environment( ENV=os.environ, variables = vars )

print(f"use the {env['CXX']} compiler")

# check for netcdf
if not Configure(env).CheckLibWithHeader('netcdf', 'netcdf.h', 'c++'):
  print('netcdf was not found')
  Exit(1)

# generate help message
Help( vars.GenerateHelpText( env ) )

# add default flags
env.Append( CXXFLAGS = [ '-g',
                         '-std=c++11',
                         '-Wall',
                         '-Wextra',
                         '-Wpedantic',
                         '-Werror' ] )

# set optimization mode
if 'debug' in env['mode']:
  env.Append( CXXFLAGS = [ '-O0' ] )
else:
  if 'g++' in env['CXX']:
    env.Append( CXXFLAGS = [ '-O2' ] )
  elif 'icpc' in env['CXX']:
    env.Append( CXXFLAGS = [ '-fast' ] )

# add sanitizers
if 'san' in  env['mode']:
  env.Append( CXXFLAGS =  [ '-fsanitize=float-divide-by-zero',
                            '-fsanitize=bounds',
                            '-fsanitize=address',
                            '-fsanitize=undefined',
                            '-fno-omit-frame-pointer' ] )
  env.Append( LINKFLAGS = [ '-fsanitize=address',
                            '-fsanitize=undefined' ] )

# add Catch2
env.Append( CXXFLAGS = [ '-isystem', 'submodules/Catch2/single_include' ] )

# add nlohmann/json
env.Append( CXXFLAGS = [ '-isystem', 'submodules/json/single_include' ] )

# get source files
VariantDir( variant_dir = 'build/src',
            src_dir     = 'src' )

env.sources = []
env.tests = []

Export('env')
SConscript( 'build/src/SConscript' )
Import('env')

env.Program( target = 'build/tsunami_lab',
             source = env.sources + env.standalone )

env.Program( target = 'build/tests',
             source = env.sources + env.tests )