# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

utildir=$(pkgincludedir)/util

AM_CXXFLAGS = -I$(srcdir)/.. $(CONFIGURE_CXXFLAGS) -DBOOST_LOG_DYN_LINK

# Headers
util_HEADERS = logger.h timeconvert.h

noinst_LTLIBRARIES = libutil.la
libutil_la_SOURCES = logger.cc \
                     timeconvert.cc
