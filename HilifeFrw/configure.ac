#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([HLFramework], [0.1.0])


# fix warning caused by SDL stuff
# AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([HLFramework], [0.1.0])
AC_CONFIG_SRCDIR([./pre.h])
AC_CONFIG_HEADER([config.h])

# Templates
AH_TEMPLATE([_DEBUG], [Define if building with debug symbols])

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_CC

# configure options
AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug], [Build with debugging symbols]), , enable_debug=no)

if test "x$enable_debug" = "xno"
then
    CFLAGS="-O3"
    CXXFLAGS="-fomit-frame-pointer -O3"
else
    CFLAGS="-g3 -O0"
    CXXFLAGS="-g3 -O0"
    AC_DEFINE([_DEBUG], 1)
fi

# Checks for libraries.
PKG_CHECK_MODULES(CEGUI, CEGUI >= 0.3.0)
PKG_CHECK_MODULES(OGRE, OGRE>=1.0.0)

# Check for SDL
#SDL_VERSION=1.2.0
#AM_PATH_SDL($SDL_VERSION,
#            :,
#            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
#)

#AM_CFLAGS="$AM_CFLAGS -DLINUX"
#AM_LDFLAGS="$AM_LDFLAGS"
#AC_SUBST(AM_CFLAGS)
#AC_SUBST(AM_LDFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_STAT
AC_CHECK_FUNCS([getcwd memset sqrt])

HLFWK_CURRENT=1
HLFWK_REVISION=0
HLFWK_AGE=0
HLFWK_VERSION_INFO=$HLFWK_CURRENT:$HLFWK_REVISION:$HLFWK_AGE
AC_SUBST(HLFWK_VERSION_INFO)

AC_CONFIG_FILES([Makefile,
  HilifeDll/Makefile])

AC_OUTPUT
