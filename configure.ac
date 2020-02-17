# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

# Initialize autotools configs
AC_INIT([libtcta3cpp], [20.20190211.0], [tc-ta3@bbn.com])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_LINKS([tests/TCCDMDatum.avsc:tests/TCCDMDatum.avsc])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_PROG_AR
AC_CONFIG_MACRO_DIR([m4])
LT_INIT
AC_LANG([C++])
AC_PROG_CXX

SAVED_LIBS=$LIBS

case "$host_os" in
freebsd*)
  CPPFLAGS="$CPPFLAGS -I/usr/local/include"
  LDFLAGS="$CPPFLAGS -L/usr/local/lib"
  ;;
esac

## Avro
AC_CHECK_HEADERS([avro/ValidSchema.hh], [],
  [AC_MSG_ERROR([required header avro/ValidSchema.hh not found])])
LIBS="$LIBS -lavrocpp"
AC_MSG_CHECKING([for libavrocpp])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM([[#include <avro/ValidSchema.hh>]],
                   [[avro::ValidSchema schema]])],
  [AC_MSG_RESULT([yes])],
  [
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([libavrocpp not found])
  ]
)
AVROCPP_LIBS="-lavrocpp"
AC_SUBST([AVROCPP_LIBS])
LIBS=$SAVED_LIBS

## RdKafka
PKG_CHECK_MODULES([RDKAFKACPP], [rdkafka++ = 0.11.4])

## Google test
PKG_CHECK_MODULES([GTEST], [gtest])

## Boost log
AC_CHECK_HEADERS([boost/log/trivial.hpp], [],
  [AC_MSG_ERROR([required header boost/log/trivial.hpp not found])])
LIBS="$LIBS -lboost_log -lpthread"
SAVED_LDFLAGS=$LDFLAGS
LDFLAGS="-DBOOST_LOG_DYN_LINK $LDFLAGS"
AC_MSG_CHECKING([for libboost_log])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM([[#include <boost/log/trivial.hpp>]],
                   [[BOOST_LOG_TRIVIAL(info) << "test"]])],
  [AC_MSG_RESULT([yes])],
  [
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([libboost_log not found])
  ]
)
BOOST_LOG_LIBS="-lboost_log -lboost_log_setup -lpthread"
AC_SUBST([BOOST_LOG_LIBS])
LIBS=$SAVED_LIBS
LDFLAGS=$SAVED_LDFLAGS


## tc_schema
AC_CHECK_HEADERS([tc_schema/cdm.h], [],
  [AC_MSG_ERROR([required header tc_schema/cdm.h not found])])

# Define automake variables
CONFIGURE_CXXFLAGS="-Wall -Wno-deprecated-register -Wno-missing-braces -Werror -pedantic -std=c++11"
AC_SUBST([CONFIGURE_CXXFLAGS])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/records/Makefile
    src/serialization/Makefile
    src/services/Makefile
    src/util/Makefile
    tests/Makefile
    examples/Makefile
  ])

AC_CONFIG_LINKS([conf/logconfig.ini:conf/logconfig.ini])

AC_OUTPUT
