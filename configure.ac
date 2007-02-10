### configure.ac  -*- Autoconf -*-

AC_PREREQ(2.59)
dnl FIXME: full name? version?
AC_INIT([HDFdump], [0.1-is], [ivan@theory.asu.ru])
AC_CONFIG_SRCDIR([src/hdfdump.c])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

AC_DEFUN([MY_NO_FUNCTION],
  [AC_MSG_ERROR([Required function not found])])
AC_DEFUN([MY_NO_LIBRARY],
  [AC_MSG_ERROR([Required library not found])])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([m],      [sqrt], , [MY_NO_LIBRARY])
AC_CHECK_LIB([z],      [deflate], , [MY_NO_LIBRARY])
AC_CHECK_LIB([jpeg],   [jpeg_read_header], , [MY_NO_LIBRARY])
AC_CHECK_LIB([df],     [DFopen], , [MY_NO_LIBRARY])
AC_CHECK_LIB([mfhdf],  [SDstart], , [MY_NO_LIBRARY])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([strchr strdup strtol])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])

AC_OUTPUT

### configure.ac ends here
