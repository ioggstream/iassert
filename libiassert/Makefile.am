#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libiassert.la

#######################################
# Build information for each library

# Sources for libiassert
libiassert_la_SOURCES = libiassert.c signal_handler.c

# Linker options libTestProgram
libiassert_la_LDFLAGS = -L/usr/local/lib/

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libiassert_la_CPPFLAGS = -I$(top_srcdir)/include

