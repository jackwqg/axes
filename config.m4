dnl $Id$
dnl config.m4 for extension axes

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(axes, for axes support,
Make sure that the comment is aligned:
[  --with-axes             Include axes support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(axes, whether to enable axes support,
Make sure that the comment is aligned:
[  --enable-axes           Enable axes support])

if test "$PHP_AXES" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-axes -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/axes.h"  # you most likely want to change this
  dnl if test -r $PHP_AXES/$SEARCH_FOR; then # path given as parameter
  dnl   AXES_DIR=$PHP_AXES
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for axes files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       AXES_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$AXES_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the axes distribution])
  dnl fi

  dnl # --with-axes -> add include path
  dnl PHP_ADD_INCLUDE($AXES_DIR/include)

  dnl # --with-axes -> check for lib and symbol presence
  dnl LIBNAME=axes # you may want to change this
  dnl LIBSYMBOL=axes # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $AXES_DIR/$PHP_LIBDIR, AXES_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_AXESLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong axes lib version or lib not found])
  dnl ],[
  dnl   -L$AXES_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(AXES_SHARED_LIBADD)

  PHP_NEW_EXTENSION(axes, axes.c, $ext_shared)
fi
