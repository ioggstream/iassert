dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(iassert, 0.1-beta)
AC_PROG_CC

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
                examples/Makefile
                libiassert/Makefile
                include/Makefile)

AC_OUTPUT
AC_CONFIG_MACRO_DIR([m4])
