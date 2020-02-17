# Copyright (c) 2020 Raytheon BBN Technologies Corp.
# See LICENSE.txt for details.

SUBDIRS = records serialization services util

AM_CXXFLAGS = $(CONFIGURE_CXXFLAGS)

# Libraries
lib_LTLIBRARIES = libtcta3cpp.la
libtcta3cpp_la_SOURCES =
# Point to a dummy cxx file to force linking with a CXX compiler
nodist_EXTRA_libtcta3cpp_la_SOURCES = dummy.cxx
libtcta3cpp_la_LIBADD = serialization/libserialization.la records/librecords.la services/libservices.la util/libutil.la
# Note that libtool's version-info does NOT correspond to release version.
libtcta3cpp_la_LDFLAGS = -version-info 15:0:0
