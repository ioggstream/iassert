#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=simple_test

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=simple_test multiple_test

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
simple_test_SOURCES=simple_test.c
multiple_test_SOURCES=multiple_test.c

AM_LDFLAGS=-L/usr/local/lib/ -liassert
# Linker options for a.out
#simple_test_LDFLAGS = $(top_srcdir)/libiassert/libiassert.la
#multiple_test_LDFLAGS = $(top_srcdir)/libiassert/libiassert.la

# Compiler options for a.out
simple_test_CPPFLAGS = -I$(top_srcdir)/include
multiple_test_CPPFLAGS = -I$(top_srcdir)/include
