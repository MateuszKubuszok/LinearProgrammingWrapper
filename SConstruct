import os
import SCons.Tool

################################################################################

useStaticLink = int(ARGUMENTS.get('static',   0))
debugSymbols  = int(ARGUMENTS.get('debug',    0))
optimization  = int(ARGUMENTS.get('optimize', 0 if debugSymbols else 1))

################################################################################

# Directories configuration

target   = 'debug/' if debugSymbols else 'release/'

# Main directories
lpw       = 'lpw/'
include   = 'include/'
source    = 'src/'
test      = 'test/'
objects   = 'objects/' + target
libraries = 'bin/'     + target

################################################################################

# Used flags

GccFlags = {
  'COMMON'       : [ '-std=c++11' ],
  'WARNINGS'     : [ '-Wall', '-Wextra', '-Werror', '-pedantic-errors' ],
  'DEBUG'        : [ '-g' ],
  'OPTIMIZATION' : [ '-O3' ],
  'STATIC'       : [ '--static' ],
  'PCH'          : [ '-x', 'c++' ]
}
if not debugSymbols:
  GccFlags['COMMON'].append('-DNDEBUG')

# Select used flags
Flags = GccFlags

################################################################################

def targetForStatic(file):
  return str(file).replace('.cpp', env['OBJSUFFIX']).replace(source, objects)

def targetForShared(file):
  return str(file).replace('.cpp', env['SHOBJSUFFIX']).replace(source, objects)

################################################################################

# Production environment configuration

env = Environment()

# Allows overridding default compiler with eg. Clang.
env['CC']          = os.getenv('CC')   or env['CC']
env['CXX']         = os.getenv('CXX')  or env['CXX']
env['ENV']['PATH'] = os.getenv('PATH') or env['ENV']['PATH']
env['ENV'].update(x for x in os.environ.items() if x[0].startswith('CCC_'))

# Assuming that instalation is valid unless proved otherwise
validInstallation = True

conf = Configure(env)

# C++ check
if not conf.CheckCXX():
  print('Your environment/C++ compiler is not configured/installed correctly!!')
  validInstallation = False

# Header check
for header in [
  # standard libraries
  'cstdlib', 'vector', 'string'
]:
  if not conf.CheckCXXHeader(header):
    print('Your environment does not seem to have header <'+header+'>!!')
    validInstallation = False


# Assuming no library present
lpLibraryPresent = False

# GNU Linear Package Kit
if conf.CheckCXXHeader('glpk.h'):
  print('GLPK library available!!')
  lpLibraryPresent = True
  GccFlags['COMMON'].append('-DGLPK_AVAILABLE')

if not lpLibraryPresent:
  print('No LP library present!!')
  validInstallation = False


# Sets C++11 standard to be used during compilation.
conf.env.Append(CPPFLAGS=Flags['COMMON'])
# Sets warning informations in main conf.
conf.env.Append(CPPFLAGS=Flags['WARNINGS'])
# Makes executables contain debug information.
if debugSymbols:
  conf.env.Append(CPPFLAGS=Flags['DEBUG'])
# Turns on optimization.
if optimization:
  conf.env.Append(CPPFLAGS=Flags['OPTIMIZATION'])

conf.env.Append(CPPPATH=[include, source])

conf.Finish()

################################################################################

# Validate installation

# Terminate build if installation is not valid
if not validInstallation:
  print('Invalid compiler/libraries installation - build terminated!!')
  Exit(1)

################################################################################

# Sources

sources = Glob(source+lpw+'*.cpp')

################################################################################

# Static library

staticObjects = [
  env.StaticObject(
    source=source_cpp,
    target=targetForStatic(source_cpp)
  )
  for source_cpp in sources
]
staticLibrary = env.Library(
  source=staticObjects,
  target=libraries+'lpw'
)

################################################################################

# Dynamic library

staticObjects = [
  env.StaticObject(
    source=source_cpp,
    target=targetForStatic(source_cpp)
  )
  for source_cpp in sources
]
staticLibrary = env.Library(
  source=staticObjects,
  target=libraries+'lpw'
)
